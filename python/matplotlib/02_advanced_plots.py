#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Matplotlib 高级绘图示例
演示子图、多轴、3D绘图等高级功能
"""

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.gridspec as gridspec
from matplotlib.patches import Circle, Rectangle, Polygon
import matplotlib.patches as mpatches

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei', 'Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False

def subplot_examples():
    """子图布局示例"""
    print("创建子图布局示例...")
    
    # 示例1: 基础子图布局
    fig, axes = plt.subplots(2, 3, figsize=(15, 10))
    fig.suptitle('基础子图布局示例', fontsize=16, fontweight='bold')
    
    # 生成数据
    x = np.linspace(0, 10, 100)
    
    # 填充子图
    plots_data = [
        (np.sin(x), 'sin(x)', 'blue'),
        (np.cos(x), 'cos(x)', 'red'),
        (np.tan(x), 'tan(x)', 'green'),
        (np.exp(-x/5), 'exp(-x/5)', 'purple'),
        (x**2/50, 'x²/50', 'orange'),
        (np.log(x+1), 'log(x+1)', 'brown')
    ]
    
    for i, (y_data, title, color) in enumerate(plots_data):
        row, col = i // 3, i % 3
        axes[row, col].plot(x, y_data, color=color, linewidth=2)
        axes[row, col].set_title(title)
        axes[row, col].grid(True, alpha=0.3)
        axes[row, col].set_xlabel('X轴')
        axes[row, col].set_ylabel('Y轴')
    
    plt.tight_layout()
    plt.savefig('subplot_basic.png', dpi=300, bbox_inches='tight')
    plt.show()

def gridspec_examples():
    """GridSpec高级布局示例"""
    print("创建GridSpec高级布局示例...")
    
    # 创建复杂的网格布局
    fig = plt.figure(figsize=(12, 10))
    gs = gridspec.GridSpec(3, 3, figure=fig)
    
    # 大图占据左上角2x2区域
    ax1 = fig.add_subplot(gs[0:2, 0:2])
    x = np.linspace(0, 10, 100)
    y1 = np.sin(x)
    y2 = np.cos(x)
    ax1.plot(x, y1, label='sin(x)', linewidth=2)
    ax1.plot(x, y2, label='cos(x)', linewidth=2)
    ax1.set_title('主图区域 (2x2)', fontsize=14, fontweight='bold')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # 右上角小图
    ax2 = fig.add_subplot(gs[0, 2])
    ax2.bar(['A', 'B', 'C'], [1, 3, 2], color=['red', 'green', 'blue'])
    ax2.set_title('柱状图')
    
    # 右中间小图
    ax3 = fig.add_subplot(gs[1, 2])
    theta = np.linspace(0, 2*np.pi, 100)
    ax3.plot(theta, np.sin(theta))
    ax3.set_title('正弦波')
    
    # 底部横跨整行的图
    ax4 = fig.add_subplot(gs[2, :])
    x_scatter = np.random.randn(100)
    y_scatter = np.random.randn(100)
    ax4.scatter(x_scatter, y_scatter, alpha=0.6, c=np.random.rand(100), cmap='viridis')
    ax4.set_title('底部散点图 (横跨整行)', fontsize=14, fontweight='bold')
    ax4.grid(True, alpha=0.3)
    
    plt.suptitle('GridSpec 复杂布局示例', fontsize=16, fontweight='bold')
    plt.tight_layout()
    plt.savefig('gridspec_layout.png', dpi=300, bbox_inches='tight')
    plt.show()

def multiple_axes_examples():
    """多轴绘图示例"""
    print("创建多轴绘图示例...")
    
    fig, ax1 = plt.subplots(figsize=(12, 8))
    
    # 生成数据
    months = np.arange(1, 13)
    temperature = 15 + 10 * np.sin((months - 3) * np.pi / 6)  # 温度数据
    rainfall = 50 + 30 * np.random.rand(12)  # 降雨量数据
    humidity = 60 + 20 * np.sin((months - 1) * np.pi / 6)  # 湿度数据
    
    # 第一个Y轴 - 温度 (线图)
    color1 = 'tab:red'
    ax1.set_xlabel('月份', fontsize=12)
    ax1.set_ylabel('温度 (°C)', color=color1, fontsize=12)
    line1 = ax1.plot(months, temperature, color=color1, marker='o', 
                     linewidth=2, markersize=6, label='温度')
    ax1.tick_params(axis='y', labelcolor=color1)
    ax1.grid(True, alpha=0.3)
    
    # 第二个Y轴 - 降雨量 (柱状图)
    ax2 = ax1.twinx()
    color2 = 'tab:blue'
    ax2.set_ylabel('降雨量 (mm)', color=color2, fontsize=12)
    bars = ax2.bar(months, rainfall, alpha=0.6, color=color2, 
                   width=0.6, label='降雨量')
    ax2.tick_params(axis='y', labelcolor=color2)
    
    # 第三个Y轴 - 湿度 (线图)
    ax3 = ax1.twinx()
    ax3.spines['right'].set_position(('outward', 60))  # 移动第三个轴
    color3 = 'tab:green'
    ax3.set_ylabel('湿度 (%)', color=color3, fontsize=12)
    line3 = ax3.plot(months, humidity, color=color3, marker='s', 
                     linewidth=2, markersize=6, linestyle='--', label='湿度')
    ax3.tick_params(axis='y', labelcolor=color3)
    
    # 设置标题和图例
    plt.title('多轴气象数据可视化', fontsize=16, fontweight='bold', pad=20)
    
    # 组合图例
    lines1, labels1 = ax1.get_legend_handles_labels()
    lines2, labels2 = ax2.get_legend_handles_labels()
    lines3, labels3 = ax3.get_legend_handles_labels()
    ax1.legend(lines1 + lines2 + lines3, labels1 + labels2 + labels3, 
               loc='upper left', bbox_to_anchor=(0.02, 0.98))
    
    # 设置X轴标签
    month_names = ['1月', '2月', '3月', '4月', '5月', '6月',
                   '7月', '8月', '9月', '10月', '11月', '12月']
    ax1.set_xticks(months)
    ax1.set_xticklabels(month_names, rotation=45)
    
    plt.tight_layout()
    plt.savefig('multiple_axes.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_3d_examples():
    """3D绘图示例"""
    print("创建3D绘图示例...")
    
    # 创建2x2的3D子图
    fig = plt.figure(figsize=(15, 12))
    fig.suptitle('3D绘图示例集合', fontsize=16, fontweight='bold')
    
    # 1. 3D线图
    ax1 = fig.add_subplot(221, projection='3d')
    t = np.linspace(0, 4*np.pi, 100)
    x1 = np.sin(t)
    y1 = np.cos(t)
    z1 = t
    ax1.plot(x1, y1, z1, 'b-', linewidth=2, label='螺旋线')
    ax1.set_title('3D螺旋线')
    ax1.set_xlabel('X轴')
    ax1.set_ylabel('Y轴')
    ax1.set_zlabel('Z轴')
    ax1.legend()
    
    # 2. 3D散点图
    ax2 = fig.add_subplot(222, projection='3d')
    n = 100
    x2 = np.random.randn(n)
    y2 = np.random.randn(n)
    z2 = np.random.randn(n)
    colors = np.random.rand(n)
    ax2.scatter(x2, y2, z2, c=colors, cmap='viridis', s=50, alpha=0.8)
    ax2.set_title('3D散点图')
    ax2.set_xlabel('X轴')
    ax2.set_ylabel('Y轴')
    ax2.set_zlabel('Z轴')
    
    # 3. 3D表面图
    ax3 = fig.add_subplot(223, projection='3d')
    x3 = np.linspace(-5, 5, 50)
    y3 = np.linspace(-5, 5, 50)
    X3, Y3 = np.meshgrid(x3, y3)
    Z3 = np.sin(np.sqrt(X3**2 + Y3**2))
    surf = ax3.plot_surface(X3, Y3, Z3, cmap='coolwarm', alpha=0.8)
    ax3.set_title('3D表面图')
    ax3.set_xlabel('X轴')
    ax3.set_ylabel('Y轴')
    ax3.set_zlabel('Z轴')
    fig.colorbar(surf, ax=ax3, shrink=0.5)
    
    # 4. 3D等高线图
    ax4 = fig.add_subplot(224, projection='3d')
    x4 = np.linspace(-3, 3, 30)
    y4 = np.linspace(-3, 3, 30)
    X4, Y4 = np.meshgrid(x4, y4)
    Z4 = X4**2 + Y4**2
    contour = ax4.contour(X4, Y4, Z4, levels=10, cmap='plasma')
    ax4.set_title('3D等高线图')
    ax4.set_xlabel('X轴')
    ax4.set_ylabel('Y轴')
    ax4.set_zlabel('Z轴')
    
    plt.tight_layout()
    plt.savefig('3d_plots.png', dpi=300, bbox_inches='tight')
    plt.show()

def inset_axes_examples():
    """嵌入子图示例"""
    print("创建嵌入子图示例...")
    
    fig, ax = plt.subplots(figsize=(10, 8))
    
    # 主图数据
    x = np.linspace(0, 10, 1000)
    y = np.sin(x) * np.exp(-x/10)
    
    ax.plot(x, y, 'b-', linewidth=2, label='衰减正弦波')
    ax.set_xlabel('时间 (s)')
    ax.set_ylabel('振幅')
    ax.set_title('带嵌入放大图的信号分析', fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3)
    ax.legend()
    
    # 创建嵌入的放大图
    from mpl_toolkits.axes_grid1.inset_locator import inset_axes
    axins = inset_axes(ax, width="40%", height="40%", loc='upper right')
    
    # 放大特定区域 (x=2到x=4)
    x_zoom = x[(x >= 2) & (x <= 4)]
    y_zoom = y[(x >= 2) & (x <= 4)]
    axins.plot(x_zoom, y_zoom, 'r-', linewidth=2)
    axins.set_xlim(2, 4)
    axins.set_ylim(y_zoom.min()*1.1, y_zoom.max()*1.1)
    axins.grid(True, alpha=0.3)
    axins.set_title('放大区域', fontsize=10)
    
    # 添加连接线
    from mpl_toolkits.axes_grid1.inset_locator import mark_inset
    mark_inset(ax, axins, loc1=2, loc2=4, fc="none", ec="0.5")
    
    plt.tight_layout()
    plt.savefig('inset_axes.png', dpi=300, bbox_inches='tight')
    plt.show()

def polar_plot_examples():
    """极坐标图示例"""
    print("创建极坐标图示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(12, 10), subplot_kw=dict(projection='polar'))
    fig.suptitle('极坐标图示例集合', fontsize=16, fontweight='bold')
    
    # 1. 基础极坐标图
    theta1 = np.linspace(0, 2*np.pi, 100)
    r1 = 1 + 0.5 * np.sin(5*theta1)
    axes[0, 0].plot(theta1, r1, 'b-', linewidth=2)
    axes[0, 0].set_title('花瓣图案', pad=20)
    axes[0, 0].grid(True)
    
    # 2. 极坐标散点图
    theta2 = np.random.uniform(0, 2*np.pi, 100)
    r2 = np.random.uniform(0, 1, 100)
    colors = theta2
    axes[0, 1].scatter(theta2, r2, c=colors, cmap='hsv', alpha=0.7, s=50)
    axes[0, 1].set_title('极坐标散点图', pad=20)
    axes[0, 1].grid(True)
    
    # 3. 极坐标柱状图
    theta3 = np.linspace(0, 2*np.pi, 8, endpoint=False)
    r3 = np.random.uniform(0.5, 1.5, 8)
    width = 2*np.pi / 8
    axes[1, 0].bar(theta3, r3, width=width, alpha=0.7, 
                   color=plt.cm.viridis(r3/max(r3)))
    axes[1, 0].set_title('极坐标柱状图', pad=20)
    axes[1, 0].grid(True)
    
    # 4. 螺旋图
    theta4 = np.linspace(0, 6*np.pi, 200)
    r4 = theta4 / (2*np.pi)
    axes[1, 1].plot(theta4, r4, 'r-', linewidth=2)
    axes[1, 1].set_title('阿基米德螺旋', pad=20)
    axes[1, 1].grid(True)
    
    plt.tight_layout()
    plt.savefig('polar_plots.png', dpi=300, bbox_inches='tight')
    plt.show()

def main():
    """主函数"""
    print("=" * 50)
    print("Matplotlib 高级绘图示例")
    print("=" * 50)
    
    # 执行各种高级绘图示例
    subplot_examples()
    gridspec_examples()
    multiple_axes_examples()
    plot_3d_examples()
    inset_axes_examples()
    polar_plot_examples()
    
    print("\n所有高级绘图示例已完成！")
    print("生成的图片文件:")
    print("- subplot_basic.png")
    print("- gridspec_layout.png")
    print("- multiple_axes.png")
    print("- 3d_plots.png")
    print("- inset_axes.png")
    print("- polar_plots.png")

if __name__ == "__main__":
    main()