# Define here the extensions for your Scrapy project
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/extensions.html

from scrapy import signals
from scrapy.exceptions import NotConfigured
import logging
import time
import json
from datetime import datetime


class CustomStatsExtension:
    """自定义统计扩展"""
    
    def __init__(self, crawler):
        self.crawler = crawler
        self.stats = crawler.stats
        self.start_time = None
        self.custom_stats = {
            'pages_crawled': 0,
            'items_scraped': 0,
            'errors_count': 0,
            'response_times': [],
            'status_codes': {}
        }
        
    @classmethod
    def from_crawler(cls, crawler):
        # 检查扩展是否启用
        if not crawler.settings.getbool('CUSTOM_STATS_ENABLED', True):
            raise NotConfigured('Custom stats extension disabled')
            
        ext = cls(crawler)
        
        # 连接信号
        crawler.signals.connect(ext.spider_opened, signal=signals.spider_opened)
        crawler.signals.connect(ext.spider_closed, signal=signals.spider_closed)
        crawler.signals.connect(ext.request_scheduled, signal=signals.request_scheduled)
        crawler.signals.connect(ext.response_received, signal=signals.response_received)
        crawler.signals.connect(ext.item_scraped, signal=signals.item_scraped)
        crawler.signals.connect(ext.spider_error, signal=signals.spider_error)
        
        return ext
        
    def spider_opened(self, spider):
        self.start_time = time.time()
        spider.logger.info(f"Custom stats extension started for spider: {spider.name}")
        
    def spider_closed(self, spider, reason):
        end_time = time.time()
        duration = end_time - self.start_time if self.start_time else 0
        
        # 计算平均响应时间
        avg_response_time = (
            sum(self.custom_stats['response_times']) / len(self.custom_stats['response_times'])
            if self.custom_stats['response_times'] else 0
        )
        
        # 生成统计报告
        report = {
            'spider_name': spider.name,
            'start_time': datetime.fromtimestamp(self.start_time).isoformat() if self.start_time else None,
            'end_time': datetime.fromtimestamp(end_time).isoformat(),
            'duration_seconds': round(duration, 2),
            'close_reason': reason,
            'pages_crawled': self.custom_stats['pages_crawled'],
            'items_scraped': self.custom_stats['items_scraped'],
            'errors_count': self.custom_stats['errors_count'],
            'average_response_time': round(avg_response_time, 3),
            'status_codes': self.custom_stats['status_codes'],
            'pages_per_minute': round(self.custom_stats['pages_crawled'] / (duration / 60), 2) if duration > 0 else 0
        }
        
        # 保存统计报告
        with open(f'{spider.name}_stats.json', 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)
            
        spider.logger.info(f"Custom stats report saved: {report}")
        
    def request_scheduled(self, request, spider):
        request.meta['request_start_time'] = time.time()
        
    def response_received(self, response, request, spider):
        self.custom_stats['pages_crawled'] += 1
        
        # 记录响应时间
        if 'request_start_time' in request.meta:
            response_time = time.time() - request.meta['request_start_time']
            self.custom_stats['response_times'].append(response_time)
            
        # 记录状态码
        status = response.status
        self.custom_stats['status_codes'][status] = self.custom_stats['status_codes'].get(status, 0) + 1
        
    def item_scraped(self, item, response, spider):
        self.custom_stats['items_scraped'] += 1
        
    def spider_error(self, failure, response, spider):
        self.custom_stats['errors_count'] += 1
        spider.logger.error(f"Spider error: {failure.value}")


class MemoryUsageExtension:
    """内存使用监控扩展"""
    
    def __init__(self, crawler):
        self.crawler = crawler
        self.check_interval = crawler.settings.getint('MEMORY_CHECK_INTERVAL', 60)  # 60秒检查一次
        self.memory_limit = crawler.settings.getint('MEMORY_LIMIT_MB', 500)  # 500MB限制
        
    @classmethod
    def from_crawler(cls, crawler):
        if not crawler.settings.getbool('MEMORY_MONITOR_ENABLED', False):
            raise NotConfigured('Memory monitor extension disabled')
            
        try:
            import psutil
        except ImportError:
            raise NotConfigured('psutil is required for memory monitoring')
            
        ext = cls(crawler)
        crawler.signals.connect(ext.spider_opened, signal=signals.spider_opened)
        return ext
        
    def spider_opened(self, spider):
        import psutil
        
        def check_memory():
            process = psutil.Process()
            memory_mb = process.memory_info().rss / 1024 / 1024
            
            spider.logger.info(f"Current memory usage: {memory_mb:.2f} MB")
            
            if memory_mb > self.memory_limit:
                spider.logger.warning(
                    f"Memory usage ({memory_mb:.2f} MB) exceeds limit ({self.memory_limit} MB)"
                )
                # 可以在这里实现内存清理或停止爬虫的逻辑
                
        # 定期检查内存使用
        from twisted.internet import task
        self.memory_task = task.LoopingCall(check_memory)
        self.memory_task.start(self.check_interval)


