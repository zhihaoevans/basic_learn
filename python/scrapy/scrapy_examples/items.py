# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy
from itemloaders.processors import TakeFirst, MapCompose, Join
from w3lib.html import remove_tags


class QuoteItem(scrapy.Item):
    """引用数据项 - 演示基本Item用法"""
    text = scrapy.Field()
    author = scrapy.Field()
    tags = scrapy.Field()
    

class BookItem(scrapy.Item):
    """书籍数据项 - 演示复杂Item用法"""
    title = scrapy.Field(
        input_processor=MapCompose(remove_tags, str.strip),
        output_processor=TakeFirst()
    )
    price = scrapy.Field(
        input_processor=MapCompose(remove_tags, str.strip),
        output_processor=TakeFirst()
    )
    availability = scrapy.Field(
        input_processor=MapCompose(remove_tags, str.strip),
        output_processor=TakeFirst()
    )
    rating = scrapy.Field(
        output_processor=TakeFirst()
    )
    description = scrapy.Field(
        input_processor=MapCompose(remove_tags, str.strip),
        output_processor=Join(' ')
    )
    image_urls = scrapy.Field()
    images = scrapy.Field()
    url = scrapy.Field()
    

class NewsItem(scrapy.Item):
    """新闻数据项 - 演示带有处理器的Item"""
    title = scrapy.Field()
    content = scrapy.Field()
    author = scrapy.Field()
    publish_date = scrapy.Field()
    category = scrapy.Field()
    tags = scrapy.Field()
    url = scrapy.Field()
    

class ProductItem(scrapy.Item):
    """产品数据项 - 演示电商爬虫Item"""
    name = scrapy.Field()
    price = scrapy.Field()
    original_price = scrapy.Field()
    discount = scrapy.Field()
    brand = scrapy.Field()
    category = scrapy.Field()
    specifications = scrapy.Field()
    reviews_count = scrapy.Field()
    rating = scrapy.Field()
    image_urls = scrapy.Field()
    product_id = scrapy.Field()
    url = scrapy.Field()