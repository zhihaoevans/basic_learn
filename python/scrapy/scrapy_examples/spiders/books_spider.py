import scrapy
from scrapy_examples.items import BookItem
from scrapy.loader import ItemLoader
from itemloaders.processors import TakeFirst, MapCompose, Join
import re


class BooksSpider(scrapy.Spider):
    """书籍爬虫示例 - 演示复杂数据提取
    
    演示功能:
    - ItemLoader使用
    - 复杂数据清洗和处理
    - 图片下载
    - 详情页面抓取
    - 错误处理
    """
    
    name = 'books'
    allowed_domains = ['books.toscrape.com']
    start_urls = ['http://books.toscrape.com/']
    
    custom_settings = {
        'ITEM_PIPELINES': {
            'scrapy_examples.pipelines.ValidationPipeline': 300,
            'scrapy_examples.pipelines.DuplicatesPipeline': 400,
            'scrapy.pipelines.images.ImagesPipeline': 450,
            'scrapy_examples.pipelines.DatabasePipeline': 500,
        },
        'IMAGES_STORE': 'images',
        'IMAGES_URLS_FIELD': 'image_urls',
        'IMAGES_RESULT_FIELD': 'images',
    }
    
    def parse(self, response):
        """解析书籍列表页面"""
        self.logger.info(f'Parsing books list: {response.url}')
        
        # 提取书籍链接
        book_links = response.css('article.product_pod h3 a::attr(href)').getall()
        
        for link in book_links:
            book_url = response.urljoin(link)
            yield scrapy.Request(
                url=book_url,
                callback=self.parse_book,
                meta={'book_list_url': response.url}
            )
        
        # 处理分页
        next_page = response.css('li.next a::attr(href)').get()
        if next_page:
            yield response.follow(next_page, callback=self.parse)
    
    def parse_book(self, response):
        """解析书籍详情页面"""
        self.logger.info(f'Parsing book details: {response.url}')
        
        # 使用ItemLoader进行数据加载和清洗
        loader = BookItemLoader(item=BookItem(), response=response)
        
        # 基本信息
        loader.add_css('title', 'h1::text')
        loader.add_css('price', 'p.price_color::text')
        loader.add_css('availability', 'p.instock.availability::text')
        
        # 评分处理
        rating_class = response.css('p.star-rating::attr(class)').get()
        if rating_class:
            rating_text = rating_class.split()[-1]  # 获取最后一个类名
            rating_map = {
                'One': 1, 'Two': 2, 'Three': 3, 'Four': 4, 'Five': 5
            }
            loader.add_value('rating', rating_map.get(rating_text, 0))
        
        # 描述信息
        description_paragraphs = response.css('#product_description ~ p::text').getall()
        if description_paragraphs:
            loader.add_value('description', description_paragraphs)
        
        # 图片URL
        image_url = response.css('div.item.active img::attr(src)').get()
        if image_url:
            full_image_url = response.urljoin(image_url)
            loader.add_value('image_urls', [full_image_url])
        
        # 页面URL
        loader.add_value('url', response.url)
        
        # 从表格中提取额外信息
        table_rows = response.css('table tr')
        for row in table_rows:
            header = row.css('th::text').get()
            value = row.css('td::text').get()
            
            if header and value:
                if 'UPC' in header:
                    loader.add_value('upc', value)
                elif 'Product Type' in header:
                    loader.add_value('product_type', value)
                elif 'Tax' in header:
                    loader.add_value('tax', value)
        
        yield loader.load_item()


class BookItemLoader(ItemLoader):
    """自定义ItemLoader - 演示数据处理器"""
    
    default_item_class = BookItem
    default_output_processor = TakeFirst()
    
    # 价格处理器
    price_in = MapCompose(
        lambda x: x.replace('£', '').replace('$', '').strip(),
        float
    )
    
    # 库存处理器
    availability_in = MapCompose(
        lambda x: re.search(r'\d+', x).group() if re.search(r'\d+', x) else '0',
        int
    )
    
    # 描述处理器
    description_out = Join(' ')


class BooksCategorySpider(scrapy.Spider):
    """按分类爬取书籍示例
    
    演示功能:
    - 分类页面处理
    - 动态URL生成
    - 条件过滤
    """
    
    name = 'books_category'
    allowed_domains = ['books.toscrape.com']
    start_urls = ['http://books.toscrape.com/']
    
    def parse(self, response):
        """解析主页，获取所有分类"""
        category_links = response.css('div.side_categories ul li ul li a')
        
        for category_link in category_links:
            category_name = category_link.css('::text').get().strip()
            category_url = category_link.css('::attr(href)').get()
            
            if category_url:
                full_url = response.urljoin(category_url)
                yield scrapy.Request(
                    url=full_url,
                    callback=self.parse_category,
                    meta={'category_name': category_name}
                )
    
    def parse_category(self, response):
        """解析分类页面"""
        category_name = response.meta['category_name']
        self.logger.info(f'Parsing category: {category_name}')
        
        # 提取该分类下的所有书籍
        book_links = response.css('article.product_pod h3 a::attr(href)').getall()
        
        for link in book_links:
            book_url = response.urljoin(link)
            yield scrapy.Request(
                url=book_url,
                callback=self.parse_book_with_category,
                meta={'category_name': category_name}
            )
        
        # 处理分类页面的分页
        next_page = response.css('li.next a::attr(href)').get()
        if next_page:
            yield response.follow(
                next_page,
                callback=self.parse_category,
                meta={'category_name': category_name}
            )
    
    def parse_book_with_category(self, response):
        """解析书籍页面并添加分类信息"""
        category_name = response.meta['category_name']
        
        loader = BookItemLoader(item=BookItem(), response=response)
        
        # 基本信息
        loader.add_css('title', 'h1::text')
        loader.add_css('price', 'p.price_color::text')
        loader.add_value('category', category_name)  # 添加分类信息
        loader.add_value('url', response.url)
        
        # 评分
        rating_class = response.css('p.star-rating::attr(class)').get()
        if rating_class:
            rating_text = rating_class.split()[-1]
            rating_map = {'One': 1, 'Two': 2, 'Three': 3, 'Four': 4, 'Five': 5}
            loader.add_value('rating', rating_map.get(rating_text, 0))
        
        yield loader.load_item()


class BooksSearchSpider(scrapy.Spider):
    """搜索功能爬虫示例
    
    演示功能:
    - 搜索表单提交
    - POST请求
    - 动态参数
    """
    
    name = 'books_search'
    allowed_domains = ['books.toscrape.com']
    
    def __init__(self, query='python', *args, **kwargs):
        super(BooksSearchSpider, self).__init__(*args, **kwargs)
        self.search_query = query
    
    def start_requests(self):
        """生成搜索请求"""
        # 注意：books.toscrape.com实际上没有搜索功能
        # 这里只是演示如何构造搜索请求
        search_url = 'http://books.toscrape.com/search/'
        
        return [
            scrapy.FormRequest(
                url=search_url,
                formdata={'q': self.search_query},
                callback=self.parse_search_results
            )
        ]
    
    def parse_search_results(self, response):
        """解析搜索结果"""
        self.logger.info(f'Parsing search results for: {self.search_query}')
        
        # 处理搜索结果
        books = response.css('article.product_pod')
        
        for book in books:
            title = book.css('h3 a::attr(title)').get()
            price = book.css('p.price_color::text').get()
            
            if title and self.search_query.lower() in title.lower():
                yield {
                    'title': title,
                    'price': price,
                    'search_query': self.search_query,
                    'url': response.urljoin(book.css('h3 a::attr(href)').get())
                }