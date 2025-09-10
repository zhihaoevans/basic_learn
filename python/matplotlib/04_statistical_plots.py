#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Matplotlib 统计图表示例
演示直方图、箱线图、热力图、小提琴图等统计可视化
"""

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy import stats
import matplotlib.patches as patches

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei', 'Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False

def histogram_examples():
    """直方图示例"""
    print("创建直方图示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('直方图示例集合', fontsize=16, fontweight='bold')
    
    # 生成不同分布的数据
    np.random.seed(42)
    normal_data = np.random.normal(100, 15, 1000)
    uniform_data = np.random.uniform(50, 150, 1000)
    exponential_data = np.random.exponential(2, 1000)
    
    # 1. 基础直方图
    axes[0, 0].hist(normal_data, bins=30, alpha=0.7, color='skyblue', edgecolor='black')
    axes[0, 0].set_title('基础直方图 - 正态分布')
    axes[0, 0].set_xlabel('数值')
    axes[0, 0].set_ylabel('频次')
    axes[0, 0].grid(True, alpha=0.3)
    
    # 添加统计信息
    mean_val = np.mean(normal_data)
    std_val = np.std(normal_data)
    axes[0, 0].axvline(mean_val, color='red', linestyle='--', linewidth=2, label=f'均值: {mean_val:.1f}')
    axes[0, 0].axvline(mean_val + std_val, color='orange', linestyle='--', alpha=0.7, label=f'+1σ: {mean_val + std_val:.1f}')
    axes[0, 0].axvline(mean_val - std_val, color='orange', linestyle='--', alpha=0.7, label=f'-1σ: {mean_val - std_val:.1f}')
    axes[0, 0].legend()
    
    # 2. 多个分布对比
    axes[0, 1].hist(normal_data, bins=30, alpha=0.6, label='正态分布', density=True)
    axes[0, 1].hist(uniform_data, bins=30, alpha=0.6, label='均匀分布', density=True)
    axes[0, 1].set_title('多分布对比 - 密度直方图')
    axes[0, 1].set_xlabel('数值')
    axes[0, 1].set_ylabel('密度')
    axes[0, 1].legend()
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 堆叠直方图
    group1 = np.random.normal(100, 10, 500)
    group2 = np.random.normal(110, 12, 500)
    group3 = np.random.normal(90, 8, 500)
    
    axes[1, 0].hist([group1, group2, group3], bins=25, alpha=0.7, 
                   label=['组1', '组2', '组3'], stacked=True)
    axes[1, 0].set_title('堆叠直方图')
    axes[1, 0].set_xlabel('数值')
    axes[1, 0].set_ylabel('频次')
    axes[1, 0].legend()
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 2D直方图（热力图形式）
    x = np.random.normal(0, 1, 1000)
    y = np.random.normal(0, 1, 1000)
    
    hist, xedges, yedges = np.histogram2d(x, y, bins=20)
    im = axes[1, 1].imshow(hist.T, origin='lower', extent=[xedges[0], xedges[-1], yedges[0], yedges[-1]], 
                          cmap='Blues', aspect='auto')
    axes[1, 1].set_title('2D直方图')
    axes[1, 1].set_xlabel('X值')
    axes[1, 1].set_ylabel('Y值')
    plt.colorbar(im, ax=axes[1, 1], label='频次')
    
    plt.tight_layout()
    plt.savefig('histogram_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def boxplot_examples():
    """箱线图示例"""
    print("创建箱线图示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('箱线图示例集合', fontsize=16, fontweight='bold')
    
    # 生成测试数据
    np.random.seed(42)
    data1 = np.random.normal(100, 15, 100)
    data2 = np.random.normal(110, 20, 100)
    data3 = np.random.normal(95, 10, 100)
    data4 = np.random.exponential(10, 100) + 80
    
    # 1. 基础箱线图
    box_data = [data1, data2, data3, data4]
    labels = ['组A', '组B', '组C', '组D']
    
    bp1 = axes[0, 0].boxplot(box_data, tick_labels=labels, patch_artist=True)
    axes[0, 0].set_title('基础箱线图')
    axes[0, 0].set_ylabel('数值')
    axes[0, 0].grid(True, alpha=0.3)
    
    # 自定义箱线图颜色
    colors = ['lightblue', 'lightgreen', 'lightcoral', 'lightyellow']
    for patch, color in zip(bp1['boxes'], colors):
        patch.set_facecolor(color)
        patch.set_alpha(0.7)
    
    # 2. 水平箱线图
    bp2 = axes[0, 1].boxplot(box_data, tick_labels=labels, vert=False, patch_artist=True)
    axes[0, 1].set_title('水平箱线图')
    axes[0, 1].set_xlabel('数值')
    axes[0, 1].grid(True, alpha=0.3)
    
    for patch, color in zip(bp2['boxes'], colors):
        patch.set_facecolor(color)
        patch.set_alpha(0.7)
    
    # 3. 带缺口的箱线图
    bp3 = axes[1, 0].boxplot(box_data, tick_labels=labels, notch=True, patch_artist=True)
    axes[1, 0].set_title('带缺口的箱线图')
    axes[1, 0].set_ylabel('数值')
    axes[1, 0].grid(True, alpha=0.3)
    
    for patch, color in zip(bp3['boxes'], colors):
        patch.set_facecolor(color)
        patch.set_alpha(0.7)
    
    # 4. 箱线图与散点图结合
    bp4 = axes[1, 1].boxplot(box_data, tick_labels=labels, patch_artist=True)
    
    # 添加散点
    for i, data in enumerate(box_data):
        # 添加一些随机抖动以避免重叠
        x = np.random.normal(i+1, 0.04, len(data))
        axes[1, 1].scatter(x, data, alpha=0.4, s=20)
    
    axes[1, 1].set_title('箱线图 + 散点图')
    axes[1, 1].set_ylabel('数值')
    axes[1, 1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('boxplot_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def heatmap_examples():
    """热力图示例"""
    print("创建热力图示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('热力图示例集合', fontsize=16, fontweight='bold')
    
    # 1. 基础热力图
    np.random.seed(42)
    data_matrix = np.random.rand(10, 12)
    
    im1 = axes[0, 0].imshow(data_matrix, cmap='viridis', aspect='auto')
    axes[0, 0].set_title('基础热力图')
    axes[0, 0].set_xlabel('列索引')
    axes[0, 0].set_ylabel('行索引')
    plt.colorbar(im1, ax=axes[0, 0])
    
    # 2. 相关性矩阵热力图
    # 生成相关数据
    variables = ['变量A', '变量B', '变量C', '变量D', '变量E']
    correlation_matrix = np.array([
        [1.0, 0.8, -0.3, 0.1, 0.6],
        [0.8, 1.0, -0.1, 0.2, 0.4],
        [-0.3, -0.1, 1.0, 0.7, -0.2],
        [0.1, 0.2, 0.7, 1.0, 0.3],
        [0.6, 0.4, -0.2, 0.3, 1.0]
    ])
    
    im2 = axes[0, 1].imshow(correlation_matrix, cmap='RdBu_r', vmin=-1, vmax=1, aspect='auto')
    axes[0, 1].set_title('相关性矩阵热力图')
    axes[0, 1].set_xticks(range(len(variables)))
    axes[0, 1].set_yticks(range(len(variables)))
    axes[0, 1].set_xticklabels(variables, rotation=45)
    axes[0, 1].set_yticklabels(variables)
    
    # 添加数值标签
    for i in range(len(variables)):
        for j in range(len(variables)):
            axes[0, 1].text(j, i, f'{correlation_matrix[i, j]:.2f}', 
                           ha='center', va='center', 
                           color='white' if abs(correlation_matrix[i, j]) > 0.5 else 'black')
    
    plt.colorbar(im2, ax=axes[0, 1], label='相关系数')
    
    # 3. 时间序列热力图
    days = ['周一', '周二', '周三', '周四', '周五', '周六', '周日']
    hours = [f'{i:02d}:00' for i in range(24)]
    
    # 模拟一周24小时的活动数据
    activity_data = np.random.poisson(lam=5, size=(7, 24))
    # 添加一些模式（工作日vs周末，白天vs夜晚）
    for i in range(7):
        for j in range(24):
            if i < 5:  # 工作日
                if 9 <= j <= 17:  # 工作时间
                    activity_data[i, j] += np.random.poisson(10)
            else:  # 周末
                if 10 <= j <= 22:  # 休闲时间
                    activity_data[i, j] += np.random.poisson(8)
    
    im3 = axes[1, 0].imshow(activity_data, cmap='YlOrRd', aspect='auto')
    axes[1, 0].set_title('一周活动热力图')
    axes[1, 0].set_xlabel('小时')
    axes[1, 0].set_ylabel('星期')
    axes[1, 0].set_xticks(range(0, 24, 4))
    axes[1, 0].set_xticklabels([f'{i:02d}:00' for i in range(0, 24, 4)])
    axes[1, 0].set_yticks(range(7))
    axes[1, 0].set_yticklabels(days)
    plt.colorbar(im3, ax=axes[1, 0], label='活动强度')
    
    # 4. 自定义热力图
    # 创建一个函数热力图
    x = np.linspace(-3, 3, 50)
    y = np.linspace(-3, 3, 50)
    X, Y = np.meshgrid(x, y)
    Z = np.sin(X) * np.cos(Y) * np.exp(-(X**2 + Y**2)/4)
    
    im4 = axes[1, 1].contourf(X, Y, Z, levels=20, cmap='coolwarm')
    axes[1, 1].set_title('函数热力图')
    axes[1, 1].set_xlabel('X轴')
    axes[1, 1].set_ylabel('Y轴')
    
    # 添加等高线
    contour = axes[1, 1].contour(X, Y, Z, levels=10, colors='black', alpha=0.4, linewidths=0.5)
    axes[1, 1].clabel(contour, inline=True, fontsize=8)
    
    plt.colorbar(im4, ax=axes[1, 1], label='函数值')
    
    plt.tight_layout()
    plt.savefig('heatmap_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def violin_plot_examples():
    """小提琴图示例"""
    print("创建小提琴图示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('小提琴图示例集合', fontsize=16, fontweight='bold')
    
    # 生成不同分布的数据
    np.random.seed(42)
    normal_data = [np.random.normal(100, 15, 200) for _ in range(4)]
    skewed_data = [np.random.gamma(2, 2, 200) * 10 + 80 for _ in range(4)]
    
    # 1. 基础小提琴图
    parts1 = axes[0, 0].violinplot(normal_data, positions=range(1, 5), showmeans=True, showmedians=True)
    axes[0, 0].set_title('基础小提琴图')
    axes[0, 0].set_xlabel('组别')
    axes[0, 0].set_ylabel('数值')
    axes[0, 0].set_xticks(range(1, 5))
    axes[0, 0].set_xticklabels(['组A', '组B', '组C', '组D'])
    axes[0, 0].grid(True, alpha=0.3)
    
    # 自定义颜色
    colors = ['lightblue', 'lightgreen', 'lightcoral', 'lightyellow']
    for pc, color in zip(parts1['bodies'], colors):
        pc.set_facecolor(color)
        pc.set_alpha(0.7)
    
    # 2. 水平小提琴图
    parts2 = axes[0, 1].violinplot(normal_data, positions=range(1, 5), 
                                  vert=False, showmeans=True, showmedians=True)
    axes[0, 1].set_title('水平小提琴图')
    axes[0, 1].set_ylabel('组别')
    axes[0, 1].set_xlabel('数值')
    axes[0, 1].set_yticks(range(1, 5))
    axes[0, 1].set_yticklabels(['组A', '组B', '组C', '组D'])
    axes[0, 1].grid(True, alpha=0.3)
    
    for pc, color in zip(parts2['bodies'], colors):
        pc.set_facecolor(color)
        pc.set_alpha(0.7)
    
    # 3. 小提琴图与箱线图对比
    # 左半边：小提琴图
    parts3 = axes[1, 0].violinplot(skewed_data, positions=np.arange(1, 5) - 0.2, 
                                  widths=0.35, showmeans=False, showmedians=False)
    # 右半边：箱线图
    bp3 = axes[1, 0].boxplot(skewed_data, positions=np.arange(1, 5) + 0.2, 
                            widths=0.35, patch_artist=True)
    
    axes[1, 0].set_title('小提琴图 vs 箱线图')
    axes[1, 0].set_xlabel('组别')
    axes[1, 0].set_ylabel('数值')
    axes[1, 0].set_xticks(range(1, 5))
    axes[1, 0].set_xticklabels(['组A', '组B', '组C', '组D'])
    axes[1, 0].grid(True, alpha=0.3)
    
    # 设置颜色
    for pc, color in zip(parts3['bodies'], colors):
        pc.set_facecolor(color)
        pc.set_alpha(0.7)
    
    for patch, color in zip(bp3['boxes'], colors):
        patch.set_facecolor(color)
        patch.set_alpha(0.7)
    
    # 4. 分组小提琴图
    group1_data = [np.random.normal(100, 10, 100), np.random.normal(110, 12, 100)]
    group2_data = [np.random.normal(95, 8, 100), np.random.normal(105, 15, 100)]
    
    # 绘制两组数据
    parts4a = axes[1, 1].violinplot(group1_data, positions=[1, 2], 
                                   widths=0.4, showmeans=True)
    parts4b = axes[1, 1].violinplot(group2_data, positions=[3, 4], 
                                   widths=0.4, showmeans=True)
    
    axes[1, 1].set_title('分组小提琴图')
    axes[1, 1].set_xlabel('条件')
    axes[1, 1].set_ylabel('数值')
    axes[1, 1].set_xticks([1.5, 3.5])
    axes[1, 1].set_xticklabels(['条件A', '条件B'])
    axes[1, 1].grid(True, alpha=0.3)
    
    # 设置不同组的颜色
    for pc in parts4a['bodies']:
        pc.set_facecolor('lightblue')
        pc.set_alpha(0.7)
    
    for pc in parts4b['bodies']:
        pc.set_facecolor('lightcoral')
        pc.set_alpha(0.7)
    
    plt.tight_layout()
    plt.savefig('violin_plot_examples.png', dpi=300, bbox_inches='tight')
    plt.show()

def distribution_comparison():
    """分布比较示例"""
    print("创建分布比较示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('统计分布比较示例', fontsize=16, fontweight='bold')
    
    # 生成不同分布的数据
    np.random.seed(42)
    n_samples = 1000
    
    normal_data = np.random.normal(0, 1, n_samples)
    uniform_data = np.random.uniform(-2, 2, n_samples)
    exponential_data = np.random.exponential(1, n_samples)
    gamma_data = np.random.gamma(2, 1, n_samples)
    
    # 1. 密度图对比
    axes[0, 0].hist(normal_data, bins=50, alpha=0.6, density=True, label='正态分布')
    axes[0, 0].hist(uniform_data, bins=50, alpha=0.6, density=True, label='均匀分布')
    axes[0, 0].set_title('密度分布对比')
    axes[0, 0].set_xlabel('数值')
    axes[0, 0].set_ylabel('密度')
    axes[0, 0].legend()
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. Q-Q图
    from scipy import stats
    stats.probplot(normal_data, dist="norm", plot=axes[0, 1])
    axes[0, 1].set_title('Q-Q图 - 正态性检验')
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 累积分布函数
    x_range = np.linspace(-3, 3, 100)
    
    # 经验累积分布
    sorted_normal = np.sort(normal_data)
    y_normal = np.arange(1, len(sorted_normal) + 1) / len(sorted_normal)
    axes[1, 0].plot(sorted_normal, y_normal, label='经验CDF', linewidth=2)
    
    # 理论累积分布
    theoretical_cdf = stats.norm.cdf(x_range, 0, 1)
    axes[1, 0].plot(x_range, theoretical_cdf, label='理论CDF', linewidth=2, linestyle='--')
    
    axes[1, 0].set_title('累积分布函数对比')
    axes[1, 0].set_xlabel('数值')
    axes[1, 0].set_ylabel('累积概率')
    axes[1, 0].legend()
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 多分布箱线图对比
    all_data = [normal_data, uniform_data, exponential_data, gamma_data]
    labels = ['正态分布', '均匀分布', '指数分布', 'Gamma分布']
    
    bp = axes[1, 1].boxplot(all_data, tick_labels=labels, patch_artist=True)
    axes[1, 1].set_title('多分布箱线图对比')
    axes[1, 1].set_ylabel('数值')
    axes[1, 1].grid(True, alpha=0.3)
    
    colors = ['lightblue', 'lightgreen', 'lightcoral', 'lightyellow']
    for patch, color in zip(bp['boxes'], colors):
        patch.set_facecolor(color)
        patch.set_alpha(0.7)
    
    plt.tight_layout()
    plt.savefig('distribution_comparison.png', dpi=300, bbox_inches='tight')
    plt.show()

def statistical_tests_visualization():
    """统计检验可视化示例"""
    print("创建统计检验可视化示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('统计检验可视化示例', fontsize=16, fontweight='bold')
    
    # 1. t检验可视化
    np.random.seed(42)
    group1 = np.random.normal(100, 15, 50)
    group2 = np.random.normal(110, 15, 50)
    
    axes[0, 0].hist(group1, alpha=0.6, label='组1', bins=15, density=True)
    axes[0, 0].hist(group2, alpha=0.6, label='组2', bins=15, density=True)
    
    # 添加均值线
    axes[0, 0].axvline(np.mean(group1), color='blue', linestyle='--', 
                      label=f'组1均值: {np.mean(group1):.1f}')
    axes[0, 0].axvline(np.mean(group2), color='orange', linestyle='--', 
                      label=f'组2均值: {np.mean(group2):.1f}')
    
    # 进行t检验
    t_stat, p_value = stats.ttest_ind(group1, group2)
    axes[0, 0].set_title(f't检验可视化\nt统计量: {t_stat:.3f}, p值: {p_value:.3f}')
    axes[0, 0].set_xlabel('数值')
    axes[0, 0].set_ylabel('密度')
    axes[0, 0].legend()
    axes[0, 0].grid(True, alpha=0.3)
    
    # 2. 相关性分析
    n = 100
    x = np.random.randn(n)
    y = 0.7 * x + 0.3 * np.random.randn(n)  # 有相关性的数据
    
    axes[0, 1].scatter(x, y, alpha=0.6)
    
    # 添加回归线
    z = np.polyfit(x, y, 1)
    p = np.poly1d(z)
    axes[0, 1].plot(sorted(x), p(sorted(x)), "r--", alpha=0.8, linewidth=2)
    
    # 计算相关系数
    correlation = np.corrcoef(x, y)[0, 1]
    axes[0, 1].set_title(f'相关性分析\n相关系数: {correlation:.3f}')
    axes[0, 1].set_xlabel('X变量')
    axes[0, 1].set_ylabel('Y变量')
    axes[0, 1].grid(True, alpha=0.3)
    
    # 3. 置信区间可视化
    sample_means = []
    for _ in range(100):
        sample = np.random.normal(100, 15, 30)
        sample_means.append(np.mean(sample))
    
    sample_means = np.array(sample_means)
    mean_of_means = np.mean(sample_means)
    std_of_means = np.std(sample_means)
    
    axes[1, 0].hist(sample_means, bins=20, alpha=0.7, density=True, color='lightblue')
    axes[1, 0].axvline(mean_of_means, color='red', linestyle='-', linewidth=2, label='样本均值的均值')
    
    # 95%置信区间
    ci_lower = mean_of_means - 1.96 * std_of_means
    ci_upper = mean_of_means + 1.96 * std_of_means
    axes[1, 0].axvline(ci_lower, color='green', linestyle='--', label='95% CI下限')
    axes[1, 0].axvline(ci_upper, color='green', linestyle='--', label='95% CI上限')
    
    axes[1, 0].set_title('抽样分布与置信区间')
    axes[1, 0].set_xlabel('样本均值')
    axes[1, 0].set_ylabel('密度')
    axes[1, 0].legend()
    axes[1, 0].grid(True, alpha=0.3)
    
    # 4. 方差分析(ANOVA)可视化
    group_a = np.random.normal(100, 10, 30)
    group_b = np.random.normal(105, 12, 30)
    group_c = np.random.normal(110, 8, 30)
    
    data_groups = [group_a, group_b, group_c]
    labels = ['组A', '组B', '组C']
    
    # 箱线图
    bp = axes[1, 1].boxplot(data_groups, tick_labels=labels, patch_artist=True)
    
    # 添加散点
    for i, data in enumerate(data_groups):
        x = np.random.normal(i+1, 0.04, len(data))
        axes[1, 1].scatter(x, data, alpha=0.4, s=20)
    
    # 进行方差分析
    f_stat, p_value_anova = stats.f_oneway(group_a, group_b, group_c)
    axes[1, 1].set_title(f'方差分析(ANOVA)\nF统计量: {f_stat:.3f}, p值: {p_value_anova:.3f}')
    axes[1, 1].set_ylabel('数值')
    axes[1, 1].grid(True, alpha=0.3)
    
    colors = ['lightblue', 'lightgreen', 'lightcoral']
    for patch, color in zip(bp['boxes'], colors):
        patch.set_facecolor(color)
        patch.set_alpha(0.7)
    
    plt.tight_layout()
    plt.savefig('statistical_tests.png', dpi=300, bbox_inches='tight')
    plt.show()

def main():
    """主函数"""
    print("=" * 50)
    print("Matplotlib 统计图表示例")
    print("=" * 50)
    
    # 执行各种统计图表示例
    histogram_examples()
    boxplot_examples()
    heatmap_examples()
    violin_plot_examples()
    distribution_comparison()
    statistical_tests_visualization()
    
    print("\n所有统计图表示例已完成！")
    print("生成的图片文件:")
    print("- histogram_examples.png")
    print("- boxplot_examples.png")
    print("- heatmap_examples.png")
    print("- violin_plot_examples.png")
    print("- distribution_comparison.png")
    print("- statistical_tests.png")

if __name__ == "__main__":
    main()