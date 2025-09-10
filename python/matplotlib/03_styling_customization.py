#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Matplotlib 样式和自定义示例
演示颜色、标记、字体、主题等样式定制功能
"""

import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors as mcolors
import matplotlib.patches as patches
from matplotlib import cm

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei', 'Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False

def color_examples():
    """颜色使用示例"""
    print("创建颜色使用示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('颜色使用示例集合', fontsize=16, fontweight='bold')
    
    x = np.linspace(0, 10, 100)
    
    # 1. 基础颜色命名
    basic_colors = ['red', 'blue', 'green', 'orange', 'purple', 'brown', 'pink', 'gray']
    for i, color in enumerate(basic_colors):
        y = np.sin(x + i*0.5)
        axes[0, 0].plot(x, y, color=color, label=color, linewidth=2)
    axes[0, 0].set_title('基础颜色命名')
    axes[0, 0].legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. 十六进制颜色
    hex_colors = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4', '#FFEAA7', '#DDA0DD']
    for i, color in enumerate(hex_colors):
        y = np.cos(x + i*0.5)
        axes[0, 1].plot(x, y, color=color, label=color, linewidth=2)
    axes[0, 1].set_title('十六进制颜色')
    axes[0, 1].legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. RGB颜色
    rgb_colors = [(1, 0, 0), (0, 1, 0), (0, 0, 1), (1, 1, 0), (1, 0, 1), (0, 1, 1)]
    for i, color in enumerate(rgb_colors):
        y = np.sin(x + i*0.3) * np.exp(-x/10)
        axes[1, 0].plot(x, y, color=color, label=f'RGB{color}', linewidth=2)
    axes[1, 0].set_title('RGB颜色')
    axes[1, 0].legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 颜色映射
    y_data = [np.sin(x + i*0.2) for i in range(10)]
    colors = cm.viridis(np.linspace(0, 1, 10))
    for i, (y, color) in enumerate(zip(y_data, colors)):
        axes[1, 1].plot(x, y, color=color, label=f'线条{i+1}', linewidth=2)
    axes[1, 1].set_title('Viridis颜色映射')
    axes[1, 1].legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('color_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def marker_line_style_examples():
    """标记和线型样式示例"""
    print("创建标记和线型样式示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('标记和线型样式示例', fontsize=16, fontweight='bold')
    
    x = np.linspace(0, 10, 20)
    
    # 1. 不同标记样式
    markers = ['o', 's', '^', 'v', '<', '>', 'D', 'p', '*', 'h']
    for i, marker in enumerate(markers):
        y = i + np.sin(x)
        axes[0, 0].plot(x, y, marker=marker, label=f'标记: {marker}', 
                       markersize=8, linewidth=1.5)
    axes[0, 0].set_title('不同标记样式')
    axes[0, 0].legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. 不同线型样式
    line_styles = ['-', '--', '-.', ':', (0, (3, 1, 1, 1)), (0, (5, 5)), (0, (1, 1))]
    style_names = ['实线', '虚线', '点划线', '点线', '自定义1', '自定义2', '自定义3']
    for i, (style, name) in enumerate(zip(line_styles, style_names)):
        y = np.sin(x + i*0.5)
        axes[0, 1].plot(x, y, linestyle=style, label=name, linewidth=2)
    axes[0, 1].set_title('不同线型样式')
    axes[0, 1].legend()
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 标记大小和颜色变化
    y = np.sin(x)
    sizes = np.linspace(20, 200, len(x))
    colors = np.linspace(0, 1, len(x))
    scatter = axes[1, 0].scatter(x, y, s=sizes, c=colors, cmap='plasma', 
                                alpha=0.7, edgecolors='black', linewidth=1)
    axes[1, 0].set_title('变化的标记大小和颜色')
    axes[1, 0].grid(True, alpha=0.3)
    plt.colorbar(scatter, ax=axes[1, 0])
    
    # 4. 组合样式
    styles = [('o-', 'red', '实线+圆点'),
              ('s--', 'blue', '虚线+方形'),
              ('^-.', 'green', '点划线+三角'),
              ('D:', 'purple', '点线+菱形')]
    
    for i, (style, color, label) in enumerate(styles):
        y = np.cos(x + i*0.8)
        axes[1, 1].plot(x, y, style, color=color, label=label, 
                       linewidth=2, markersize=8)
    axes[1, 1].set_title('组合样式')
    axes[1, 1].legend()
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('marker_line_styles.png', dpi=300, bbox_inches='tight')
    plt.show()

def font_text_examples():
    """字体和文本样式示例"""
    print("创建字体和文本样式示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('字体和文本样式示例', fontsize=20, fontweight='bold')
    
    x = np.linspace(0, 10, 100)
    y = np.sin(x)
    
    # 1. 不同字体大小
    axes[0, 0].plot(x, y, 'b-', linewidth=2)
    axes[0, 0].set_title('不同字体大小示例', fontsize=18, fontweight='bold')
    axes[0, 0].set_xlabel('X轴标签', fontsize=14)
    axes[0, 0].set_ylabel('Y轴标签', fontsize=16)
    axes[0, 0].text(5, 0.5, '大号文本', fontsize=20, ha='center')
    axes[0, 0].text(5, 0, '中号文本', fontsize=14, ha='center')
    axes[0, 0].text(5, -0.5, '小号文本', fontsize=10, ha='center')
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. 不同字体样式
    axes[0, 1].plot(x, y, 'r-', linewidth=2)
    axes[0, 1].set_title('字体样式示例', fontsize=16, fontweight='bold')
    axes[0, 1].text(2, 0.7, '正常字体', fontsize=12, fontstyle='normal')
    axes[0, 1].text(2, 0.4, '斜体字体', fontsize=12, fontstyle='italic')
    axes[0, 1].text(2, 0.1, '粗体字体', fontsize=12, fontweight='bold')
    axes[0, 1].text(2, -0.2, '粗斜体', fontsize=12, fontweight='bold', fontstyle='italic')
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 文本对齐和旋转
    axes[1, 0].plot(x, y, 'g-', linewidth=2)
    axes[1, 0].set_title('文本对齐和旋转', fontsize=16, fontweight='bold')
    
    # 不同对齐方式
    axes[1, 0].text(5, 0.8, '左对齐', ha='left', va='center', fontsize=12, 
                   bbox=dict(boxstyle='round', facecolor='lightblue'))
    axes[1, 0].text(5, 0.5, '居中对齐', ha='center', va='center', fontsize=12,
                   bbox=dict(boxstyle='round', facecolor='lightgreen'))
    axes[1, 0].text(5, 0.2, '右对齐', ha='right', va='center', fontsize=12,
                   bbox=dict(boxstyle='round', facecolor='lightcoral'))
    
    # 旋转文本
    axes[1, 0].text(7, 0, '旋转45度', rotation=45, fontsize=12, ha='center')
    axes[1, 0].text(3, -0.5, '旋转90度', rotation=90, fontsize=12, ha='center')
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 数学公式和特殊符号
    axes[1, 1].plot(x, y, 'm-', linewidth=2)
    axes[1, 1].set_title('数学公式示例', fontsize=16, fontweight='bold')
    
    # LaTeX数学公式
    axes[1, 1].text(5, 0.7, r'$y = \sin(x)$', fontsize=16, ha='center',
                   bbox=dict(boxstyle='round', facecolor='yellow', alpha=0.7))
    axes[1, 1].text(5, 0.3, r'$\int_0^{\pi} \sin(x) dx = 2$', fontsize=14, ha='center')
    axes[1, 1].text(5, -0.1, r'$\alpha + \beta = \gamma$', fontsize=14, ha='center')
    axes[1, 1].text(5, -0.5, r'$\sum_{i=1}^{n} x_i = \bar{x} \cdot n$', fontsize=12, ha='center')
    
    # 希腊字母
    axes[1, 1].text(2, 0, r'$\alpha, \beta, \gamma, \delta, \pi, \sigma$', 
                   fontsize=12, rotation=90, ha='center')
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('font_text_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def theme_style_examples():
    """主题和样式示例"""
    print("创建主题和样式示例...")
    
    # 获取可用的样式
    available_styles = ['default', 'classic', 'ggplot', 'bmh', 'fivethirtyeight']
    
    fig, axes = plt.subplots(2, 3, figsize=(18, 12))
    fig.suptitle('不同主题样式对比', fontsize=16, fontweight='bold')
    
    # 生成示例数据
    x = np.linspace(0, 10, 50)
    y1 = np.sin(x)
    y2 = np.cos(x)
    y3 = np.sin(x) * np.exp(-x/10)
    
    # 应用不同样式
    for i, style in enumerate(available_styles):
        row, col = i // 3, i % 3
        ax = axes[row, col]
        
        with plt.style.context(style):
            ax.plot(x, y1, label='sin(x)', linewidth=2)
            ax.plot(x, y2, label='cos(x)', linewidth=2)
            ax.plot(x, y3, label='衰减sin(x)', linewidth=2)
            ax.set_title(f'{style} 样式', fontsize=12, fontweight='bold')
            ax.set_xlabel('X轴')
            ax.set_ylabel('Y轴')
            ax.legend()
            ax.grid(True, alpha=0.3)
    
    # 自定义样式示例
    ax = axes[1, 2]
    
    # 设置自定义样式
    ax.set_facecolor('#f0f0f0')  # 背景色
    ax.plot(x, y1, color='#e74c3c', linewidth=3, label='sin(x)')
    ax.plot(x, y2, color='#3498db', linewidth=3, label='cos(x)')
    ax.plot(x, y3, color='#2ecc71', linewidth=3, label='衰减sin(x)')
    
    ax.set_title('自定义样式', fontsize=12, fontweight='bold')
    ax.set_xlabel('X轴', fontweight='bold')
    ax.set_ylabel('Y轴', fontweight='bold')
    ax.legend(frameon=True, fancybox=True, shadow=True)
    ax.grid(True, alpha=0.5, linestyle='--')
    
    # 设置边框样式
    for spine in ax.spines.values():
        spine.set_linewidth(2)
        spine.set_color('#34495e')
    
    plt.tight_layout()
    plt.savefig('theme_styles.png', dpi=300, bbox_inches='tight')
    plt.show()

def colormap_examples():
    """颜色映射示例"""
    print("创建颜色映射示例...")
    
    fig, axes = plt.subplots(2, 3, figsize=(18, 12))
    fig.suptitle('颜色映射示例集合', fontsize=16, fontweight='bold')
    
    # 生成2D数据
    x = np.linspace(-3, 3, 100)
    y = np.linspace(-3, 3, 100)
    X, Y = np.meshgrid(x, y)
    Z = np.sin(X) * np.cos(Y) * np.exp(-(X**2 + Y**2)/4)
    
    # 不同的颜色映射
    colormaps = ['viridis', 'plasma', 'inferno', 'magma', 'coolwarm', 'RdYlBu']
    
    for i, cmap in enumerate(colormaps):
        row, col = i // 3, i % 3
        ax = axes[row, col]
        
        im = ax.contourf(X, Y, Z, levels=20, cmap=cmap)
        ax.set_title(f'{cmap} 颜色映射', fontsize=12, fontweight='bold')
        ax.set_xlabel('X轴')
        ax.set_ylabel('Y轴')
        
        # 添加颜色条
        cbar = plt.colorbar(im, ax=ax)
        cbar.set_label('数值', rotation=270, labelpad=15)
    
    plt.tight_layout()
    plt.savefig('colormap_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def custom_legend_examples():
    """自定义图例示例"""
    print("创建自定义图例示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('自定义图例示例', fontsize=16, fontweight='bold')
    
    x = np.linspace(0, 10, 100)
    
    # 1. 基础图例位置
    axes[0, 0].plot(x, np.sin(x), label='sin(x)', linewidth=2)
    axes[0, 0].plot(x, np.cos(x), label='cos(x)', linewidth=2)
    axes[0, 0].plot(x, np.tan(x/2), label='tan(x/2)', linewidth=2)
    axes[0, 0].set_title('不同图例位置')
    axes[0, 0].legend(loc='upper right', frameon=True, shadow=True)
    axes[0, 0].grid(True, alpha=0.3)
    axes[0, 0].set_ylim(-2, 2)
    
    # 2. 图例在图外
    axes[0, 1].plot(x, np.sin(x), label='sin(x)', linewidth=2)
    axes[0, 1].plot(x, np.cos(x), label='cos(x)', linewidth=2)
    axes[0, 1].plot(x, np.sin(2*x), label='sin(2x)', linewidth=2)
    axes[0, 1].set_title('图例在图外')
    axes[0, 1].legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 自定义图例样式
    axes[1, 0].plot(x, np.sin(x), 'r-', linewidth=3, label='正弦波')
    axes[1, 0].plot(x, np.cos(x), 'b--', linewidth=3, label='余弦波')
    axes[1, 0].set_title('自定义图例样式')
    legend = axes[1, 0].legend(loc='upper right', 
                              frameon=True, 
                              fancybox=True, 
                              shadow=True,
                              framealpha=0.9,
                              facecolor='lightgray',
                              edgecolor='black',
                              fontsize=12)
    legend.get_frame().set_linewidth(2)
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 多列图例
    colors = ['red', 'blue', 'green', 'orange', 'purple', 'brown']
    for i, color in enumerate(colors):
        axes[1, 1].plot(x, np.sin(x + i*0.5), color=color, 
                       label=f'相位{i}', linewidth=2)
    axes[1, 1].set_title('多列图例')
    axes[1, 1].legend(ncol=2, loc='upper center', bbox_to_anchor=(0.5, -0.05))
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('custom_legends.png', dpi=300, bbox_inches='tight')
    plt.show()

def annotation_examples():
    """注释和标注示例"""
    print("创建注释和标注示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('注释和标注示例', fontsize=16, fontweight='bold')
    
    x = np.linspace(0, 10, 100)
    y = np.sin(x) * np.exp(-x/10)
    
    # 1. 基础注释
    axes[0, 0].plot(x, y, 'b-', linewidth=2)
    axes[0, 0].set_title('基础注释')
    
    # 找到最大值点
    max_idx = np.argmax(y)
    axes[0, 0].annotate(f'最大值\n({x[max_idx]:.1f}, {y[max_idx]:.2f})',
                       xy=(x[max_idx], y[max_idx]),
                       xytext=(x[max_idx]+2, y[max_idx]+0.2),
                       arrowprops=dict(arrowstyle='->', color='red', lw=2),
                       fontsize=12,
                       bbox=dict(boxstyle='round,pad=0.3', facecolor='yellow', alpha=0.7))
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. 多种箭头样式
    axes[0, 1].plot(x, y, 'g-', linewidth=2)
    axes[0, 1].set_title('不同箭头样式')
    
    arrow_styles = ['->', '-|>', '<->', '<|-|>', 'fancy']
    for i, style in enumerate(arrow_styles):
        axes[0, 1].annotate(f'箭头{i+1}',
                           xy=(2+i*1.5, y[20+i*15]),
                           xytext=(2+i*1.5, y[20+i*15]+0.3),
                           arrowprops=dict(arrowstyle=style, color=f'C{i}', lw=2),
                           ha='center')
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 文本框样式
    axes[1, 0].plot(x, y, 'r-', linewidth=2)
    axes[1, 0].set_title('不同文本框样式')
    
    box_styles = ['round', 'square', 'circle', 'sawtooth', 'round4']
    colors = ['lightblue', 'lightgreen', 'lightcoral', 'lightyellow', 'lightpink']
    
    for i, (box_style, color) in enumerate(zip(box_styles, colors)):
        axes[1, 0].text(2+i*1.5, 0.5-i*0.1, f'{box_style}',
                       bbox=dict(boxstyle=box_style, facecolor=color, alpha=0.8),
                       ha='center', fontsize=10)
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 复杂注释组合
    axes[1, 1].plot(x, y, 'purple', linewidth=2, label='衰减正弦波')
    axes[1, 1].set_title('复杂注释组合')
    
    # 标注多个特殊点
    special_points = [(1, y[10]), (3, y[30]), (6, y[60]), (8, y[80])]
    annotations = ['起始点', '下降段', '中间点', '末尾段']
    
    for (px, py), text in zip(special_points, annotations):
        axes[1, 1].plot(px, py, 'ro', markersize=8)
        axes[1, 1].annotate(text,
                           xy=(px, py),
                           xytext=(px, py+0.2),
                           arrowprops=dict(arrowstyle='->', color='red'),
                           ha='center',
                           bbox=dict(boxstyle='round,pad=0.2', 
                                   facecolor='white', 
                                   edgecolor='red',
                                   alpha=0.8))
    
    axes[1, 1].legend()
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('annotation_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def main():
    """主函数"""
    print("=" * 50)
    print("Matplotlib 样式和自定义示例")
    print("=" * 50)
    
    # 执行各种样式示例
    color_examples()
    marker_line_style_examples()
    font_text_examples()
    theme_style_examples()
    colormap_examples()
    custom_legend_examples()
    annotation_examples()
    
    print("\n所有样式和自定义示例已完成！")
    print("生成的图片文件:")
    print("- color_examples.png")
    print("- marker_line_styles.png")
    print("- font_text_examples.png")
    print("- theme_styles.png")
    print("- colormap_examples.png")
    print("- custom_legends.png")
    print("- annotation_examples.png")

if __name__ == "__main__":
    main()