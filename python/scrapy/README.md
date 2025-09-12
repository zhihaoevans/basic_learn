# Scrapy 完整示例项目

这个项目演示了 Python Scrapy 库的所有主要用法和功能。包含了从基础爬虫到高级功能的完整示例。

## 项目结构

```
scrapy_examples/
├── scrapy.cfg              # Scrapy 配置文件
├── README.md              # 项目说明文档
├── requirements.txt       # 依赖包列表
└── scrapy_examples/       # 主要代码目录
    ├── __init__.py
    ├── settings.py        # 项目设置
    ├── items.py          # 数据项定义
    ├── pipelines.py      # 数据处理管道
    ├── middlewares.py    # 中间件
    ├── extensions.py     # 扩展
    └── spiders/          # 爬虫目录
        ├── __init__.py
        ├── quotes_spider.py     # 基础爬虫示例
        ├── books_spider.py      # 复杂数据提取示例
        └── advanced_spider.py   # 高级功能示例
```

## 安装依赖

```bash
pip install scrapy
pip install itemloaders
pip install w3lib
pip install psutil  # 用于内存监控扩展
```

## 功能演示

### 1. 基础爬虫功能

#### 1.1 简单网页抓取 (`quotes_spider.py`)

**QuotesSpider** - 演示基本的网页抓取功能：

```bash
# 运行基础爬虫
scrapy crawl quotes

# 保存为JSON文件
scrapy crawl quotes -o quotes.json

# 保存为CSV文件
scrapy crawl quotes -o quotes.csv
```

**功能特点：**
- CSS选择器和XPath使用
- 数据提取和Item使用
- 分页处理
- 自定义请求头和元数据

#### 1.2 JavaScript渲染页面 (`QuotesJSSpider`)

```bash
scrapy crawl quotes_js
```

**功能特点：**
- 处理JavaScript渲染的页面
- 动态内容加载

#### 1.3 API数据抓取 (`QuotesAPISpider`)

```bash
scrapy crawl quotes_api
```

**功能特点：**
- JSON API数据抓取
- API分页处理
- 请求头设置

### 2. 复杂数据提取 (`books_spider.py`)

#### 2.1 书籍信息爬虫 (`BooksSpider`)

```bash
scrapy crawl books
```

**功能特点：**
- ItemLoader使用
- 复杂数据清洗和处理
- 图片下载
- 详情页面抓取
- 数据库存储

#### 2.2 分类爬虫 (`BooksCategorySpider`)

```bash
scrapy crawl books_category
```

**功能特点：**
- 分类页面处理
- 动态URL生成
- 条件过滤

#### 2.3 搜索功能 (`BooksSearchSpider`)

```bash
scrapy crawl books_search -a query="python"
```

**功能特点：**
- 搜索表单提交
- 动态参数传递

### 3. 高级功能 (`advanced_spider.py`)

#### 3.1 登录爬虫 (`LoginSpider`)

```bash
scrapy crawl login_spider
```

**功能特点：**
- 表单登录
- Session管理
- Cookie处理
- 登录后数据抓取

#### 3.2 AJAX请求 (`AjaxSpider`)

```bash
scrapy crawl ajax_spider
```

**功能特点：**
- AJAX请求处理
- JSON数据解析
- 动态内容加载

#### 3.3 文件下载 (`FileDownloadSpider`)

```bash
scrapy crawl file_download
```

**功能特点：**
- 文件下载
- 二进制数据处理
- 文件保存

#### 3.4 代理使用 (`ProxySpider`)

```bash
scrapy crawl proxy_spider
```

**功能特点：**
- 代理设置
- IP轮换
- 代理验证

#### 3.5 Cookie处理 (`CookieSpider`)

```bash
scrapy crawl cookie_spider
```

**功能特点：**
- Cookie设置和获取
- Session管理
- 状态保持

#### 3.6 请求头处理 (`HeadersSpider`)

```bash
scrapy crawl headers_spider
```

**功能特点：**
- 自定义请求头
- User-Agent设置
- Referer处理

