import scrapy
from scrapy import FormRequest
from scrapy_examples.items import NewsItem, ProductItem
import json
import base64
from urllib.parse import urljoin, urlparse


class LoginSpider(scrapy.Spider):
    """登录爬虫示例
    
    演示功能:
    - 表单登录
    - Session管理
    - Cookie处理
    - 登录后数据抓取
    """
    
    name = 'login_spider'
    allowed_domains = ['quotes.toscrape.com']
    start_urls = ['http://quotes.toscrape.com/login']
    
    def parse(self, response):
        """解析登录页面并提交登录表单"""
        self.logger.info('Parsing login page')
        
        # 提取CSRF token（如果有的话）
        csrf_token = response.css('input[name="csrf_token"]::attr(value)').get()
        
        # 构造登录数据
        formdata = {
            'username': 'admin',  # 示例用户名
            'password': 'admin',  # 示例密码
        }
        
        if csrf_token:
            formdata['csrf_token'] = csrf_token
        
        # 提交登录表单
        return FormRequest.from_response(
            response,
            formdata=formdata,
            callback=self.after_login
        )
    
    def after_login(self, response):
        """登录后的处理"""
        # 检查是否登录成功
        if 'logout' in response.text.lower():
            self.logger.info('Login successful')
            
            # 访问需要登录的页面
            yield scrapy.Request(
                url='http://quotes.toscrape.com/',
                callback=self.parse_protected_content
            )
        else:
            self.logger.error('Login failed')
    
    def parse_protected_content(self, response):
        """解析需要登录才能访问的内容"""
        quotes = response.css('div.quote')
        
        for quote in quotes:
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.css('small.author::text').get(),
                'tags': quote.css('div.tags a.tag::text').getall(),
                'logged_in': True
            }


class AjaxSpider(scrapy.Spider):
    """AJAX请求爬虫示例
    
    演示功能:
    - AJAX请求处理
    - JSON数据解析
    - 动态内容加载
    - 请求头设置
    """
    
    name = 'ajax_spider'
    allowed_domains = ['httpbin.org']
    
    def start_requests(self):
        """生成AJAX请求"""
        ajax_url = 'http://httpbin.org/json'
        
        yield scrapy.Request(
            url=ajax_url,
            callback=self.parse_json,
            headers={
                'Accept': 'application/json, text/javascript, */*; q=0.01',
                'X-Requested-With': 'XMLHttpRequest',
                'Content-Type': 'application/json'
            }
        )
    
    def parse_json(self, response):
        """解析JSON响应"""
        try:
            data = json.loads(response.text)
            
            yield {
                'slideshow_title': data.get('slideshow', {}).get('title'),
                'author': data.get('slideshow', {}).get('author'),
                'slides_count': len(data.get('slideshow', {}).get('slides', [])),
                'response_url': response.url
            }
            
        except json.JSONDecodeError as e:
            self.logger.error(f'JSON decode error: {e}')


class FileDownloadSpider(scrapy.Spider):
    """文件下载爬虫示例
    
    演示功能:
    - 文件下载
    - 二进制数据处理
    - 文件保存
    - 进度跟踪
    """
    
    name = 'file_download'
    allowed_domains = ['httpbin.org']
    start_urls = ['http://httpbin.org/image/png']
    
    custom_settings = {
        'ITEM_PIPELINES': {
            'scrapy.pipelines.files.FilesPipeline': 1,
        },
        'FILES_STORE': 'downloads',
    }
    
    def parse(self, response):
        """处理文件下载"""
        if response.headers.get('content-type', b'').startswith(b'image/'):
            # 保存图片文件
            filename = f"downloaded_image_{hash(response.url)}.png"
            
            with open(filename, 'wb') as f:
                f.write(response.body)
            
            yield {
                'file_url': response.url,
                'file_size': len(response.body),
                'content_type': response.headers.get('content-type', b'').decode(),
                'filename': filename
            }


