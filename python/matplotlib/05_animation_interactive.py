#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Matplotlib 动画和交互示例
演示动态图表、事件处理、交互式可视化
"""

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
from matplotlib.widgets import Slider, Button, RadioButtons, CheckButtons
from matplotlib.patches import Circle
import time

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei', 'Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False

def basic_animation_example():
    """基础动画示例"""
    print("创建基础动画示例...")
    
    # 创建图形和轴
    fig, ax = plt.subplots(figsize=(10, 6))
    
    # 设置轴的范围
    ax.set_xlim(0, 2*np.pi)
    ax.set_ylim(-2, 2)
    ax.set_xlabel('X轴')
    ax.set_ylabel('Y轴')
    ax.set_title('动态正弦波动画')
    ax.grid(True, alpha=0.3)
    
    # 初始化空的线条
    line, = ax.plot([], [], 'b-', linewidth=2, label='sin(x + t)')
    ax.legend()
    
    # 动画函数
    def animate(frame):
        x = np.linspace(0, 2*np.pi, 100)
        y = np.sin(x + frame * 0.1)
        line.set_data(x, y)
        return line,
    
    # 创建动画
    anim = animation.FuncAnimation(fig, animate, frames=200, interval=50, blit=True, repeat=True)
    
    # 保存动画为GIF
    try:
        anim.save('basic_animation.gif', writer='pillow', fps=20)
        print("动画已保存为 basic_animation.gif")
    except Exception as e:
        print(f"保存动画时出错: {e}")
    
    plt.show()
    return anim

def scatter_animation_example():
    """散点图动画示例"""
    print("创建散点图动画示例...")
    
    # 创建图形
    fig, ax = plt.subplots(figsize=(10, 8))
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)
    ax.set_xlabel('X轴')
    ax.set_ylabel('Y轴')
    ax.set_title('粒子运动动画')
    ax.grid(True, alpha=0.3)
    
    # 初始化粒子数据
    n_particles = 50
    np.random.seed(42)
    
    # 粒子初始位置和速度
    positions = np.random.uniform(-8, 8, (n_particles, 2))
    velocities = np.random.uniform(-0.5, 0.5, (n_particles, 2))
    colors = np.random.rand(n_particles)
    sizes = np.random.uniform(20, 100, n_particles)
    
    # 创建散点图
    scat = ax.scatter(positions[:, 0], positions[:, 1], 
                     c=colors, s=sizes, alpha=0.7, cmap='viridis')
    
    def animate(frame):
        global positions, velocities
        
        # 更新位置
        positions += velocities
        
        # 边界反弹
        for i in range(n_particles):
            if positions[i, 0] <= -10 or positions[i, 0] >= 10:
                velocities[i, 0] *= -1
            if positions[i, 1] <= -10 or positions[i, 1] >= 10:
                velocities[i, 1] *= -1
        
        # 更新散点图
        scat.set_offsets(positions)
        return scat,
    
    # 创建动画
    anim = animation.FuncAnimation(fig, animate, frames=500, interval=50, blit=True, repeat=True)
    
    try:
        anim.save('scatter_animation.gif', writer='pillow', fps=20)
        print("散点动画已保存为 scatter_animation.gif")
    except Exception as e:
        print(f"保存动画时出错: {e}")
    
    plt.show()
    return anim

def bar_chart_race_example():
    """柱状图竞赛动画示例"""
    print("创建柱状图竞赛动画示例...")
    
    # 创建模拟数据
    categories = ['产品A', '产品B', '产品C', '产品D', '产品E']
    n_frames = 50
    
    # 生成随机增长数据
    np.random.seed(42)
    data = np.zeros((n_frames, len(categories)))
    data[0] = np.random.uniform(10, 50, len(categories))
    
    for i in range(1, n_frames):
        # 随机增长
        growth = np.random.uniform(-2, 5, len(categories))
        data[i] = np.maximum(data[i-1] + growth, 0)
    
    # 创建图形
    fig, ax = plt.subplots(figsize=(12, 8))
    colors = plt.cm.Set3(np.linspace(0, 1, len(categories)))
    
    def animate(frame):
        ax.clear()
        
        # 当前帧的数据
        current_data = data[frame]
        
        # 按值排序
        sorted_indices = np.argsort(current_data)[::-1]
        sorted_categories = [categories[i] for i in sorted_indices]
        sorted_values = current_data[sorted_indices]
        sorted_colors = [colors[i] for i in sorted_indices]
        
        # 绘制水平柱状图
        bars = ax.barh(range(len(categories)), sorted_values, color=sorted_colors, alpha=0.8)
        
        # 设置标签和标题
        ax.set_yticks(range(len(categories)))
        ax.set_yticklabels(sorted_categories)
        ax.set_xlabel('销售额')
        ax.set_title(f'产品销售竞赛 - 第{frame+1}周', fontsize=16, fontweight='bold')
        ax.set_xlim(0, np.max(data) * 1.1)
        
        # 添加数值标签
        for i, (bar, value) in enumerate(zip(bars, sorted_values)):
            ax.text(value + np.max(data) * 0.01, i, f'{value:.1f}', 
                   va='center', fontweight='bold')
        
        ax.grid(True, alpha=0.3, axis='x')
    
    # 创建动画
    anim = animation.FuncAnimation(fig, animate, frames=n_frames, interval=200, repeat=True)
    
    try:
        anim.save('bar_race_animation.gif', writer='pillow', fps=5)
        print("柱状图竞赛动画已保存为 bar_race_animation.gif")
    except Exception as e:
        print(f"保存动画时出错: {e}")
    
    plt.show()
    return anim

def interactive_slider_example():
    """交互式滑块示例"""
    print("创建交互式滑块示例...")
    
    # 创建图形和轴
    fig, ax = plt.subplots(figsize=(12, 8))
    plt.subplots_adjust(bottom=0.25)
    
    # 初始参数
    t = np.linspace(0, 2*np.pi, 1000)
    initial_freq = 1.0
    initial_amp = 1.0
    initial_phase = 0.0
    
    # 初始绘图
    line, = ax.plot(t, initial_amp * np.sin(initial_freq * t + initial_phase), 
                   linewidth=2, color='blue')
    ax.set_xlim(0, 2*np.pi)
    ax.set_ylim(-3, 3)
    ax.set_xlabel('时间')
    ax.set_ylabel('振幅')
    ax.set_title('交互式正弦波调节器')
    ax.grid(True, alpha=0.3)
    
    # 创建滑块轴
    ax_freq = plt.axes([0.2, 0.15, 0.5, 0.03])
    ax_amp = plt.axes([0.2, 0.10, 0.5, 0.03])
    ax_phase = plt.axes([0.2, 0.05, 0.5, 0.03])
    
    # 创建滑块
    slider_freq = Slider(ax_freq, '频率', 0.1, 5.0, valinit=initial_freq, valfmt='%.1f')
    slider_amp = Slider(ax_amp, '振幅', 0.1, 3.0, valinit=initial_amp, valfmt='%.1f')
    slider_phase = Slider(ax_phase, '相位', 0, 2*np.pi, valinit=initial_phase, valfmt='%.2f')
    
    # 更新函数
    def update(val):
        freq = slider_freq.val
        amp = slider_amp.val
        phase = slider_phase.val
        
        y = amp * np.sin(freq * t + phase)
        line.set_ydata(y)
        
        # 更新标题显示当前参数
        ax.set_title(f'交互式正弦波调节器 - 频率:{freq:.1f}, 振幅:{amp:.1f}, 相位:{phase:.2f}')
        fig.canvas.draw_idle()
    
    # 连接滑块事件
    slider_freq.on_changed(update)
    slider_amp.on_changed(update)
    slider_phase.on_changed(update)
    
    # 重置按钮
    ax_reset = plt.axes([0.8, 0.025, 0.1, 0.04])
    button_reset = Button(ax_reset, '重置')
    
    def reset(event):
        slider_freq.reset()
        slider_amp.reset()
        slider_phase.reset()
    
    button_reset.on_clicked(reset)
    
    plt.show()

def interactive_plot_selection():
    """交互式图表选择示例"""
    print("创建交互式图表选择示例...")
    
    # 创建图形
    fig, ax = plt.subplots(figsize=(12, 8))
    plt.subplots_adjust(left=0.3)
    
    # 生成数据
    t = np.linspace(0, 10, 100)
    
    # 不同的函数
    functions = {
        'sin(x)': np.sin(t),
        'cos(x)': np.cos(t),
        'sin(2x)': np.sin(2*t),
        'cos(2x)': np.cos(2*t),
        'sin(x)*exp(-x/5)': np.sin(t) * np.exp(-t/5)
    }
    
    # 初始绘图
    current_func = 'sin(x)'
    line, = ax.plot(t, functions[current_func], linewidth=2, label=current_func)
    ax.set_xlim(0, 10)
    ax.set_ylim(-1.5, 1.5)
    ax.set_xlabel('X轴')
    ax.set_ylabel('Y轴')
    ax.set_title('交互式函数选择器')
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    # 创建单选按钮
    ax_radio = plt.axes([0.05, 0.4, 0.15, 0.3])
    radio = RadioButtons(ax_radio, list(functions.keys()))
    
    def update_function(label):
        line.set_ydata(functions[label])
        line.set_label(label)
        ax.legend()
        ax.set_title(f'交互式函数选择器 - 当前: {label}')
        fig.canvas.draw_idle()
    
    radio.on_clicked(update_function)
    
    # 创建复选框用于显示/隐藏网格
    ax_check = plt.axes([0.05, 0.2, 0.15, 0.1])
    check = CheckButtons(ax_check, ['显示网格', '显示图例'], [True, True])
    
    def update_display(label):
        if label == '显示网格':
            ax.grid(not ax.get_xgridlines()[0].get_visible())
        elif label == '显示图例':
            legend = ax.get_legend()
            if legend:
                legend.set_visible(not legend.get_visible())
        fig.canvas.draw_idle()
    
    check.on_clicked(update_display)
    
    plt.show()

def mouse_interaction_example():
    """鼠标交互示例"""
    print("创建鼠标交互示例...")
    
    fig, ax = plt.subplots(figsize=(10, 8))
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 10)
    ax.set_xlabel('X轴')
    ax.set_ylabel('Y轴')
    ax.set_title('鼠标交互示例 - 点击添加点，右键删除最近的点')
    ax.grid(True, alpha=0.3)
    
    # 存储点的列表
    points = []
    scatter = ax.scatter([], [], s=100, c='red', alpha=0.7)
    
    def on_click(event):
        if event.inaxes != ax:
            return
        
        if event.button == 1:  # 左键点击
            # 添加点
            points.append((event.xdata, event.ydata))
            print(f"添加点: ({event.xdata:.2f}, {event.ydata:.2f})")
            
        elif event.button == 3:  # 右键点击
            # 删除最近的点
            if points:
                removed_point = points.pop()
                print(f"删除点: ({removed_point[0]:.2f}, {removed_point[1]:.2f})")
        
        # 更新散点图
        if points:
            x_coords, y_coords = zip(*points)
            scatter.set_offsets(list(zip(x_coords, y_coords)))
        else:
            scatter.set_offsets([])
        
        # 更新标题显示点的数量
        ax.set_title(f'鼠标交互示例 - 当前点数: {len(points)}')
        fig.canvas.draw_idle()
    
    # 连接鼠标事件
    fig.canvas.mpl_connect('button_press_event', on_click)
    
    # 添加说明文本
    ax.text(0.5, 9.5, '左键点击: 添加点\n右键点击: 删除最后一个点', 
           ha='left', va='top', fontsize=12, 
           bbox=dict(boxstyle='round', facecolor='lightyellow', alpha=0.8))
    
    plt.show()

def real_time_data_example():
    """实时数据更新示例"""
    print("创建实时数据更新示例...")
    
    # 创建图形
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))
    
    # 数据缓冲区
    max_points = 100
    x_data = []
    y1_data = []  # 随机数据
    y2_data = []  # 正弦波数据
    
    # 初始化线条
    line1, = ax1.plot([], [], 'b-', linewidth=2, label='随机数据')
    line2, = ax2.plot([], [], 'r-', linewidth=2, label='正弦波数据')
    
    # 设置轴
    ax1.set_xlim(0, max_points)
    ax1.set_ylim(-3, 3)
    ax1.set_title('实时随机数据')
    ax1.set_ylabel('数值')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    ax2.set_xlim(0, max_points)
    ax2.set_ylim(-2, 2)
    ax2.set_title('实时正弦波数据')
    ax2.set_xlabel('时间步')
    ax2.set_ylabel('数值')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    def animate(frame):
        # 生成新数据点
        if len(x_data) >= max_points:
            x_data.pop(0)
            y1_data.pop(0)
            y2_data.pop(0)
        
        x_data.append(frame)
        y1_data.append(np.random.randn() + 0.1 * np.sin(frame * 0.1))  # 带趋势的随机数据
        y2_data.append(np.sin(frame * 0.2) + 0.3 * np.cos(frame * 0.05))  # 复合正弦波
        
        # 更新线条数据
        line1.set_data(range(len(x_data)), y1_data)
        line2.set_data(range(len(x_data)), y2_data)
        
        # 动态调整x轴范围
        if len(x_data) >= max_points:
            ax1.set_xlim(len(x_data) - max_points, len(x_data))
            ax2.set_xlim(len(x_data) - max_points, len(x_data))
        
        return line1, line2
    
    # 创建动画
    anim = animation.FuncAnimation(fig, animate, frames=1000, interval=100, blit=True, repeat=True)
    
    try:
        # 保存前几秒的动画
        anim.save('realtime_data.gif', writer='pillow', fps=10, frames=50)
        print("实时数据动画已保存为 realtime_data.gif")
    except Exception as e:
        print(f"保存动画时出错: {e}")
    
    plt.show()
    return anim

def interactive_3d_example():
    """交互式3D图表示例"""
    print("创建交互式3D图表示例...")
    
    from mpl_toolkits.mplot3d import Axes3D
    
    fig = plt.figure(figsize=(12, 9))
    ax = fig.add_subplot(111, projection='3d')
    
    # 生成3D数据
    u = np.linspace(0, 2 * np.pi, 50)
    v = np.linspace(0, np.pi, 50)
    U, V = np.meshgrid(u, v)
    
    # 球面参数方程
    X = np.cos(U) * np.sin(V)
    Y = np.sin(U) * np.sin(V)
    Z = np.cos(V)
    
    # 绘制3D表面
    surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8)
    
    ax.set_xlabel('X轴')
    ax.set_ylabel('Y轴')
    ax.set_zlabel('Z轴')
    ax.set_title('交互式3D球面 - 可以用鼠标旋转和缩放')
    
    # 添加颜色条
    fig.colorbar(surf, ax=ax, shrink=0.5)
    
    # 添加一些3D散点
    n_points = 20
    x_points = np.random.uniform(-1, 1, n_points)
    y_points = np.random.uniform(-1, 1, n_points)
    z_points = np.random.uniform(-1, 1, n_points)
    
    ax.scatter(x_points, y_points, z_points, c='red', s=50, alpha=0.8)
    
    plt.show()

def event_handling_example():
    """事件处理综合示例"""
    print("创建事件处理综合示例...")
    
    fig, ax = plt.subplots(figsize=(12, 8))
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 10)
    ax.set_xlabel('X轴')
    ax.set_ylabel('Y轴')
    ax.set_title('综合事件处理示例')
    ax.grid(True, alpha=0.3)
    
    # 状态变量
    drawing = False
    current_path = []
    paths = []
    
    def on_press(event):
        nonlocal drawing, current_path
        if event.inaxes != ax:
            return
        
        if event.key == 'c':  # 按C键清除所有路径
            paths.clear()
            ax.clear()
            ax.set_xlim(0, 10)
            ax.set_ylim(0, 10)
            ax.set_xlabel('X轴')
            ax.set_ylabel('Y轴')
            ax.set_title('综合事件处理示例 - 已清除')
            ax.grid(True, alpha=0.3)
            fig.canvas.draw()
            print("画布已清除")
    
    def on_mouse_press(event):
        nonlocal drawing, current_path
        if event.inaxes != ax:
            return
        
        if event.button == 1:  # 左键开始绘制
            drawing = True
            current_path = [(event.xdata, event.ydata)]
            print(f"开始绘制: ({event.xdata:.2f}, {event.ydata:.2f})")
    
    def on_mouse_move(event):
        nonlocal drawing, current_path
        if not drawing or event.inaxes != ax:
            return
        
        current_path.append((event.xdata, event.ydata))
        
        # 绘制当前路径
        if len(current_path) > 1:
            x_coords, y_coords = zip(*current_path)
            ax.plot(x_coords, y_coords, 'b-', alpha=0.7, linewidth=2)
            fig.canvas.draw_idle()
    
    def on_mouse_release(event):
        nonlocal drawing, current_path
        if not drawing:
            return
        
        drawing = False
        if len(current_path) > 1:
            paths.append(current_path.copy())
            print(f"完成绘制，路径长度: {len(current_path)}")
        current_path = []
    
    # 连接事件
    fig.canvas.mpl_connect('key_press_event', on_press)
    fig.canvas.mpl_connect('button_press_event', on_mouse_press)
    fig.canvas.mpl_connect('motion_notify_event', on_mouse_move)
    fig.canvas.mpl_connect('button_release_event', on_mouse_release)
    
    # 添加说明
    instruction_text = (
        "操作说明:\n"
        "• 按住左键拖拽: 绘制路径\n"
        "• 按 'C' 键: 清除画布\n"
        "• 可以绘制多条路径"
    )
    
    ax.text(0.5, 9.5, instruction_text, ha='left', va='top', fontsize=10,
           bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.8))
    
    plt.show()

def main():
    """主函数"""
    print("=" * 50)
    print("Matplotlib 动画和交互示例")
    print("=" * 50)
    
    # 注意：在某些环境中，动画可能需要特殊设置才能正常显示
    print("注意：动画示例需要支持GUI的环境才能正常显示")
    print("如果在Jupyter notebook中运行，请使用 %matplotlib widget")
    print()
    
    try:
        # 基础动画示例
        print("1. 基础动画示例")
        basic_animation_example()
        
        print("\n2. 散点图动画示例")
        scatter_animation_example()
        
        print("\n3. 柱状图竞赛动画")
        bar_chart_race_example()
        
        print("\n4. 交互式滑块示例")
        interactive_slider_example()
        
        print("\n5. 交互式图表选择")
        interactive_plot_selection()
        
        print("\n6. 鼠标交互示例")
        mouse_interaction_example()
        
        print("\n7. 实时数据更新")
        real_time_data_example()
        
        print("\n8. 交互式3D图表")
        interactive_3d_example()
        
        print("\n9. 综合事件处理")
        event_handling_example()
        
    except Exception as e:
        print(f"运行示例时出错: {e}")
        print("这可能是因为当前环境不支持交互式显示")
    
    print("\n所有动画和交互示例已完成！")
    print("生成的动画文件:")
    print("- basic_animation.gif")
    print("- scatter_animation.gif")
    print("- bar_race_animation.gif")
    print("- realtime_data.gif")

if __name__ == "__main__":
    main()