#### 3.7 错误处理 (`ErrorHandlingSpider`)

```bash
scrapy crawl error_handling
```

**功能特点：**
- 异常处理
- 重试机制
- 错误日志
- 降级处理

## 数据处理管道 (Pipelines)

### 1. 数据验证管道 (`ValidationPipeline`)
- 验证必填字段
- 数据清洗和格式化

### 2. 去重管道 (`DuplicatesPipeline`)
- 基于URL或标题去重
- 防止重复数据

### 3. JSON写入管道 (`JsonWriterPipeline`)
- 将数据保存为JSON文件
- 格式化输出

### 4. 数据库管道 (`DatabasePipeline`)
- SQLite数据库存储
- 自动创建表结构

### 5. 图片管道 (`CustomImagesPipeline`)
- 图片下载和处理
- 自定义图片存储

### 6. 统计管道 (`StatsPipeline`)
- 收集爬取统计信息
- 实时监控

### 7. 邮件通知管道 (`EmailNotificationPipeline`)
- 特定条件下发送通知
- 高价值商品提醒

## 中间件 (Middlewares)

### 1. 用户代理轮换 (`UserAgentMiddleware`)
- 随机User-Agent
- 防止被识别

### 2. 代理中间件 (`ProxyMiddleware`)
- 代理IP轮换
- 突破IP限制

### 3. 自定义重试 (`CustomRetryMiddleware`)
- 智能重试机制
- 错误处理优化

### 4. Cookie处理 (`CookieMiddleware`)
- Cookie管理
- 状态保持

### 5. JavaScript渲染 (`JavaScriptMiddleware`)
- JS页面处理标记
- 动态内容支持

### 6. 缓存中间件 (`CacheMiddleware`)
- 响应缓存
- 提高效率

## 扩展 (Extensions)

### 1. 自定义统计 (`CustomStatsExtension`)
- 详细统计信息
- 性能监控
- 统计报告生成

### 2. 内存监控 (`MemoryUsageExtension`)
- 内存使用监控
- 内存泄漏检测

### 3. 进度监控 (`ProgressExtension`)
- 实时进度显示
- 爬取状态跟踪

### 4. 邮件通知 (`EmailNotificationExtension`)
- 爬虫完成通知
- 错误报警

### 5. 自动限速 (`AutoThrottleExtension`)
- 智能限速
- 自适应调整

## 数据项 (Items)

### 1. QuoteItem - 引用数据
- 文本内容
- 作者信息
- 标签列表

### 2. BookItem - 书籍数据
- 标题、价格、库存
- 评分、描述
- 图片URL
- 数据处理器

### 3. NewsItem - 新闻数据
- 标题、内容、作者
- 发布日期、分类
- 标签、URL

### 4. ProductItem - 产品数据
- 商品信息
- 价格、折扣
- 品牌、规格
- 评价数据

## 配置说明 (`settings.py`)

### 基础设置
- `BOT_NAME`: 爬虫名称
- `ROBOTSTXT_OBEY`: 遵守robots.txt
- `DOWNLOAD_DELAY`: 下载延迟
- `CONCURRENT_REQUESTS`: 并发请求数

### 中间件配置
- `SPIDER_MIDDLEWARES`: Spider中间件
- `DOWNLOADER_MIDDLEWARES`: 下载器中间件

### 管道配置
- `ITEM_PIPELINES`: 数据处理管道
- 优先级设置

### 扩展配置
- `EXTENSIONS`: 扩展列表
- 自定义扩展

### 缓存设置
- `HTTPCACHE_ENABLED`: 启用缓存
- `HTTPCACHE_EXPIRATION_SECS`: 缓存过期时间

### 自动限速
- `AUTOTHROTTLE_ENABLED`: 启用自动限速
- `AUTOTHROTTLE_START_DELAY`: 初始延迟
- `AUTOTHROTTLE_MAX_DELAY`: 最大延迟

## 运行示例

### 1. 基本运行
```bash
# 列出所有爬虫
scrapy list

# 运行特定爬虫
scrapy crawl quotes

# 查看爬虫信息
scrapy crawl quotes --help
```

