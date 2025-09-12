#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scrapy示例运行脚本

这个脚本提供了一个简单的方式来运行所有的Scrapy示例爬虫。
可以选择运行单个爬虫或所有爬虫。
"""

import os
import sys
import subprocess
import time
from pathlib import Path


class ScrapyRunner:
    """Scrapy爬虫运行器"""
    
    def __init__(self):
        self.spiders = {
            'quotes': {
                'name': 'quotes',
                'description': '基础爬虫 - 抓取名言网站',
                'output': 'quotes.json'
            },
            'quotes_js': {
                'name': 'quotes_js',
                'description': 'JavaScript页面爬虫',
                'output': 'quotes_js.json'
            },
            'quotes_api': {
                'name': 'quotes_api',
                'description': 'API数据爬虫',
                'output': 'quotes_api.json'
            },
            'books': {
                'name': 'books',
                'description': '书籍信息爬虫 - 复杂数据提取',
                'output': 'books.json'
            },
            'books_category': {
                'name': 'books_category',
                'description': '分类书籍爬虫',
                'output': 'books_category.json'
            },
            'login_spider': {
                'name': 'login_spider',
                'description': '登录爬虫示例',
                'output': 'login_data.json'
            },
            'ajax_spider': {
                'name': 'ajax_spider',
                'description': 'AJAX请求爬虫',
                'output': 'ajax_data.json'
            },
            'file_download': {
                'name': 'file_download',
                'description': '文件下载爬虫',
                'output': 'downloads.json'
            },
            'proxy_spider': {
                'name': 'proxy_spider',
                'description': '代理使用示例',
                'output': 'proxy_test.json'
            },
            'cookie_spider': {
                'name': 'cookie_spider',
                'description': 'Cookie处理示例',
                'output': 'cookie_test.json'
            },
            'headers_spider': {
                'name': 'headers_spider',
                'description': '请求头处理示例',
                'output': 'headers_test.json'
            },
            'error_handling': {
                'name': 'error_handling',
                'description': '错误处理示例',
                'output': 'error_test.json'
            }
        }
        
    def list_spiders(self):
        """列出所有可用的爬虫"""
        print("\n=== 可用的Scrapy爬虫示例 ===")
        print(f"{'序号':<4} {'爬虫名称':<20} {'描述':<30}")
        print("-" * 60)
        
        for i, (key, spider) in enumerate(self.spiders.items(), 1):
            print(f"{i:<4} {spider['name']:<20} {spider['description']:<30}")
        
        print("\n0    all                  运行所有爬虫")
        print("-" * 60)
    
    def run_spider(self, spider_name, output_file=None, extra_args=None):
        """运行单个爬虫"""
        print(f"\n🚀 正在运行爬虫: {spider_name}")
        
        # 构建命令
        cmd = ['scrapy', 'crawl', spider_name]
        
        # 添加输出文件
        if output_file:
            cmd.extend(['-o', output_file])
        
        # 添加额外参数
        if extra_args:
            cmd.extend(extra_args)
        
        # 添加日志级别
        cmd.extend(['-L', 'INFO'])
        
        print(f"执行命令: {' '.join(cmd)}")
        
        try:
            # 记录开始时间
            start_time = time.time()
            
            # 运行爬虫
            result = subprocess.run(cmd, capture_output=True, text=True, timeout=300)
            
            # 计算运行时间
            duration = time.time() - start_time
            
            if result.returncode == 0:
                print(f"✅ 爬虫 {spider_name} 运行成功! 耗时: {duration:.2f}秒")
                if output_file and os.path.exists(output_file):
                    file_size = os.path.getsize(output_file)
                    print(f"📁 输出文件: {output_file} (大小: {file_size} 字节)")
            else:
                print(f"❌ 爬虫 {spider_name} 运行失败!")
                print(f"错误信息: {result.stderr}")
                
            return result.returncode == 0
            
        except subprocess.TimeoutExpired:
            print(f"⏰ 爬虫 {spider_name} 运行超时 (5分钟)")
            return False
        except Exception as e:
            print(f"💥 运行爬虫时发生异常: {e}")
            return False
    
    def run_all_spiders(self):
        """运行所有爬虫"""
        print("\n🎯 开始运行所有爬虫示例...")
        
        success_count = 0
        total_count = len(self.spiders)
        
        for spider_key, spider_info in self.spiders.items():
            spider_name = spider_info['name']
            output_file = spider_info['output']
            
            # 为某些爬虫添加特殊参数
            extra_args = []
            if spider_name == 'books_search':
                extra_args = ['-a', 'query=python']
            
            success = self.run_spider(spider_name, output_file, extra_args)
            if success:
                success_count += 1
            
            # 在爬虫之间添加短暂延迟
            time.sleep(2)
        
        print(f"\n📊 运行完成! 成功: {success_count}/{total_count}")
    
    def interactive_mode(self):
        """交互式模式"""
        while True:
            self.list_spiders()
            
            try:
                choice = input("\n请选择要运行的爬虫 (输入序号或爬虫名称，q退出): ").strip()
                
                if choice.lower() in ['q', 'quit', 'exit']:
                    print("👋 再见!")
                    break
                
                if choice == '0' or choice.lower() == 'all':
                    self.run_all_spiders()
                    continue
                
                # 尝试按序号选择
                if choice.isdigit():
                    spider_index = int(choice) - 1
                    if 0 <= spider_index < len(self.spiders):
                        spider_key = list(self.spiders.keys())[spider_index]
                        spider_info = self.spiders[spider_key]
                        self.run_spider(spider_info['name'], spider_info['output'])
                    else:
                        print("❌ 无效的序号!")
                # 尝试按名称选择
                elif choice in self.spiders:
                    spider_info = self.spiders[choice]
                    self.run_spider(spider_info['name'], spider_info['output'])
                else:
                    # 直接作为爬虫名称
                    spider_names = [info['name'] for info in self.spiders.values()]
                    if choice in spider_names:
                        self.run_spider(choice, f"{choice}.json")
                    else:
                        print("❌ 未找到指定的爬虫!")
                        
            except KeyboardInterrupt:
                print("\n\n👋 用户中断，再见!")
                break
            except Exception as e:
                print(f"💥 发生错误: {e}")


def main():
    """主函数"""
    print("🕷️  Scrapy 示例爬虫运行器")
    print("=" * 50)
    
    # 检查是否在正确的目录
    if not os.path.exists('scrapy.cfg'):
        print("❌ 错误: 请在Scrapy项目根目录下运行此脚本!")
        print("当前目录应该包含 scrapy.cfg 文件")
        sys.exit(1)
    
    # 检查Scrapy是否安装
    try:
        subprocess.run(['scrapy', '--version'], capture_output=True, check=True)
    except (subprocess.CalledProcessError, FileNotFoundError):
        print("❌ 错误: 未找到Scrapy命令!")
        print("请先安装Scrapy: pip install scrapy")
        sys.exit(1)
    
    runner = ScrapyRunner()
    
    # 检查命令行参数
    if len(sys.argv) > 1:
        spider_name = sys.argv[1]
        
        if spider_name == 'list':
            runner.list_spiders()
        elif spider_name == 'all':
            runner.run_all_spiders()
        else:
            # 运行指定的爬虫
            output_file = f"{spider_name}.json"
            extra_args = sys.argv[2:] if len(sys.argv) > 2 else None
            runner.run_spider(spider_name, output_file, extra_args)
    else:
        # 交互式模式
        runner.interactive_mode()


if __name__ == '__main__':
    main()