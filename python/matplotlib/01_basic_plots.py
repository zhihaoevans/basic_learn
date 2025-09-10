#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Matplotlib 基础绘图示例
演示线图、散点图、柱状图的基本用法
"""

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei', 'Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False

def line_plot_examples():
    """线图示例"""
    print("创建线图示例...")
    
    # 创建数据
    x = np.linspace(0, 10, 100)
    y1 = np.sin(x)
    y2 = np.cos(x)
    y3 = np.sin(x) * np.exp(-x/10)
    
    # 创建子图
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    fig.suptitle('线图示例集合', fontsize=16, fontweight='bold')
    
    # 1. 基础线图
    axes[0, 0].plot(x, y1, label='sin(x)', color='blue', linewidth=2)
    axes[0, 0].plot(x, y2, label='cos(x)', color='red', linewidth=2)
    axes[0, 0].set_title('基础线图')
    axes[0, 0].set_xlabel('X轴')
    axes[0, 0].set_ylabel('Y轴')
    axes[0, 0].legend()
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. 不同线型样式
    axes[0, 1].plot(x, y1, '--', label='虚线', linewidth=2)
    axes[0, 1].plot(x, y2, '-.', label='点划线', linewidth=2)
    axes[0, 1].plot(x, y3, ':', label='点线', linewidth=2)
    axes[0, 1].set_title('不同线型样式')
    axes[0, 1].set_xlabel('X轴')
    axes[0, 1].set_ylabel('Y轴')
    axes[0, 1].legend()
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 标记点的线图
    x_sparse = np.linspace(0, 10, 20)
    y_sparse = np.sin(x_sparse)
    axes[1, 0].plot(x_sparse, y_sparse, 'o-', markersize=6, label='带标记点')
    axes[1, 0].plot(x_sparse, np.cos(x_sparse), 's--', markersize=6, label='方形标记')
    axes[1, 0].set_title('带标记点的线图')
    axes[1, 0].set_xlabel('X轴')
    axes[1, 0].set_ylabel('Y轴')
    axes[1, 0].legend()
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 多条线图对比
    for i in range(5):
        axes[1, 1].plot(x, np.sin(x + i*0.5), label=f'相位偏移 {i*0.5:.1f}', alpha=0.8)
    axes[1, 1].set_title('多条线图对比')
    axes[1, 1].set_xlabel('X轴')
    axes[1, 1].set_ylabel('Y轴')
    axes[1, 1].legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('line_plots.png', dpi=300, bbox_inches='tight')
    plt.show()

def scatter_plot_examples():
    """散点图示例"""
    print("创建散点图示例...")
    
    # 生成随机数据
    np.random.seed(42)
    n = 100
    x = np.random.randn(n)
    y = np.random.randn(n)
    colors = np.random.rand(n)
    sizes = 1000 * np.random.rand(n)
    
    # 创建子图
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    fig.suptitle('散点图示例集合', fontsize=16, fontweight='bold')
    
    # 1. 基础散点图
    axes[0, 0].scatter(x, y, alpha=0.6)
    axes[0, 0].set_title('基础散点图')
    axes[0, 0].set_xlabel('X轴')
    axes[0, 0].set_ylabel('Y轴')
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. 彩色散点图
    scatter = axes[0, 1].scatter(x, y, c=colors, alpha=0.6, cmap='viridis')
    axes[0, 1].set_title('彩色散点图')
    axes[0, 1].set_xlabel('X轴')
    axes[0, 1].set_ylabel('Y轴')
    axes[0, 1].grid(True, alpha=0.3)
    plt.colorbar(scatter, ax=axes[0, 1])
    
    # 3. 不同大小的散点图
    axes[1, 0].scatter(x, y, s=sizes, alpha=0.6, c=colors, cmap='plasma')
    axes[1, 0].set_title('不同大小的散点图')
    axes[1, 0].set_xlabel('X轴')
    axes[1, 0].set_ylabel('Y轴')
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 分类散点图
    # 生成分类数据
    categories = np.random.choice(['类别A', '类别B', '类别C'], n)
    colors_cat = {'类别A': 'red', '类别B': 'blue', '类别C': 'green'}
    
    for category in ['类别A', '类别B', '类别C']:
        mask = categories == category
        axes[1, 1].scatter(x[mask], y[mask], c=colors_cat[category], 
                          label=category, alpha=0.6, s=50)
    
    axes[1, 1].set_title('分类散点图')
    axes[1, 1].set_xlabel('X轴')
    axes[1, 1].set_ylabel('Y轴')
    axes[1, 1].legend()
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('scatter_plots.png', dpi=300, bbox_inches='tight')
    plt.show()

def bar_plot_examples():
    """柱状图示例"""
    print("创建柱状图示例...")
    
    # 创建数据
    categories = ['产品A', '产品B', '产品C', '产品D', '产品E']
    values1 = [23, 45, 56, 78, 32]
    values2 = [34, 25, 67, 45, 28]
    values3 = [12, 35, 23, 56, 45]
    
    x_pos = np.arange(len(categories))
    
    # 创建子图
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    fig.suptitle('柱状图示例集合', fontsize=16, fontweight='bold')
    
    # 1. 基础柱状图
    bars1 = axes[0, 0].bar(categories, values1, color='skyblue', alpha=0.8)
    axes[0, 0].set_title('基础柱状图')
    axes[0, 0].set_xlabel('产品类别')
    axes[0, 0].set_ylabel('销售量')
    axes[0, 0].grid(True, alpha=0.3, axis='y')
    
    # 添加数值标签
    for bar in bars1:
        height = bar.get_height()
        axes[0, 0].text(bar.get_x() + bar.get_width()/2., height + 1,
                       f'{height}', ha='center', va='bottom')
    
    # 2. 水平柱状图
    bars2 = axes[0, 1].barh(categories, values1, color='lightcoral', alpha=0.8)
    axes[0, 1].set_title('水平柱状图')
    axes[0, 1].set_xlabel('销售量')
    axes[0, 1].set_ylabel('产品类别')
    axes[0, 1].grid(True, alpha=0.3, axis='x')
    
    # 3. 分组柱状图
    width = 0.25
    axes[1, 0].bar(x_pos - width, values1, width, label='第一季度', alpha=0.8)
    axes[1, 0].bar(x_pos, values2, width, label='第二季度', alpha=0.8)
    axes[1, 0].bar(x_pos + width, values3, width, label='第三季度', alpha=0.8)
    
    axes[1, 0].set_title('分组柱状图')
    axes[1, 0].set_xlabel('产品类别')
    axes[1, 0].set_ylabel('销售量')
    axes[1, 0].set_xticks(x_pos)
    axes[1, 0].set_xticklabels(categories)
    axes[1, 0].legend()
    axes[1, 0].grid(True, alpha=0.3, axis='y')
    
    # 4. 堆叠柱状图
    axes[1, 1].bar(categories, values1, label='第一季度', alpha=0.8)
    axes[1, 1].bar(categories, values2, bottom=values1, label='第二季度', alpha=0.8)
    axes[1, 1].bar(categories, values3, bottom=np.array(values1) + np.array(values2), 
                  label='第三季度', alpha=0.8)
    
    axes[1, 1].set_title('堆叠柱状图')
    axes[1, 1].set_xlabel('产品类别')
    axes[1, 1].set_ylabel('累计销售量')
    axes[1, 1].legend()
    axes[1, 1].grid(True, alpha=0.3, axis='y')
    
    plt.tight_layout()
    plt.savefig('bar_plots.png', dpi=300, bbox_inches='tight')
    plt.show()

def combined_plot_example():
    """组合图表示例"""
    print("创建组合图表示例...")
    
    # 创建数据
    months = ['1月', '2月', '3月', '4月', '5月', '6月']
    sales = [120, 135, 148, 165, 180, 195]
    profit_margin = [0.15, 0.18, 0.16, 0.20, 0.22, 0.19]
    
    fig, ax1 = plt.subplots(figsize=(10, 6))
    
    # 左侧Y轴 - 柱状图
    color = 'tab:blue'
    ax1.set_xlabel('月份')
    ax1.set_ylabel('销售额 (万元)', color=color)
    bars = ax1.bar(months, sales, color=color, alpha=0.7, label='销售额')
    ax1.tick_params(axis='y', labelcolor=color)
    ax1.grid(True, alpha=0.3)
    
    # 右侧Y轴 - 线图
    ax2 = ax1.twinx()
    color = 'tab:red'
    ax2.set_ylabel('利润率', color=color)
    line = ax2.plot(months, profit_margin, color=color, marker='o', 
                   linewidth=2, markersize=8, label='利润率')
    ax2.tick_params(axis='y', labelcolor=color)
    
    # 添加标题和图例
    plt.title('销售额与利润率组合图表', fontsize=14, fontweight='bold', pad=20)
    
    # 组合图例
    lines1, labels1 = ax1.get_legend_handles_labels()
    lines2, labels2 = ax2.get_legend_handles_labels()
    ax1.legend(lines1 + lines2, labels1 + labels2, loc='upper left')
    
    plt.tight_layout()
    plt.savefig('combined_plot.png', dpi=300, bbox_inches='tight')
    plt.show()

def main():
    """主函数"""
    print("=" * 50)
    print("Matplotlib 基础绘图示例")
    print("=" * 50)
    
    # 执行各种绘图示例
    line_plot_examples()
    scatter_plot_examples()
    bar_plot_examples()
    combined_plot_example()
    
    print("\n所有基础绘图示例已完成！")
    print("生成的图片文件:")
    print("- line_plots.png")
    print("- scatter_plots.png")
    print("- bar_plots.png")
    print("- combined_plot.png")

if __name__ == "__main__":
    main()