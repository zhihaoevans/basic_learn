import scrapy
from scrapy_examples.items import QuoteItem


class QuotesSpider(scrapy.Spider):
    """基础爬虫示例 - 抓取名言网站
    
    演示功能:
    - 基本的网页抓取
    - CSS选择器和XPath使用
    - 数据提取和Item使用
    - 分页处理
    - 请求和响应处理
    """
    
    name = 'quotes'
    allowed_domains = ['quotes.toscrape.com']
    start_urls = ['http://quotes.toscrape.com/']
    
    # 自定义设置（可选）
    custom_settings = {
        'DOWNLOAD_DELAY': 2,
        'CONCURRENT_REQUESTS': 1,
        'ITEM_PIPELINES': {
            'scrapy_examples.pipelines.ValidationPipeline': 300,
            'scrapy_examples.pipelines.JsonWriterPipeline': 500,
        }
    }
    
    def parse(self, response):
        """解析主页面，提取引用数据"""
        self.logger.info(f'Parsing page: {response.url}')
        
        # 使用CSS选择器提取引用
        quotes = response.css('div.quote')
        
        for quote in quotes:
            # 方法1: 直接返回字典
            # yield {
            #     'text': quote.css('span.text::text').get(),
            #     'author': quote.css('small.author::text').get(),
            #     'tags': quote.css('div.tags a.tag::text').getall(),
            # }
            
            # 方法2: 使用Item类（推荐）
            item = QuoteItem()
            item['text'] = quote.css('span.text::text').get()
            item['author'] = quote.css('small.author::text').get()
            item['tags'] = quote.css('div.tags a.tag::text').getall()
            
            yield item
            
            # 方法3: 使用XPath（替代方案）
            # yield QuoteItem(
            #     text=quote.xpath('.//span[@class="text"]/text()').get(),
            #     author=quote.xpath('.//small[@class="author"]/text()').get(),
            #     tags=quote.xpath('.//div[@class="tags"]/a/text()').getall()
            # )
        
        # 处理分页 - 跟随下一页链接
        next_page = response.css('li.next a::attr(href)').get()
        if next_page is not None:
            # 方法1: 使用response.follow（推荐，自动处理相对URL）
            yield response.follow(next_page, callback=self.parse)
            
            # 方法2: 使用scrapy.Request
            # next_page_url = response.urljoin(next_page)
            # yield scrapy.Request(url=next_page_url, callback=self.parse)
    
    def start_requests(self):
        """自定义起始请求（可选重写）"""
        for url in self.start_urls:
            yield scrapy.Request(
                url=url,
                callback=self.parse,
                headers={
                    'User-Agent': 'Mozilla/5.0 (compatible; QuotesBot/1.0)'
                },
                meta={
                    'dont_cache': True,  # 不缓存此请求
                    'download_timeout': 30,  # 30秒超时
                }
            )
    
    def parse_author(self, response):
        """解析作者页面（示例回调函数）"""
        author_name = response.css('h3.author-title::text').get()
        author_birth_date = response.css('span.author-born-date::text').get()
        author_birth_location = response.css('span.author-born-location::text').get()
        author_description = response.css('div.author-description::text').get()
        
        yield {
            'name': author_name,
            'birth_date': author_birth_date,
            'birth_location': author_birth_location,
            'description': author_description.strip() if author_description else None
        }


class QuotesJSSpider(scrapy.Spider):
    """JavaScript渲染页面爬虫示例
    
    演示功能:
    - 处理JavaScript渲染的页面
    - 使用Splash或Selenium（需要额外配置）
    """
    
    name = 'quotes_js'
    allowed_domains = ['quotes.toscrape.com']
    start_urls = ['http://quotes.toscrape.com/js/']
    
    def parse(self, response):
        """解析JavaScript渲染的页面"""
        # 注意：这个示例需要配置Splash或Selenium中间件
        # 这里只是展示基本结构
        
        quotes = response.css('div.quote')
        
        for quote in quotes:
            yield QuoteItem(
                text=quote.css('span.text::text').get(),
                author=quote.css('small.author::text').get(),
                tags=quote.css('div.tags a.tag::text').getall()
            )
        
        # 处理无限滚动或动态加载的内容
        # 这通常需要JavaScript执行
        next_page = response.css('li.next a::attr(href)').get()
        if next_page:
            yield response.follow(next_page, callback=self.parse)


class QuotesAPISpider(scrapy.Spider):
    """API爬虫示例
    
    演示功能:
    - 抓取JSON API
    - 处理API分页
    - 请求头和参数设置
    """
    
    name = 'quotes_api'
    allowed_domains = ['quotes.toscrape.com']
    
    def start_requests(self):
        """生成API请求"""
        api_url = 'http://quotes.toscrape.com/api/quotes'
        
        yield scrapy.Request(
            url=api_url,
            callback=self.parse_api,
            headers={
                'Accept': 'application/json',
                'Content-Type': 'application/json'
            },
            meta={'page': 1}
        )
    
    def parse_api(self, response):
        """解析API响应"""
        import json
        
        try:
            data = json.loads(response.text)
            quotes = data.get('quotes', [])
            
            for quote_data in quotes:
                yield QuoteItem(
                    text=quote_data.get('text'),
                    author=quote_data.get('author', {}).get('name'),
                    tags=quote_data.get('tags', [])
                )
            
            # 处理API分页
            current_page = response.meta['page']
            has_next = data.get('has_next', False)
            
            if has_next:
                next_page = current_page + 1
                next_url = f'http://quotes.toscrape.com/api/quotes?page={next_page}'
                
                yield scrapy.Request(
                    url=next_url,
                    callback=self.parse_api,
                    headers=response.request.headers,
                    meta={'page': next_page}
                )
                
        except json.JSONDecodeError as e:
            self.logger.error(f'JSON decode error: {e}')
        except Exception as e:
            self.logger.error(f'Unexpected error: {e}')