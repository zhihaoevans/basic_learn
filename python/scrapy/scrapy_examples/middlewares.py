# Define here the models for your spider middleware
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/spider-middleware.html

from scrapy import signals
from scrapy.http import HtmlResponse
from scrapy.downloadermiddlewares.retry import RetryMiddleware
from scrapy.utils.response import response_status_message
import random
import time
import logging
from urllib.parse import urljoin


class ScrapyExamplesSpiderMiddleware:
    """Spider中间件示例"""
    
    @classmethod
    def from_crawler(cls, crawler):
        # This method is used by Scrapy to create your spiders.
        s = cls()
        crawler.signals.connect(s.spider_opened, signal=signals.spider_opened)
        return s

    def process_spider_input(self, response, spider):
        # Called for each response that goes through the spider
        # middleware and into the spider.
        return None

    def process_spider_output(self, response, result, spider):
        # Called with the results returned from the Spider, after
        # it has processed the response.
        for i in result:
            yield i

    def process_spider_exception(self, response, exception, spider):
        # Called when a spider or process_spider_input() method
        # (from other spider middleware) raises an exception.
        spider.logger.error(f"Spider exception: {exception}")
        pass

    def process_start_requests(self, start_requests, spider):
        # Called with the start requests of the spider, and works
        # similarly to the process_spider_output() method, except
        # that it doesn't have a response associated.
        for r in start_requests:
            yield r

    def spider_opened(self, spider):
        spider.logger.info('Spider opened: %s' % spider.name)


class ScrapyExamplesDownloaderMiddleware:
    """下载器中间件示例"""
    
    @classmethod
    def from_crawler(cls, crawler):
        # This method is used by Scrapy to create your spiders.
        s = cls()
        crawler.signals.connect(s.spider_opened, signal=signals.spider_opened)
        return s

    def process_request(self, request, spider):
        # Called for each request that goes through the downloader
        # middleware.
        
        # 添加随机延迟
        time.sleep(random.uniform(0.5, 2.0))
        
        # 记录请求
        spider.logger.debug(f"Processing request: {request.url}")
        
        return None

    def process_response(self, request, response, spider):
        # Called with the response returned from the downloader.
        
        # 检查响应状态
        if response.status != 200:
            spider.logger.warning(
                f"Non-200 response {response.status} for {request.url}"
            )
            
        return response

    def process_exception(self, request, exception, spider):
        # Called when a download handler or a process_request()
        # (from other downloader middleware) raises an exception.
        spider.logger.error(f"Download exception for {request.url}: {exception}")
        pass

    def spider_opened(self, spider):
        spider.logger.info('Spider opened: %s' % spider.name)


class UserAgentMiddleware:
    """用户代理轮换中间件"""
    
    def __init__(self):
        self.user_agents = [
            'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
            'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
            'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
            'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:89.0) Gecko/20100101 Firefox/89.0',
            'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0',
        ]
        
    def process_request(self, request, spider):
        # 随机选择User-Agent
        ua = random.choice(self.user_agents)
        request.headers['User-Agent'] = ua
        spider.logger.debug(f"Using User-Agent: {ua}")
        return None


class ProxyMiddleware:
    """代理中间件"""
    
    def __init__(self):
        # 示例代理列表（实际使用时需要有效的代理）
        self.proxies = [
            # 'http://proxy1:port',
            # 'http://proxy2:port',
            # 'http://proxy3:port',
        ]
        
    def process_request(self, request, spider):
        if self.proxies:
            proxy = random.choice(self.proxies)
            request.meta['proxy'] = proxy
            spider.logger.debug(f"Using proxy: {proxy}")
        return None


class CustomRetryMiddleware(RetryMiddleware):
    """自定义重试中间件"""
    
    def __init__(self, settings):
        super().__init__(settings)
        self.max_retry_times = settings.getint('RETRY_TIMES')
        self.retry_http_codes = set(int(x) for x in settings.getlist('RETRY_HTTP_CODES'))
        self.priority_adjust = settings.getint('RETRY_PRIORITY_ADJUST')
        
    def process_response(self, request, response, spider):
        if request.meta.get('dont_retry', False):
            return response
            
        if response.status in self.retry_http_codes:
            reason = response_status_message(response.status)
            return self._retry(request, reason, spider) or response
            
        return response
        
    def process_exception(self, request, exception, spider):
        if isinstance(exception, self.EXCEPTIONS_TO_RETRY) and not request.meta.get('dont_retry', False):
            return self._retry(request, exception, spider)


class CookieMiddleware:
    """Cookie处理中间件"""
    
    def __init__(self):
        self.cookies = {}
        
    def process_request(self, request, spider):
        # 为特定域名设置cookies
        if 'example.com' in request.url:
            request.cookies.update({
                'session_id': 'example_session_123',
                'user_pref': 'dark_mode'
            })
        return None
        
    def process_response(self, request, response, spider):
        # 保存响应中的cookies
        if hasattr(response, 'cookies'):
            for cookie in response.cookies:
                self.cookies[cookie.name] = cookie.value
                spider.logger.debug(f"Saved cookie: {cookie.name}={cookie.value}")
        return response


class JavaScriptMiddleware:
    """JavaScript渲染中间件（需要selenium或splash）"""
    
    def __init__(self):
        # 注意：这里只是示例，实际使用需要安装selenium
        self.js_enabled_domains = ['spa-example.com', 'react-app.com']
        
    def process_request(self, request, spider):
        # 检查是否需要JavaScript渲染
        for domain in self.js_enabled_domains:
            if domain in request.url:
                request.meta['render_js'] = True
                spider.logger.info(f"JavaScript rendering enabled for {request.url}")
                break
        return None
        
    def process_response(self, request, response, spider):
        # 如果需要JS渲染但没有渲染，这里可以集成selenium等工具
        if request.meta.get('render_js') and not request.meta.get('js_rendered'):
            spider.logger.warning(f"JavaScript rendering requested but not performed for {request.url}")
        return response


class CacheMiddleware:
    """自定义缓存中间件"""
    
    def __init__(self):
        self.cache = {}
        self.cache_timeout = 3600  # 1小时缓存
        
    def process_request(self, request, spider):
        # 检查缓存
        cache_key = self._get_cache_key(request)
        if cache_key in self.cache:
            cached_response, timestamp = self.cache[cache_key]
            if time.time() - timestamp < self.cache_timeout:
                spider.logger.info(f"Cache hit for {request.url}")
                return cached_response
            else:
                # 缓存过期，删除
                del self.cache[cache_key]
        return None
        
    def process_response(self, request, response, spider):
        # 缓存响应
        if response.status == 200:
            cache_key = self._get_cache_key(request)
            self.cache[cache_key] = (response, time.time())
            spider.logger.debug(f"Cached response for {request.url}")
        return response
        
    def _get_cache_key(self, request):
        return f"{request.method}:{request.url}"