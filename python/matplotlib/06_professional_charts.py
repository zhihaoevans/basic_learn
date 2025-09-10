#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Matplotlib 专业图表示例
演示金融图表、科学可视化、工程图表等专业应用
"""

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from datetime import datetime, timedelta
import matplotlib.dates as mdates
from matplotlib.patches import Rectangle, FancyBboxPatch
import matplotlib.patches as mpatches
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.collections import LineCollection

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei', 'Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False

def financial_candlestick_chart():
    """金融K线图示例"""
    print("创建金融K线图示例...")
    
    # 生成模拟股价数据
    np.random.seed(42)
    n_days = 60
    dates = [datetime.now() - timedelta(days=x) for x in range(n_days, 0, -1)]
    
    # 模拟股价走势
    initial_price = 100
    prices = [initial_price]
    
    for i in range(1, n_days):
        # 随机游走模拟股价
        change = np.random.normal(0, 2)
        new_price = max(prices[-1] + change, 10)  # 确保价格不为负
        prices.append(new_price)
    
    # 生成OHLC数据
    ohlc_data = []
    for i, price in enumerate(prices):
        # 模拟开盘、最高、最低、收盘价
        open_price = price + np.random.normal(0, 0.5)
        high_price = max(open_price, price) + abs(np.random.normal(0, 1))
        low_price = min(open_price, price) - abs(np.random.normal(0, 1))
        close_price = price
        
        ohlc_data.append({
            'date': dates[i],
            'open': open_price,
            'high': high_price,
            'low': low_price,
            'close': close_price,
            'volume': np.random.randint(1000, 10000)
        })
    
    df = pd.DataFrame(ohlc_data)
    
    # 创建图形
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(15, 10), 
                                   gridspec_kw={'height_ratios': [3, 1]})
    
    # 绘制K线图
    for i, row in df.iterrows():
        date = row['date']
        open_price = row['open']
        high_price = row['high']
        low_price = row['low']
        close_price = row['close']
        
        # 确定颜色（红涨绿跌）
        color = 'red' if close_price >= open_price else 'green'
        
        # 绘制高低价线
        ax1.plot([date, date], [low_price, high_price], color='black', linewidth=1)
        
        # 绘制实体
        height = abs(close_price - open_price)
        bottom = min(open_price, close_price)
        
        rect = Rectangle((mdates.date2num(date) - 0.3, bottom), 0.6, height,
                        facecolor=color, alpha=0.8, edgecolor='black')
        ax1.add_patch(rect)
    
    # 添加移动平均线
    df['MA5'] = df['close'].rolling(window=5).mean()
    df['MA20'] = df['close'].rolling(window=20).mean()
    
    ax1.plot(df['date'], df['MA5'], label='MA5', color='blue', linewidth=1.5)
    ax1.plot(df['date'], df['MA20'], label='MA20', color='orange', linewidth=1.5)
    
    ax1.set_title('股票K线图示例', fontsize=16, fontweight='bold')
    ax1.set_ylabel('价格 (元)')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d'))
    ax1.xaxis.set_major_locator(mdates.WeekdayLocator())
    
    # 绘制成交量
    colors = ['red' if close >= open else 'green' 
              for close, open in zip(df['close'], df['open'])]
    ax2.bar(df['date'], df['volume'], color=colors, alpha=0.7, width=0.8)
    ax2.set_title('成交量')
    ax2.set_ylabel('成交量')
    ax2.set_xlabel('日期')
    ax2.grid(True, alpha=0.3)
    ax2.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d'))
    ax2.xaxis.set_major_locator(mdates.WeekdayLocator())
    
    plt.tight_layout()
    plt.xticks(rotation=45)
    plt.savefig('financial_candlestick.png', dpi=300, bbox_inches='tight')
    plt.show()

def portfolio_analysis_dashboard():
    """投资组合分析仪表板"""
    print("创建投资组合分析仪表板...")
    
    # 生成模拟投资组合数据
    np.random.seed(42)
    assets = ['股票A', '股票B', '股票C', '债券A', '债券B', '现金']
    weights = np.array([0.25, 0.20, 0.15, 0.20, 0.15, 0.05])
    returns = np.array([0.12, 0.08, 0.15, 0.04, 0.03, 0.01])  # 年化收益率
    risks = np.array([0.18, 0.15, 0.22, 0.05, 0.04, 0.00])   # 年化波动率
    
    # 创建复杂的仪表板布局
    fig = plt.figure(figsize=(20, 12))
    gs = fig.add_gridspec(3, 4, hspace=0.3, wspace=0.3)
    
    # 1. 资产配置饼图
    ax1 = fig.add_subplot(gs[0, 0])
    colors = plt.cm.Set3(np.linspace(0, 1, len(assets)))
    wedges, texts, autotexts = ax1.pie(weights, labels=assets, autopct='%1.1f%%', 
                                      colors=colors, startangle=90)
    ax1.set_title('资产配置', fontsize=14, fontweight='bold')
    
    # 2. 风险收益散点图
    ax2 = fig.add_subplot(gs[0, 1])
    scatter = ax2.scatter(risks, returns, s=weights*1000, c=colors, alpha=0.7)
    
    for i, asset in enumerate(assets):
        ax2.annotate(asset, (risks[i], returns[i]), 
                    xytext=(5, 5), textcoords='offset points', fontsize=10)
    
    ax2.set_xlabel('风险 (年化波动率)')
    ax2.set_ylabel('收益 (年化收益率)')
    ax2.set_title('风险收益分布', fontsize=14, fontweight='bold')
    ax2.grid(True, alpha=0.3)
    
    # 3. 历史净值曲线
    ax3 = fig.add_subplot(gs[0, 2:])
    days = 252  # 一年交易日
    dates = pd.date_range(start='2023-01-01', periods=days, freq='D')
    
    # 模拟净值走势
    portfolio_nav = [1.0]
    benchmark_nav = [1.0]
    
    for i in range(1, days):
        # 投资组合净值
        portfolio_return = np.sum(weights * np.random.normal(returns/252, risks/np.sqrt(252)))
        portfolio_nav.append(portfolio_nav[-1] * (1 + portfolio_return))
        
        # 基准净值（简单模拟）
        benchmark_return = np.random.normal(0.08/252, 0.12/np.sqrt(252))
        benchmark_nav.append(benchmark_nav[-1] * (1 + benchmark_return))
    
    ax3.plot(dates, portfolio_nav, label='投资组合', linewidth=2, color='blue')
    ax3.plot(dates, benchmark_nav, label='基准指数', linewidth=2, color='red', alpha=0.7)
    ax3.set_title('净值走势对比', fontsize=14, fontweight='bold')
    ax3.set_ylabel('净值')
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    ax3.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d'))
    
    # 4. 月度收益热力图
    ax4 = fig.add_subplot(gs[1, :2])
    
    # 生成月度收益数据
    months = ['1月', '2月', '3月', '4月', '5月', '6月', 
              '7月', '8月', '9月', '10月', '11月', '12月']
    years = ['2021', '2022', '2023']
    
    monthly_returns = np.random.normal(0.008, 0.03, (len(years), len(months)))
    
    im = ax4.imshow(monthly_returns, cmap='RdYlGn', aspect='auto', vmin=-0.05, vmax=0.05)
    ax4.set_xticks(range(len(months)))
    ax4.set_yticks(range(len(years)))
    ax4.set_xticklabels(months)
    ax4.set_yticklabels(years)
    ax4.set_title('月度收益热力图', fontsize=14, fontweight='bold')
    
    # 添加数值标签
    for i in range(len(years)):
        for j in range(len(months)):
            ax4.text(j, i, f'{monthly_returns[i, j]:.1%}', 
                    ha='center', va='center', fontsize=8,
                    color='white' if abs(monthly_returns[i, j]) > 0.02 else 'black')
    
    plt.colorbar(im, ax=ax4, label='月度收益率')
    
    # 5. 业绩指标表
    ax5 = fig.add_subplot(gs[1, 2:])
    ax5.axis('off')
    
    # 计算业绩指标
    portfolio_return_total = (portfolio_nav[-1] - 1) * 100
    benchmark_return_total = (benchmark_nav[-1] - 1) * 100
    excess_return = portfolio_return_total - benchmark_return_total
    
    portfolio_vol = np.std(np.diff(portfolio_nav) / portfolio_nav[:-1]) * np.sqrt(252) * 100
    sharpe_ratio = (portfolio_return_total - 1) / portfolio_vol  # 简化计算
    
    max_drawdown = 0
    peak = portfolio_nav[0]
    for nav in portfolio_nav:
        if nav > peak:
            peak = nav
        drawdown = (peak - nav) / peak
        if drawdown > max_drawdown:
            max_drawdown = drawdown
    
    metrics_data = [
        ['指标', '投资组合', '基准指数', '超额收益'],
        ['年化收益率', f'{portfolio_return_total:.2f}%', f'{benchmark_return_total:.2f}%', f'{excess_return:.2f}%'],
        ['年化波动率', f'{portfolio_vol:.2f}%', '12.00%', f'{portfolio_vol-12:.2f}%'],
        ['夏普比率', f'{sharpe_ratio:.2f}', '0.58', f'{sharpe_ratio-0.58:.2f}'],
        ['最大回撤', f'{max_drawdown:.2%}', '8.50%', f'{max_drawdown-0.085:.2%}']
    ]
    
    table = ax5.table(cellText=metrics_data[1:], colLabels=metrics_data[0],
                     cellLoc='center', loc='center', bbox=[0, 0, 1, 1])
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1, 2)
    
    # 设置表格样式
    for i in range(len(metrics_data)):
        for j in range(len(metrics_data[0])):
            cell = table[(i, j)]
            if i == 0:  # 表头
                cell.set_facecolor('#4CAF50')
                cell.set_text_props(weight='bold', color='white')
            else:
                cell.set_facecolor('#f0f0f0' if i % 2 == 0 else 'white')
    
    ax5.set_title('业绩指标对比', fontsize=14, fontweight='bold', pad=20)
    
    # 6. 行业配置柱状图
    ax6 = fig.add_subplot(gs[2, :2])
    industries = ['科技', '金融', '医疗', '消费', '能源', '工业']
    industry_weights = [0.30, 0.25, 0.15, 0.12, 0.10, 0.08]
    benchmark_weights = [0.28, 0.22, 0.18, 0.15, 0.12, 0.05]
    
    x = np.arange(len(industries))
    width = 0.35
    
    bars1 = ax6.bar(x - width/2, industry_weights, width, label='投资组合', alpha=0.8)
    bars2 = ax6.bar(x + width/2, benchmark_weights, width, label='基准指数', alpha=0.8)
    
    ax6.set_xlabel('行业')
    ax6.set_ylabel('权重')
    ax6.set_title('行业配置对比', fontsize=14, fontweight='bold')
    ax6.set_xticks(x)
    ax6.set_xticklabels(industries)
    ax6.legend()
    ax6.grid(True, alpha=0.3, axis='y')
    
    # 添加数值标签
    for bars in [bars1, bars2]:
        for bar in bars:
            height = bar.get_height()
            ax6.text(bar.get_x() + bar.get_width()/2., height + 0.005,
                    f'{height:.1%}', ha='center', va='bottom', fontsize=9)
    
    # 7. 风险分解图
    ax7 = fig.add_subplot(gs[2, 2:])
    risk_sources = ['市场风险', '行业风险', '个股风险', '其他风险']
    risk_contributions = [0.65, 0.20, 0.12, 0.03]
    
    colors_risk = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#FFA07A']
    bars = ax7.barh(risk_sources, risk_contributions, color=colors_risk, alpha=0.8)
    
    ax7.set_xlabel('风险贡献度')
    ax7.set_title('风险分解分析', fontsize=14, fontweight='bold')
    ax7.grid(True, alpha=0.3, axis='x')
    
    # 添加数值标签
    for i, (bar, value) in enumerate(zip(bars, risk_contributions)):
        ax7.text(value + 0.01, i, f'{value:.1%}', va='center', fontweight='bold')
    
    plt.suptitle('投资组合分析仪表板', fontsize=18, fontweight='bold', y=0.98)
    plt.savefig('portfolio_dashboard.png', dpi=300, bbox_inches='tight')
    plt.show()

def scientific_visualization_examples():
    """科学可视化示例"""
    print("创建科学可视化示例...")
    
    fig = plt.figure(figsize=(16, 12))
    gs = fig.add_gridspec(2, 3, hspace=0.3, wspace=0.3)
    
    # 1. 物理场可视化 - 电场线
    ax1 = fig.add_subplot(gs[0, 0])
    
    # 创建电荷
    charges = [(2, 2, 1), (-2, -2, -1), (2, -2, 1)]  # (x, y, charge)
    
    x = np.linspace(-4, 4, 20)
    y = np.linspace(-4, 4, 20)
    X, Y = np.meshgrid(x, y)
    
    # 计算电场
    Ex, Ey = np.zeros_like(X), np.zeros_like(Y)
    
    for cx, cy, q in charges:
        dx = X - cx
        dy = Y - cy
        r = np.sqrt(dx**2 + dy**2)
        r[r == 0] = 1e-10  # 避免除零
        
        Ex += q * dx / r**3
        Ey += q * dy / r**3
    
    # 绘制电场线
    ax1.streamplot(X, Y, Ex, Ey, density=1.5, color='blue')
    
    # 绘制电荷
    for cx, cy, q in charges:
        color = 'red' if q > 0 else 'blue'
        ax1.plot(cx, cy, 'o', color=color, markersize=15, 
                markeredgecolor='black', markeredgewidth=2)
        ax1.text(cx, cy, f'{q:+d}', ha='center', va='center', 
                color='white', fontweight='bold')
    
    ax1.set_title('电场线可视化', fontsize=12, fontweight='bold')
    ax1.set_xlabel('X (m)')
    ax1.set_ylabel('Y (m)')
    ax1.grid(True, alpha=0.3)
    ax1.set_aspect('equal')
    
    # 2. 分子结构可视化
    ax2 = fig.add_subplot(gs[0, 1], projection='3d')
    
    # 模拟水分子结构
    atoms = {
        'O': [(0, 0, 0)],  # 氧原子
        'H': [(0.96, 0, 0), (-0.24, 0.93, 0)]  # 氢原子
    }
    
    colors = {'O': 'red', 'H': 'lightblue'}
    sizes = {'O': 200, 'H': 100}
    
    # 绘制原子
    for atom_type, positions in atoms.items():
        for pos in positions:
            ax2.scatter(*pos, c=colors[atom_type], s=sizes[atom_type], 
                       alpha=0.8, edgecolors='black')
    
    # 绘制化学键
    bonds = [(atoms['O'][0], atoms['H'][0]), 
             (atoms['O'][0], atoms['H'][1])]
    
    for bond in bonds:
        ax2.plot3D(*zip(*bond), 'k-', linewidth=3)
    
    ax2.set_title('水分子结构 (H₂O)', fontsize=12, fontweight='bold')
    ax2.set_xlabel('X (Å)')
    ax2.set_ylabel('Y (Å)')
    ax2.set_zlabel('Z (Å)')
    
    # 3. 光谱分析
    ax3 = fig.add_subplot(gs[0, 2])
    
    # 模拟光谱数据
    wavelength = np.linspace(400, 700, 1000)  # 可见光波长范围
    
    # 模拟几个吸收峰
    peaks = [450, 550, 650]
    widths = [20, 30, 25]
    intensities = [0.8, 0.6, 0.9]
    
    spectrum = np.ones_like(wavelength)
    for peak, width, intensity in zip(peaks, widths, intensities):
        spectrum -= intensity * np.exp(-((wavelength - peak) / width)**2)
    
    # 添加噪声
    spectrum += np.random.normal(0, 0.02, len(spectrum))
    
    ax3.plot(wavelength, spectrum, 'b-', linewidth=1.5)
    ax3.fill_between(wavelength, spectrum, alpha=0.3)
    
    # 标记吸收峰
    for peak, intensity in zip(peaks, intensities):
        peak_idx = np.argmin(np.abs(wavelength - peak))
        ax3.annotate(f'{peak}nm', 
                    xy=(peak, spectrum[peak_idx]), 
                    xytext=(peak, spectrum[peak_idx] - 0.2),
                    arrowprops=dict(arrowstyle='->', color='red'),
                    ha='center', fontsize=10)
    
    ax3.set_title('吸收光谱分析', fontsize=12, fontweight='bold')
    ax3.set_xlabel('波长 (nm)')
    ax3.set_ylabel('吸收强度')
    ax3.grid(True, alpha=0.3)
    ax3.set_xlim(400, 700)
    
    # 4. 地形等高线图
    ax4 = fig.add_subplot(gs[1, 0])
    
    # 生成地形数据
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)
    
    # 模拟山峰和山谷
    Z = (np.sin(X) * np.cos(Y) * np.exp(-(X**2 + Y**2)/10) + 
         0.5 * np.sin(2*X) * np.sin(2*Y) * np.exp(-(X**2 + Y**2)/20))
    
    # 绘制等高线
    contour = ax4.contour(X, Y, Z, levels=15, colors='black', alpha=0.6, linewidths=0.8)
    contourf = ax4.contourf(X, Y, Z, levels=20, cmap='terrain', alpha=0.8)
    
    # 添加等高线标签
    ax4.clabel(contour, inline=True, fontsize=8, fmt='%.1f')
    
    ax4.set_title('地形等高线图', fontsize=12, fontweight='bold')
    ax4.set_xlabel('X (km)')
    ax4.set_ylabel('Y (km)')
    
    plt.colorbar(contourf, ax=ax4, label='海拔 (m)')
    
    # 5. 相图分析
    ax5 = fig.add_subplot(gs[1, 1])
    
    # 模拟相图数据（温度-压力）
    T = np.linspace(0, 100, 200)  # 温度
    P_solid_liquid = 1 + 0.01 * T  # 固液相界
    P_liquid_gas = np.exp((T - 100) / 20)  # 液气相界
    P_solid_gas = np.exp((T - 80) / 15)  # 固气相界（升华线）
    
    # 绘制相界线
    ax5.plot(T, P_solid_liquid, 'b-', linewidth=2, label='固-液相界')
    ax5.plot(T[T > 0], P_liquid_gas[T > 0], 'r-', linewidth=2, label='液-气相界')
    ax5.plot(T[T < 80], P_solid_gas[T < 80], 'g-', linewidth=2, label='固-气相界')
    
    # 填充相区
    ax5.fill_between(T, 0, P_solid_gas, where=(T < 80), alpha=0.3, color='lightblue', label='固相区')
    ax5.fill_between(T, P_solid_liquid, P_liquid_gas, where=(T > 0) & (T < 100), 
                    alpha=0.3, color='lightgreen', label='液相区')
    ax5.fill_between(T, 0, P_liquid_gas, where=(T > 100), alpha=0.3, color='lightyellow', label='气相区')
    
    # 标记三相点
    triple_point = (0, 1)
    ax5.plot(*triple_point, 'ko', markersize=8)
    ax5.annotate('三相点', xy=triple_point, xytext=(10, 1.5),
                arrowprops=dict(arrowstyle='->', color='black'),
                fontsize=10, fontweight='bold')
    
    ax5.set_title('物质相图', fontsize=12, fontweight='bold')
    ax5.set_xlabel('温度 (°C)')
    ax5.set_ylabel('压力 (atm)')
    ax5.legend(loc='upper left')
    ax5.grid(True, alpha=0.3)
    ax5.set_xlim(0, 100)
    ax5.set_ylim(0, 5)
    
    # 6. 数据拟合和误差分析
    ax6 = fig.add_subplot(gs[1, 2])
    
    # 生成实验数据
    np.random.seed(42)
    x_data = np.linspace(0, 10, 20)
    y_true = 2 * x_data + 1  # 真实关系
    y_data = y_true + np.random.normal(0, 1, len(x_data))  # 加入噪声
    
    # 线性拟合
    coeffs = np.polyfit(x_data, y_data, 1)
    y_fit = np.polyval(coeffs, x_data)
    
    # 计算拟合优度
    r_squared = 1 - np.sum((y_data - y_fit)**2) / np.sum((y_data - np.mean(y_data))**2)
    
    # 绘制数据点和拟合线
    ax6.errorbar(x_data, y_data, yerr=0.5, fmt='o', capsize=5, 
                capthick=2, label='实验数据', alpha=0.7)
    ax6.plot(x_data, y_fit, 'r-', linewidth=2, 
            label=f'拟合线: y = {coeffs[0]:.2f}x + {coeffs[1]:.2f}')
    ax6.plot(x_data, y_true, 'g--', linewidth=2, alpha=0.7, label='理论值')
    
    # 添加置信区间
    residuals = y_data - y_fit
    std_error = np.std(residuals)
    ax6.fill_between(x_data, y_fit - 2*std_error, y_fit + 2*std_error, 
                    alpha=0.2, color='red', label='95%置信区间')
    
    ax6.set_title(f'数据拟合分析 (R² = {r_squared:.3f})', fontsize=12, fontweight='bold')
    ax6.set_xlabel('X变量')
    ax6.set_ylabel('Y变量')
    ax6.legend()
    ax6.grid(True, alpha=0.3)
    
    plt.suptitle('科学可视化示例集合', fontsize=16, fontweight='bold')
    plt.savefig('scientific_visualization.png', dpi=300, bbox_inches='tight')
    plt.show()

def engineering_diagrams():
    """工程图表示例"""
    print("创建工程图表示例...")
    
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle('工程图表示例集合', fontsize=16, fontweight='bold')
    
    # 1. 控制系统框图
    ax1 = axes[0, 0]
    ax1.set_xlim(0, 10)
    ax1.set_ylim(0, 6)
    ax1.set_aspect('equal')
    
    # 绘制控制系统框图
    boxes = [
        {'xy': (1, 3), 'width': 1.5, 'height': 1, 'label': '控制器\nK(s)'},
        {'xy': (4, 3), 'width': 1.5, 'height': 1, 'label': '执行器\nG(s)'},
        {'xy': (7, 3), 'width': 1.5, 'height': 1, 'label': '被控对象\nP(s)'},
        {'xy': (7, 1), 'width': 1.5, 'height': 0.8, 'label': '传感器\nH(s)'}
    ]
    
    for box in boxes:
        rect = FancyBboxPatch((box['xy'][0] - box['width']/2, box['xy'][1] - box['height']/2),
                             box['width'], box['height'],
                             boxstyle="round,pad=0.1", 
                             facecolor='lightblue', 
                             edgecolor='black',
                             linewidth=2)
        ax1.add_patch(rect)
        ax1.text(box['xy'][0], box['xy'][1], box['label'], 
                ha='center', va='center', fontweight='bold', fontsize=10)
    
    # 绘制连接线和箭头
    arrows = [
        {'start': (0.5, 3.5), 'end': (1-0.75, 3.5), 'label': 'r(t)'},
        {'start': (1+0.75, 3.5), 'end': (4-0.75, 3.5), 'label': 'u(t)'},
        {'start': (4+0.75, 3.5), 'end': (7-0.75, 3.5), 'label': ''},
        {'start': (7+0.75, 3.5), 'end': (9, 3.5), 'label': 'y(t)'},
        {'start': (7.75, 3-0.5), 'end': (7.75, 1+0.4), 'label': ''},
        {'start': (7-0.75, 1.4), 'end': (1.5, 1.4), 'label': ''},
        {'start': (1.5, 1.4), 'end': (1.5, 3-0.5), 'label': ''}
    ]
    
    for arrow in arrows:
        ax1.annotate('', xy=arrow['end'], xytext=arrow['start'],
                    arrowprops=dict(arrowstyle='->', lw=2, color='red'))
        if arrow['label']:
            mid_x = (arrow['start'][0] + arrow['end'][0]) / 2
            mid_y = (arrow['start'][1] + arrow['end'][1]) / 2
            ax1.text(mid_x, mid_y + 0.2, arrow['label'], ha='center', fontweight='bold')
    
    # 添加求和点
    circle = plt.Circle((1.5, 3.5), 0.2, fill=False, edgecolor='black', linewidth=2)
    ax1.add_patch(circle)
    ax1.text(1.5, 3.5, '+', ha='center', va='center', fontsize=16, fontweight='bold')
    ax1.text(1.3, 3.2, '-', ha='center', va='center', fontsize=16, fontweight='bold')
    
    ax1.set_title('控制系统框图', fontsize=14, fontweight='bold')
    ax1.axis('off')
    
    # 2. 频率响应图（Bode图）
    ax2 = axes[0, 1]
    
    # 生成频率响应数据
    omega = np.logspace(-2, 2, 1000)  # 频率范围
    
    # 传递函数: G(s) = 100 / (s^2 + 10s + 100)
    s = 1j * omega
    H = 100 / (s**2 + 10*s + 100)
    
    magnitude_db = 20 * np.log10(np.abs(H))
    phase_deg = np.angle(H) * 180 / np.pi
    
    # 创建双Y轴
    ax2_phase = ax2.twinx()
    
    # 绘制幅频特性
    line1 = ax2.semilogx(omega, magnitude_db, 'b-', linewidth=2, label='幅频特性')
    ax2.set_ylabel('幅值 (dB)', color='blue', fontweight='bold')
    ax2.tick_params(axis='y', labelcolor='blue')
    ax2.grid(True, alpha=0.3)
    
    # 绘制相频特性
    line2 = ax2_phase.semilogx(omega, phase_deg, 'r-', linewidth=2, label='相频特性')
    ax2_phase.set_ylabel('相位 (度)', color='red', fontweight='bold')
    ax2_phase.tick_params(axis='y', labelcolor='red')
    
    ax2.set_xlabel('频率 (rad/s)')
    ax2.set_title('系统频率响应 (Bode图)', fontsize=14, fontweight='bold')
    
    # 添加图例
    lines = line1 + line2
    labels = [l.get_label() for l in lines]
    ax2.legend(lines, labels, loc='upper right')
    
    # 3. 应力-应变曲线
    ax3 = axes[1, 0]
    
    # 模拟材料的应力-应变曲线
    strain = np.linspace(0, 0.3, 1000)
    
    # 弹性阶段
    elastic_limit = 0.002
    yield_strength = 250  # MPa
    ultimate_strength = 400  # MPa
    fracture_strain = 0.25
    
    stress = np.zeros_like(strain)
    E = yield_strength / elastic_limit  # 弹性模量
    
    for i, e in enumerate(strain):
        if e <= elastic_limit:
            stress[i] = E * e  # 弹性阶段
        elif e <= 0.02:
            # 屈服阶段
            stress[i] = yield_strength + (ultimate_strength - yield_strength) * (e - elastic_limit) / (0.02 - elastic_limit)
        elif e <= fracture_strain:
            # 强化和颈缩阶段
            stress[i] = ultimate_strength * (1 - 0.5 * (e - 0.02) / (fracture_strain - 0.02))
        else:
            stress[i] = 0  # 断裂
    
    ax3.plot(strain * 100, stress, 'b-', linewidth=3, label='应力-应变曲线')
    
    # 标记关键点
    key_points = [
        (elastic_limit * 100, yield_strength, '屈服点'),
        (0.02 * 100, ultimate_strength, '抗拉强度'),
        (fracture_strain * 100, stress[np.argmin(np.abs(strain - fracture_strain))], '断裂点')
    ]
    
    for x, y, label in key_points:
        ax3.plot(x, y, 'ro', markersize=8)
        ax3.annotate(label, xy=(x, y), xytext=(x + 2, y + 20),
                    arrowprops=dict(arrowstyle='->', color='red'),
                    fontsize=10, fontweight='bold')
    
    ax3.set_xlabel('应变 (%)')
    ax3.set_ylabel('应力 (MPa)')
    ax3.set_title('材料应力-应变曲线', fontsize=14, fontweight='bold')
    ax3.grid(True, alpha=0.3)
    ax3.legend()
    
    # 4. 电路分析图
    ax4 = axes[1, 1]
    ax4.set_xlim(0, 10)
    ax4.set_ylim(0, 6)
    ax4.set_aspect('equal')
    
    # 绘制电路元件
    # 电阻
    resistor_x = [2, 2.5, 3, 3.5, 4, 4.5, 5]
    resistor_y = [4, 4.3, 3.7, 4.3, 3.7, 4.3, 4]
    ax4.plot(resistor_x, resistor_y, 'k-', linewidth=3)
    ax4.text(3.5, 4.8, 'R = 100Ω', ha='center', fontweight='bold')
    
    # 电容
    ax4.plot([6, 6], [3.5, 4.5], 'k-', linewidth=3)
    ax4.plot([6.2, 6.2], [3.5, 4.5], 'k-', linewidth=3)
    ax4.text(6.1, 4.8, 'C = 10μF', ha='center', fontweight='bold')
    
    # 电感
    inductor_x = np.linspace(7, 8, 100)
    inductor_y = 4 + 0.2 * np.sin(10 * np.pi * (inductor_x - 7))
    ax4.plot(inductor_x, inductor_y, 'k-', linewidth=3)
    ax4.text(7.5, 4.8, 'L = 1mH', ha='center', fontweight='bold')
    
    # 连接线
    connections = [
        ([1, 2], [4, 4]),  # 输入到电阻
        ([5, 6], [4, 4]),  # 电阻到电容
        ([6.2, 7], [4, 4]),  # 电容到电感
        ([8, 9], [4, 4]),  # 电感到输出
        ([1, 1, 9, 9], [4, 2, 2, 4]),  # 底部连接
    ]
    
    for x_coords, y_coords in connections:
        ax4.plot(x_coords, y_coords, 'k-', linewidth=2)
    
    # 电压源
    circle = plt.Circle((1, 3), 0.5, fill=False, edgecolor='black', linewidth=2)
    ax4.add_patch(circle)
    ax4.text(1, 3, 'V', ha='center', va='center', fontsize=16, fontweight='bold')
    ax4.text(0.3, 3, 'Vin', ha='center', fontweight='bold')
    
    # 输出
    ax4.text(9.3, 4, 'Vout', ha='center', fontweight='bold')
    
    # 添加节点标记
    nodes = [(2, 4), (5, 4), (6.2, 4), (8, 4)]
    for node in nodes:
        ax4.plot(*node, 'ko', markersize=6)
    
    ax4.set_title('RLC滤波电路', fontsize=14, fontweight='bold')
    ax4.axis('off')
    
    plt.tight_layout()
    plt.savefig('engineering_diagrams.png', dpi=300, bbox_inches='tight')
    plt.show()

def main():
    """主函数"""
    print("=" * 50)
    print("Matplotlib 专业图表示例")
    print("=" * 50)
    
    # 执行各种专业图表示例
    financial_candlestick_chart()
    portfolio_analysis_dashboard()
    scientific_visualization_examples()
    engineering_diagrams()
    
    print("\n所有专业图表示例已完成！")
    print("生成的图片文件:")
    print("- financial_candlestick.png")
    print("- portfolio_dashboard.png")
    print("- scientific_visualization.png")
    print("- engineering_diagrams.png")

if __name__ == "__main__":
    main()