class ProgressExtension:
    """进度监控扩展"""
    
    def __init__(self, crawler):
        self.crawler = crawler
        self.log_interval = crawler.settings.getint('PROGRESS_LOG_INTERVAL', 100)
        self.requests_count = 0
        self.responses_count = 0
        self.items_count = 0
        
    @classmethod
    def from_crawler(cls, crawler):
        ext = cls(crawler)
        
        crawler.signals.connect(ext.request_scheduled, signal=signals.request_scheduled)
        crawler.signals.connect(ext.response_received, signal=signals.response_received)
        crawler.signals.connect(ext.item_scraped, signal=signals.item_scraped)
        
        return ext
        
    def request_scheduled(self, request, spider):
        self.requests_count += 1
        
    def response_received(self, response, request, spider):
        self.responses_count += 1
        
        if self.responses_count % self.log_interval == 0:
            spider.logger.info(
                f"Progress: {self.responses_count} responses, "
                f"{self.items_count} items, "
                f"{self.requests_count - self.responses_count} pending requests"
            )
            
    def item_scraped(self, item, response, spider):
        self.items_count += 1


class EmailNotificationExtension:
    """邮件通知扩展"""
    
    def __init__(self, crawler):
        self.crawler = crawler
        self.smtp_host = crawler.settings.get('SMTP_HOST')
        self.smtp_port = crawler.settings.getint('SMTP_PORT', 587)
        self.smtp_user = crawler.settings.get('SMTP_USER')
        self.smtp_password = crawler.settings.get('SMTP_PASSWORD')
        self.notification_emails = crawler.settings.getlist('NOTIFICATION_EMAILS', [])
        
    @classmethod
    def from_crawler(cls, crawler):
        if not crawler.settings.get('EMAIL_NOTIFICATIONS_ENABLED', False):
            raise NotConfigured('Email notifications disabled')
            
        ext = cls(crawler)
        
        crawler.signals.connect(ext.spider_closed, signal=signals.spider_closed)
        crawler.signals.connect(ext.spider_error, signal=signals.spider_error)
        
        return ext
        
    def spider_closed(self, spider, reason):
        if self.notification_emails:
            subject = f"Spider {spider.name} finished: {reason}"
            body = f"Spider {spider.name} has finished with reason: {reason}\n\n"
            body += f"Stats: {self.crawler.stats.get_stats()}"
            
            self._send_email(subject, body)
            spider.logger.info(f"Notification email sent for spider completion")
            
    def spider_error(self, failure, response, spider):
        if self.notification_emails:
            subject = f"Spider {spider.name} error"
            body = f"Spider {spider.name} encountered an error:\n\n{failure.value}"
            
            self._send_email(subject, body)
            spider.logger.info(f"Notification email sent for spider error")
            
    def _send_email(self, subject, body):
        # 这里只是示例，实际使用需要配置SMTP服务器
        # 可以使用smtplib或其他邮件库
        pass


class AutoThrottleExtension:
    """自定义自动限速扩展"""
    
    def __init__(self, crawler):
        self.crawler = crawler
        self.target_concurrency = crawler.settings.getfloat('AUTOTHROTTLE_TARGET_CONCURRENCY', 1.0)
        self.min_delay = crawler.settings.getfloat('AUTOTHROTTLE_MIN_DELAY', 0)
        self.max_delay = crawler.settings.getfloat('AUTOTHROTTLE_MAX_DELAY', 60)
        self.current_delay = crawler.settings.getfloat('DOWNLOAD_DELAY', 0)
        
    @classmethod
    def from_crawler(cls, crawler):
        if not crawler.settings.getbool('CUSTOM_AUTOTHROTTLE_ENABLED', False):
            raise NotConfigured('Custom autothrottle extension disabled')
            
        ext = cls(crawler)
        
        crawler.signals.connect(ext.response_received, signal=signals.response_received)
        
        return ext
        
    def response_received(self, response, request, spider):
        # 根据响应时间调整延迟
        if 'request_start_time' in request.meta:
            response_time = time.time() - request.meta['request_start_time']
            
            # 简单的自适应算法
            if response_time > 2.0:  # 响应时间过长，增加延迟
                self.current_delay = min(self.current_delay * 1.2, self.max_delay)
            elif response_time < 0.5:  # 响应时间很短，减少延迟
                self.current_delay = max(self.current_delay * 0.8, self.min_delay)
                
            # 更新下载延迟设置
            self.crawler.engine.downloader.delay = self.current_delay
            
            spider.logger.debug(
                f"Response time: {response_time:.2f}s, "
                f"Adjusted delay to: {self.current_delay:.2f}s"
            )