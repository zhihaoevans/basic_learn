# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html

# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import json
import sqlite3
import logging
from scrapy.exceptions import DropItem
from scrapy.pipelines.images import ImagesPipeline
import requests


class ValidationPipeline:
    """数据验证管道 - 验证必填字段"""
    
    def process_item(self, item, spider):
        adapter = ItemAdapter(item)
        
        # 检查必填字段
        if not adapter.get('title') and not adapter.get('text'):
            raise DropItem(f"Missing title or text in {item}")
            
        # 数据清洗
        if adapter.get('price'):
            # 清理价格数据
            price = adapter['price']
            if isinstance(price, str):
                # 移除货币符号和空格
                price = price.replace('$', '').replace('£', '').replace('€', '').strip()
                try:
                    adapter['price'] = float(price)
                except ValueError:
                    spider.logger.warning(f"Invalid price format: {price}")
                    
        return item


class DuplicatesPipeline:
    """去重管道 - 基于URL或标题去重"""
    
    def __init__(self):
        self.ids_seen = set()
        
    def process_item(self, item, spider):
        adapter = ItemAdapter(item)
        
        # 使用URL或标题作为唯一标识
        item_id = adapter.get('url') or adapter.get('title')
        
        if item_id in self.ids_seen:
            raise DropItem(f"Duplicate item found: {item_id}")
        else:
            self.ids_seen.add(item_id)
            return item


class JsonWriterPipeline:
    """JSON写入管道 - 将数据保存为JSON文件"""
    
    def open_spider(self, spider):
        self.file = open(f'{spider.name}_items.json', 'w', encoding='utf-8')
        self.file.write('[')
        self.first_item = True
        
    def close_spider(self, spider):
        self.file.write(']')
        self.file.close()
        
    def process_item(self, item, spider):
        if not self.first_item:
            self.file.write(',')
        else:
            self.first_item = False
            
        line = json.dumps(ItemAdapter(item).asdict(), ensure_ascii=False, indent=2)
        self.file.write(line)
        return item


class DatabasePipeline:
    """数据库管道 - 将数据保存到SQLite数据库"""
    
    def __init__(self):
        self.connection = None
        self.cursor = None
        
    def open_spider(self, spider):
        self.connection = sqlite3.connect(f'{spider.name}_data.db')
        self.cursor = self.connection.cursor()
        
        # 创建表格
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS items (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT,
                content TEXT,
                author TEXT,
                price REAL,
                url TEXT UNIQUE,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        ''')
        self.connection.commit()
        
    def close_spider(self, spider):
        if self.connection:
            self.connection.close()
            
    def process_item(self, item, spider):
        adapter = ItemAdapter(item)
        
        try:
            # 插入数据
            self.cursor.execute('''
                INSERT OR REPLACE INTO items (title, content, author, price, url)
                VALUES (?, ?, ?, ?, ?)
            ''', (
                adapter.get('title') or adapter.get('text', '')[:100],
                adapter.get('content') or adapter.get('text', ''),
                adapter.get('author', ''),
                adapter.get('price'),
                adapter.get('url', '')
            ))
            self.connection.commit()
            spider.logger.info(f"Item saved to database: {adapter.get('title', 'Unknown')}")
            
        except sqlite3.Error as e:
            spider.logger.error(f"Database error: {e}")
            
        return item


class CustomImagesPipeline(ImagesPipeline):
    """自定义图片管道 - 下载和处理图片"""
    
    def get_media_requests(self, item, info):
        adapter = ItemAdapter(item)
        for image_url in adapter.get('image_urls', []):
            yield scrapy.Request(image_url)
            
    def item_completed(self, results, item, info):
        adapter = ItemAdapter(item)
        image_paths = [x['path'] for ok, x in results if ok]
        adapter['images'] = image_paths
        return item


class StatsPipeline:
    """统计管道 - 收集爬取统计信息"""
    
    def __init__(self):
        self.stats = {
            'items_count': 0,
            'items_by_type': {},
            'errors_count': 0
        }
        
    def process_item(self, item, spider):
        self.stats['items_count'] += 1
        
        item_type = type(item).__name__
        self.stats['items_by_type'][item_type] = self.stats['items_by_type'].get(item_type, 0) + 1
        
        spider.logger.info(f"Processed {self.stats['items_count']} items so far")
        return item
        
    def close_spider(self, spider):
        spider.logger.info(f"Final stats: {self.stats}")


class EmailNotificationPipeline:
    """邮件通知管道 - 在特定条件下发送通知"""
    
    def __init__(self):
        self.high_value_threshold = 1000  # 高价值商品阈值
        
    def process_item(self, item, spider):
        adapter = ItemAdapter(item)
        
        # 如果是高价值商品，记录日志（实际应用中可以发送邮件）
        price = adapter.get('price')
        if price and isinstance(price, (int, float)) and price > self.high_value_threshold:
            spider.logger.warning(
                f"High value item detected: {adapter.get('title', 'Unknown')} - ${price}"
            )
            
        return item