### 2. 输出格式
```bash
# JSON格式
scrapy crawl quotes -o output.json

# CSV格式
scrapy crawl quotes -o output.csv

# XML格式
scrapy crawl quotes -o output.xml

# 自定义格式
scrapy crawl quotes -o output.jl -t jsonlines
```

### 3. 设置覆盖
```bash
# 覆盖设置
scrapy crawl quotes -s DOWNLOAD_DELAY=3

# 多个设置
scrapy crawl quotes -s DOWNLOAD_DELAY=3 -s CONCURRENT_REQUESTS=1
```

### 4. 日志级别
```bash
# 设置日志级别
scrapy crawl quotes -L INFO
scrapy crawl quotes -L DEBUG
scrapy crawl quotes -L ERROR
```

### 5. 传递参数
```bash
# 传递参数给爬虫
scrapy crawl books_search -a query="python programming"
scrapy crawl books_search -a query="web scraping" -a max_pages=5
```

## 调试技巧

### 1. Scrapy Shell
```bash
# 启动交互式shell
scrapy shell "http://quotes.toscrape.com"

# 在shell中测试选择器
>>> response.css('div.quote span.text::text').getall()
>>> response.xpath('//span[@class="text"]/text()').getall()
```

### 2. 日志调试
```python
# 在爬虫中添加日志
self.logger.info('Processing page: %s', response.url)
self.logger.debug('Found %d quotes', len(quotes))
self.logger.warning('No quotes found on page')
self.logger.error('Failed to parse page: %s', response.url)
```

### 3. 断点调试
```python
# 添加断点
import pdb; pdb.set_trace()

# 或使用ipdb（需要安装）
import ipdb; ipdb.set_trace()
```

## 性能优化

### 1. 并发设置
```python
# settings.py
CONCURRENT_REQUESTS = 32
CONCURRENT_REQUESTS_PER_DOMAIN = 16
CONCURRENT_REQUESTS_PER_IP = 16
```

### 2. 下载延迟
```python
# 固定延迟
DOWNLOAD_DELAY = 3

# 随机延迟
RANDOMIZE_DOWNLOAD_DELAY = 0.5
```

### 3. 自动限速
```python
AUTOTHROTTLE_ENABLED = True
AUTOTHROTTLE_START_DELAY = 1
AUTOTHROTTLE_MAX_DELAY = 60
AUTOTHROTTLE_TARGET_CONCURRENCY = 1.0
```

### 4. 缓存优化
```python
HTTPCACHE_ENABLED = True
HTTPCACHE_EXPIRATION_SECS = 3600
HTTPCACHE_DIR = 'httpcache'
```

## 最佳实践

### 1. 遵守网站规则
- 检查 robots.txt
- 设置合理的延迟
- 不要过度请求

### 2. 错误处理
- 使用 errback 处理错误
- 实现重试机制
- 记录详细日志

### 3. 数据质量
- 验证数据完整性
- 去重处理
- 数据清洗

### 4. 监控和维护
- 监控爬虫状态
- 定期检查数据质量
- 及时处理异常

## 常见问题

### 1. 反爬虫对策
- 使用代理IP
- 轮换User-Agent
- 模拟人类行为
- 处理验证码

### 2. JavaScript页面
- 使用Splash
- 集成Selenium
- 分析AJAX请求

### 3. 性能问题
- 优化选择器
- 减少内存使用
- 合理设置并发

### 4. 数据存储
- 选择合适的存储方式
- 处理大量数据
- 数据备份

## 扩展阅读

- [Scrapy官方文档](https://docs.scrapy.org/)
- [Scrapy最佳实践](https://docs.scrapy.org/en/latest/topics/practices.html)
- [反爬虫技术](https://docs.scrapy.org/en/latest/topics/avoiding-getting-banned.html)
- [部署指南](https://docs.scrapy.org/en/latest/topics/deploy.html)

## 许可证

本项目仅用于学习和演示目的。请在使用时遵守相关网站的使用条款和法律法规。