class ProxySpider(scrapy.Spider):
    """代理使用示例
    
    演示功能:
    - 代理设置
    - IP轮换
    - 代理验证
    """
    
    name = 'proxy_spider'
    allowed_domains = ['httpbin.org']
    
    def __init__(self, *args, **kwargs):
        super(ProxySpider, self).__init__(*args, **kwargs)
        # 代理列表（示例，实际使用时需要有效代理）
        self.proxies = [
            # 'http://proxy1:port',
            # 'http://proxy2:port',
        ]
    
    def start_requests(self):
        """使用代理发起请求"""
        url = 'http://httpbin.org/ip'
        
        # 不使用代理的请求
        yield scrapy.Request(
            url=url,
            callback=self.parse_ip,
            meta={'proxy_used': None}
        )
        
        # 使用代理的请求
        for i, proxy in enumerate(self.proxies):
            yield scrapy.Request(
                url=url,
                callback=self.parse_ip,
                meta={
                    'proxy': proxy,
                    'proxy_used': proxy
                }
            )
    
    def parse_ip(self, response):
        """解析IP信息"""
        try:
            data = json.loads(response.text)
            yield {
                'origin_ip': data.get('origin'),
                'proxy_used': response.meta.get('proxy_used'),
                'response_url': response.url
            }
        except json.JSONDecodeError:
            self.logger.error('Failed to parse IP response')


class CookieSpider(scrapy.Spider):
    """Cookie处理示例
    
    演示功能:
    - Cookie设置和获取
    - Session管理
    - 状态保持
    """
    
    name = 'cookie_spider'
    allowed_domains = ['httpbin.org']
    
    def start_requests(self):
        """设置初始Cookie"""
        yield scrapy.Request(
            url='http://httpbin.org/cookies/set/session_id/abc123',
            callback=self.parse_with_cookies,
            cookies={'initial_cookie': 'test_value'}
        )
    
    def parse_with_cookies(self, response):
        """处理带Cookie的响应"""
        # 检查Cookie
        yield scrapy.Request(
            url='http://httpbin.org/cookies',
            callback=self.parse_cookies
        )
    
    def parse_cookies(self, response):
        """解析Cookie信息"""
        try:
            data = json.loads(response.text)
            yield {
                'cookies': data.get('cookies', {}),
                'response_url': response.url
            }
        except json.JSONDecodeError:
            self.logger.error('Failed to parse cookies response')


class HeadersSpider(scrapy.Spider):
    """请求头处理示例
    
    演示功能:
    - 自定义请求头
    - User-Agent设置
    - Referer处理
    """
    
    name = 'headers_spider'
    allowed_domains = ['httpbin.org']
    
    def start_requests(self):
        """发送带自定义头的请求"""
        custom_headers = {
            'User-Agent': 'Custom Spider Bot 1.0',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5',
            'Accept-Encoding': 'gzip, deflate',
            'Referer': 'https://www.google.com/',
            'Custom-Header': 'Custom-Value'
        }
        
        yield scrapy.Request(
            url='http://httpbin.org/headers',
            callback=self.parse_headers,
            headers=custom_headers
        )
    
    def parse_headers(self, response):
        """解析请求头信息"""
        try:
            data = json.loads(response.text)
            yield {
                'headers': data.get('headers', {}),
                'response_url': response.url
            }
        except json.JSONDecodeError:
            self.logger.error('Failed to parse headers response')


class ErrorHandlingSpider(scrapy.Spider):
    """错误处理示例
    
    演示功能:
    - 异常处理
    - 重试机制
    - 错误日志
    - 降级处理
    """
    
    name = 'error_handling'
    allowed_domains = ['httpbin.org']
    
    def start_requests(self):
        """生成可能出错的请求"""
        urls = [
            'http://httpbin.org/status/200',  # 正常
            'http://httpbin.org/status/404',  # 404错误
            'http://httpbin.org/status/500',  # 服务器错误
            'http://httpbin.org/delay/10',    # 超时
            'http://invalid-domain.com',      # DNS错误
        ]
        
        for url in urls:
            yield scrapy.Request(
                url=url,
                callback=self.parse_response,
                errback=self.handle_error,
                meta={
                    'dont_retry': False,
                    'download_timeout': 5
                }
            )
    
    def parse_response(self, response):
        """处理正常响应"""
        yield {
            'url': response.url,
            'status': response.status,
            'success': True,
            'content_length': len(response.body)
        }
    
    def handle_error(self, failure):
        """处理请求错误"""
        request = failure.request
        
        self.logger.error(f'Request failed: {request.url} - {failure.value}')
        
        yield {
            'url': request.url,
            'error': str(failure.value),
            'error_type': failure.type.__name__,
            'success': False
        }