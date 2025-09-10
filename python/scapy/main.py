#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scapy库完整演示程序
整合所有Scapy功能演示模块的主程序

作者: AI Assistant
版本: 1.0
日期: 2024

功能模块:
1. 基础网络包构造和操作
2. 网络扫描功能
3. 网络嗅探和包捕获
4. 协议分析和解析
5. 网络攻击模拟 (仅用于学习)
6. 无线网络分析

注意事项:
- 某些功能需要管理员权限
- 网络攻击演示仅用于学习，请勿用于非法用途
- 无线功能需要支持的硬件
- 请遵守当地法律法规
"""

import sys
import os
import importlib
from pathlib import Path

# 添加当前目录到Python路径
current_dir = Path(__file__).parent
sys.path.insert(0, str(current_dir))

def check_scapy_installation():
    """
    检查Scapy是否正确安装
    """
    try:
        import scapy
        from scapy.all import IP, TCP, UDP, ICMP, Ether
        print(f"✓ Scapy版本: {scapy.__version__}")
        return True
    except ImportError as e:
        print(f"✗ Scapy未安装或安装不完整: {e}")
        print("请运行: pip install scapy")
        return False
    except Exception as e:
        print(f"✗ Scapy导入错误: {e}")
        return False

def check_privileges():
    """
    检查运行权限
    """
    import os
    if os.name == 'nt':  # Windows
        try:
            import ctypes
            is_admin = ctypes.windll.shell32.IsUserAnAdmin()
            if is_admin:
                print("✓ 检测到管理员权限")
            else:
                print("⚠️  未检测到管理员权限，某些功能可能受限")
            return is_admin
        except:
            print("⚠️  无法检测权限状态")
            return False
    else:  # Unix/Linux/macOS
        if os.geteuid() == 0:
            print("✓ 检测到root权限")
            return True
        else:
            print("⚠️  未检测到root权限，某些功能可能需要sudo")
            return False

def load_demo_module(module_name):
    """
    动态加载演示模块
    """
    try:
        module = importlib.import_module(module_name)
        return module
    except ImportError as e:
        print(f"✗ 无法加载模块 {module_name}: {e}")
        return None
    except Exception as e:
        print(f"✗ 模块 {module_name} 加载错误: {e}")
        return None

def run_demo_safely(demo_func, demo_name):
    """
    安全运行演示函数
    """
    try:
        print(f"\n{'='*60}")
        print(f"开始运行: {demo_name}")
        print(f"{'='*60}")
        
        demo_func()
        
        print(f"\n{'='*60}")
        print(f"完成: {demo_name}")
        print(f"{'='*60}")
        
        input("\n按Enter键继续...")
        
    except KeyboardInterrupt:
        print(f"\n用户中断了 {demo_name} 的执行")
    except Exception as e:
        print(f"\n运行 {demo_name} 时发生错误: {e}")
        import traceback
        traceback.print_exc()
        input("\n按Enter键继续...")

def show_main_menu():
    """
    显示主菜单
    """
    print("\n" + "="*60)
    print("           Scapy库完整功能演示程序")
    print("="*60)
    print("\n请选择要运行的演示模块:")
    print()
    print("1. 基础网络包构造和操作演示")
    print("2. 网络扫描功能演示")
    print("3. 网络嗅探和包捕获演示")
    print("4. 协议分析和解析演示")
    print("5. 网络攻击模拟演示 (仅用于学习)")
    print("6. 无线网络分析演示")
    print()
    print("7. 运行所有演示 (按顺序)")
    print("8. 系统信息和环境检查")
    print("9. 帮助和说明")
    print("0. 退出程序")
    print()
    print("="*60)

def show_system_info():
    """
    显示系统信息和环境检查
    """
    print("\n" + "="*50)
    print("           系统信息和环境检查")
    print("="*50)
    
    # Python信息
    print(f"\nPython版本: {sys.version}")
    print(f"Python路径: {sys.executable}")
    
    # 操作系统信息
    import platform
    print(f"\n操作系统: {platform.system()} {platform.release()}")
    print(f"架构: {platform.machine()}")
    print(f"处理器: {platform.processor()}")
    
    # 网络接口信息
    try:
        from scapy.all import get_if_list, get_if_addr
        print("\n网络接口:")
        interfaces = get_if_list()
        for iface in interfaces[:5]:  # 只显示前5个接口
            try:
                addr = get_if_addr(iface)
                print(f"  {iface}: {addr}")
            except:
                print(f"  {iface}: 无法获取地址")
        if len(interfaces) > 5:
            print(f"  ... 还有 {len(interfaces)-5} 个接口")
    except Exception as e:
        print(f"\n网络接口信息获取失败: {e}")
    
    # Scapy模块检查
    print("\nScapy模块检查:")
    modules_to_check = [
        ('scapy.layers.inet', 'IP/TCP/UDP协议'),
        ('scapy.layers.l2', '数据链路层协议'),
        ('scapy.layers.dns', 'DNS协议'),
        ('scapy.layers.http', 'HTTP协议'),
        ('scapy.layers.dot11', '无线802.11协议'),
        ('scapy.utils', 'Scapy工具函数')
    ]
    
    for module_name, description in modules_to_check:
        try:
            importlib.import_module(module_name)
            print(f"  ✓ {description} ({module_name})")
        except ImportError:
            print(f"  ✗ {description} ({module_name}) - 未安装")
        except Exception as e:
            print(f"  ⚠️  {description} ({module_name}) - 错误: {e}")
    
    # 权限检查
    print("\n权限检查:")
    check_privileges()
    
    print("\n依赖包检查:")
    required_packages = [
        'scapy', 'netifaces', 'cryptography', 'matplotlib', 'numpy'
    ]
    
    for package in required_packages:
        try:
            importlib.import_module(package)
            print(f"  ✓ {package}")
        except ImportError:
            print(f"  ✗ {package} - 未安装")
        except Exception as e:
            print(f"  ⚠️  {package} - 错误: {e}")

def show_help():
    """
    显示帮助信息
    """
    print("\n" + "="*60)
    print("                    帮助和说明")
    print("="*60)
    
    print("\n📖 程序说明:")
    print("本程序是Scapy库的完整功能演示，包含6个主要模块:")
    print()
    
    modules_info = [
        ("基础网络包构造", "学习如何创建、修改和发送网络数据包"),
        ("网络扫描功能", "端口扫描、主机发现、服务识别等"),
        ("网络嗅探捕获", "监听网络流量、包过滤、流量分析"),
        ("协议分析解析", "深入分析各种网络协议的结构和内容"),
        ("攻击模拟演示", "网络安全测试技术 (仅用于学习)"),
        ("无线网络分析", "WiFi协议分析、无线安全测试")
    ]
    
    for i, (name, desc) in enumerate(modules_info, 1):
        print(f"{i}. {name}: {desc}")
    
    print("\n⚠️  重要提醒:")
    warnings = [
        "某些功能需要管理员/root权限",
        "网络攻击演示仅用于学习和授权测试",
        "请遵守当地法律法规和网络使用政策",
        "在生产环境中谨慎使用网络扫描功能",
        "无线功能需要支持监控模式的网卡"
    ]
    
    for warning in warnings:
        print(f"  • {warning}")
    
    print("\n🔧 环境要求:")
    requirements = [
        "Python 3.6+",
        "Scapy 2.4+",
        "管理员权限 (用于原始套接字)",
        "网络接口访问权限",
        "可选: 支持监控模式的无线网卡"
    ]
    
    for req in requirements:
        print(f"  • {req}")
    
    print("\n📚 学习建议:")
    suggestions = [
        "按顺序学习各个模块",
        "在虚拟环境中进行实验",
        "结合网络协议理论学习",
        "查看源代码了解实现细节",
        "参考Scapy官方文档"
    ]
    
    for suggestion in suggestions:
        print(f"  • {suggestion}")
    
    print("\n🔗 相关资源:")
    resources = [
        "Scapy官网: https://scapy.net/",
        "Scapy文档: https://scapy.readthedocs.io/",
        "GitHub: https://github.com/secdev/scapy",
        "网络协议学习: RFC文档"
    ]
    
    for resource in resources:
        print(f"  • {resource}")

def run_all_demos():
    """
    按顺序运行所有演示
    """
    print("\n开始运行所有演示模块...")
    print("注意: 这将花费较长时间，您可以随时按Ctrl+C中断")
    
    confirm = input("\n确定要继续吗? (y/N): ").strip().lower()
    if confirm not in ['y', 'yes', '是']:
        print("已取消")
        return
    
    demo_modules = [
        ('01_basic_packet_demo', '基础网络包构造和操作演示'),
        ('02_network_scanning_demo', '网络扫描功能演示'),
        ('03_packet_sniffing_demo', '网络嗅探和包捕获演示'),
        ('04_protocol_analysis_demo', '协议分析和解析演示'),
        ('05_attack_simulation_demo', '网络攻击模拟演示'),
        ('06_wireless_analysis_demo', '无线网络分析演示')
    ]
    
    for i, (module_name, demo_name) in enumerate(demo_modules, 1):
        print(f"\n[{i}/{len(demo_modules)}] 准备运行: {demo_name}")
        
        module = load_demo_module(module_name)
        if module and hasattr(module, 'main'):
            run_demo_safely(module.main, demo_name)
        else:
            print(f"跳过 {demo_name} (模块加载失败或无main函数)")
        
        if i < len(demo_modules):
            continue_choice = input("\n继续下一个演示? (Y/n): ").strip().lower()
            if continue_choice in ['n', 'no', '否']:
                print("用户选择停止")
                break
    
    print("\n所有演示完成!")

def main():
    """
    主函数
    """
    # 检查Scapy安装
    if not check_scapy_installation():
        print("\n请先安装Scapy后再运行此程序")
        return
    
    # 检查权限
    print("\n权限检查:")
    has_privileges = check_privileges()
    if not has_privileges:
        print("\n建议以管理员权限运行以获得完整功能")
    
    # 主循环
    while True:
        try:
            show_main_menu()
            choice = input("请输入选择 (0-9): ").strip()
            
            if choice == '0':
                print("\n感谢使用Scapy演示程序!")
                break
            
            elif choice == '1':
                module = load_demo_module('01_basic_packet_demo')
                if module and hasattr(module, 'main'):
                    run_demo_safely(module.main, '基础网络包构造和操作演示')
                else:
                    print("无法加载基础包演示模块")
            
            elif choice == '2':
                module = load_demo_module('02_network_scanning_demo')
                if module and hasattr(module, 'main'):
                    run_demo_safely(module.main, '网络扫描功能演示')
                else:
                    print("无法加载网络扫描演示模块")
            
            elif choice == '3':
                module = load_demo_module('03_packet_sniffing_demo')
                if module and hasattr(module, 'main'):
                    run_demo_safely(module.main, '网络嗅探和包捕获演示')
                else:
                    print("无法加载包嗅探演示模块")
            
            elif choice == '4':
                module = load_demo_module('04_protocol_analysis_demo')
                if module and hasattr(module, 'main'):
                    run_demo_safely(module.main, '协议分析和解析演示')
                else:
                    print("无法加载协议分析演示模块")
            
            elif choice == '5':
                print("\n⚠️  警告: 网络攻击模拟演示")
                print("此模块包含网络攻击技术演示，仅用于学习目的")
                print("请确保您:")
                print("1. 仅在授权的测试环境中使用")
                print("2. 遵守当地法律法规")
                print("3. 不用于恶意目的")
                
                confirm = input("\n我理解并同意上述条款 (输入 'I AGREE' 继续): ")
                if confirm == 'I AGREE':
                    module = load_demo_module('05_attack_simulation_demo')
                    if module and hasattr(module, 'main'):
                        run_demo_safely(module.main, '网络攻击模拟演示')
                    else:
                        print("无法加载攻击模拟演示模块")
                else:
                    print("已取消攻击模拟演示")
            
            elif choice == '6':
                module = load_demo_module('06_wireless_analysis_demo')
                if module and hasattr(module, 'main'):
                    run_demo_safely(module.main, '无线网络分析演示')
                else:
                    print("无法加载无线分析演示模块")
            
            elif choice == '7':
                run_all_demos()
            
            elif choice == '8':
                show_system_info()
                input("\n按Enter键继续...")
            
            elif choice == '9':
                show_help()
                input("\n按Enter键继续...")
            
            else:
                print("\n无效选择，请输入0-9之间的数字")
                input("按Enter键继续...")
        
        except KeyboardInterrupt:
            print("\n\n用户中断程序")
            break
        except Exception as e:
            print(f"\n程序运行错误: {e}")
            import traceback
            traceback.print_exc()
            input("\n按Enter键继续...")

if __name__ == "__main__":
    main()