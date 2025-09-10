#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scapy无线网络分析演示
演示使用Scapy进行无线网络分析、WiFi帧解析和无线安全测试

注意：无线网络分析需要支持监控模式的无线网卡
本演示主要展示理论和数据结构，实际使用需要特殊硬件
"""

from scapy.all import *
import time
import random
from collections import defaultdict, Counter

# 尝试导入无线相关模块
try:
    from scapy.layers.dot11 import *
    WIRELESS_AVAILABLE = True
except ImportError:
    print("警告: 无线模块不可用，将使用模拟数据演示")
    WIRELESS_AVAILABLE = False

def demo_wifi_frame_structure():
    """
    演示WiFi帧结构
    """
    print("\n=== WiFi帧结构演示 ===")
    
    if not WIRELESS_AVAILABLE:
        print("\n注意: 使用模拟数据演示WiFi帧结构")
        
        print("\n1. WiFi帧类型:")
        frame_types = {
            0: "管理帧 (Management)",
            1: "控制帧 (Control)", 
            2: "数据帧 (Data)"
        }
        
        for frame_type, description in frame_types.items():
            print(f"  类型 {frame_type}: {description}")
        
        print("\n2. 管理帧子类型:")
        mgmt_subtypes = {
            0: "Association Request",
            1: "Association Response",
            2: "Reassociation Request",
            3: "Reassociation Response",
            4: "Probe Request",
            5: "Probe Response",
            8: "Beacon",
            9: "ATIM",
            10: "Disassociation",
            11: "Authentication",
            12: "Deauthentication"
        }
        
        for subtype, description in mgmt_subtypes.items():
            print(f"    子类型 {subtype}: {description}")
        
        return
    
    # 创建各种WiFi帧
    print("\n1. Beacon帧 (信标帧):")
    beacon = Dot11(type=0, subtype=8, addr1="ff:ff:ff:ff:ff:ff", addr2="aa:bb:cc:dd:ee:ff", addr3="aa:bb:cc:dd:ee:ff")
    beacon.show()
    
    print("\n2. Probe Request帧:")
    probe_req = Dot11(type=0, subtype=4, addr1="ff:ff:ff:ff:ff:ff", addr2="11:22:33:44:55:66", addr3="ff:ff:ff:ff:ff:ff")
    probe_req.show()
    
    print("\n3. Data帧:")
    data_frame = Dot11(type=2, subtype=0, addr1="aa:bb:cc:dd:ee:ff", addr2="11:22:33:44:55:66", addr3="aa:bb:cc:dd:ee:ff")
    data_frame.show()
    
    print("\n4. WiFi帧地址字段说明:")
    print("  addr1: 接收者地址 (Receiver Address)")
    print("  addr2: 发送者地址 (Transmitter Address)")
    print("  addr3: 过滤地址 (通常是BSSID或目标地址)")
    print("  addr4: 仅在WDS模式下使用")

def demo_beacon_frame_analysis():
    """
    演示Beacon帧分析
    """
    print("\n=== Beacon帧分析演示 ===")
    
    if not WIRELESS_AVAILABLE:
        print("\n模拟Beacon帧信息:")
        
        # 模拟多个AP的Beacon信息
        mock_aps = [
            {
                "ssid": "MyWiFi",
                "bssid": "aa:bb:cc:dd:ee:ff",
                "channel": 6,
                "encryption": "WPA2-PSK",
                "signal": -45,
                "vendor": "Cisco"
            },
            {
                "ssid": "GuestNetwork", 
                "bssid": "11:22:33:44:55:66",
                "channel": 11,
                "encryption": "Open",
                "signal": -67,
                "vendor": "Netgear"
            },
            {
                "ssid": "Enterprise_WiFi",
                "bssid": "99:88:77:66:55:44",
                "channel": 1,
                "encryption": "WPA2-Enterprise",
                "signal": -52,
                "vendor": "Ubiquiti"
            }
        ]
        
        print("\n发现的接入点:")
        print("SSID\t\t\tBSSID\t\t\t信道\t加密\t\t信号强度")
        print("-" * 80)
        
        for ap in mock_aps:
            print(f"{ap['ssid']:<15}\t{ap['bssid']}\t{ap['channel']}\t{ap['encryption']:<15}\t{ap['signal']} dBm")
        
        print("\n信道使用分析:")
        channel_usage = Counter([ap['channel'] for ap in mock_aps])
        for channel, count in sorted(channel_usage.items()):
            print(f"  信道 {channel}: {count} 个AP")
        
        print("\n加密类型分析:")
        encryption_types = Counter([ap['encryption'] for ap in mock_aps])
        for enc_type, count in encryption_types.items():
            print(f"  {enc_type}: {count} 个AP")
        
        return
    
    # 创建Beacon帧
    beacon = Dot11Beacon(cap="ESS")
    essid = Dot11Elt(ID="SSID", info="TestNetwork")
    rates = Dot11Elt(ID="Rates", info="\x82\x84\x8b\x96\x0c\x12\x18\x24")
    channel = Dot11Elt(ID="DSset", info="\x06")  # 信道6
    
    beacon_frame = Dot11(type=0, subtype=8, addr1="ff:ff:ff:ff:ff:ff", addr2="aa:bb:cc:dd:ee:ff", addr3="aa:bb:cc:dd:ee:ff")/beacon/essid/rates/channel
    
    print("\n1. Beacon帧结构:")
    beacon_frame.show()
    
    print("\n2. Beacon帧信息元素:")
    print(f"SSID: TestNetwork")
    print(f"信道: 6")
    print(f"支持速率: 1, 2, 5.5, 11, 6, 9, 12, 18 Mbps")
    
    print("\n3. 能力信息分析:")
    print("ESS: 基础服务集 (Infrastructure模式)")
    print("Privacy: 加密功能")
    print("Short Preamble: 短前导码支持")
    print("PBCC: 数据包二进制卷积编码")
    print("Channel Agility: 信道敏捷性")

def demo_probe_request_analysis():
    """
    演示Probe Request分析
    """
    print("\n=== Probe Request分析演示 ===")
    
    if not WIRELESS_AVAILABLE:
        print("\n模拟Probe Request活动:")
        
        # 模拟客户端探测活动
        mock_probes = [
            {
                "client_mac": "11:22:33:44:55:66",
                "ssid": "MyHomeWiFi",
                "timestamp": "2024-01-01 12:00:01",
                "signal": -45
            },
            {
                "client_mac": "11:22:33:44:55:66",
                "ssid": "Starbucks",
                "timestamp": "2024-01-01 12:00:05",
                "signal": -45
            },
            {
                "client_mac": "77:88:99:aa:bb:cc",
                "ssid": "",  # 广播探测
                "timestamp": "2024-01-01 12:00:10",
                "signal": -62
            }
        ]
        
        print("\n检测到的Probe Request:")
        print("客户端MAC\t\t\t目标SSID\t\t时间戳\t\t\t信号")
        print("-" * 75)
        
        for probe in mock_probes:
            ssid_display = probe['ssid'] if probe['ssid'] else "<广播>"
            print(f"{probe['client_mac']}\t{ssid_display:<15}\t{probe['timestamp']}\t{probe['signal']} dBm")
        
        print("\n客户端行为分析:")
        client_macs = [probe['client_mac'] for probe in mock_probes]
        client_counts = Counter(client_macs)
        
        for mac, count in client_counts.items():
            print(f"  {mac}: {count} 次探测")
            client_probes = [p for p in mock_probes if p['client_mac'] == mac]
            ssids = [p['ssid'] for p in client_probes if p['ssid']]
            if ssids:
                print(f"    探测的网络: {', '.join(ssids)}")
        
        return
    
    # 创建Probe Request帧
    probe_req = Dot11ProbeReq()
    ssid = Dot11Elt(ID="SSID", info="TargetNetwork")
    rates = Dot11Elt(ID="Rates", info="\x82\x84\x8b\x96")
    
    probe_frame = Dot11(type=0, subtype=4, addr1="ff:ff:ff:ff:ff:ff", addr2="11:22:33:44:55:66", addr3="ff:ff:ff:ff:ff:ff")/probe_req/ssid/rates
    
    print("\n1. Probe Request帧结构:")
    probe_frame.show()
    
    print("\n2. Probe Request类型:")
    print("定向探测: 指定SSID的探测请求")
    print("广播探测: 空SSID的探测请求")
    
    print("\n3. 隐私影响:")
    print("- 暴露设备曾连接的网络")
    print("- 可用于设备跟踪")
    print("- 泄露用户行为模式")

def demo_deauth_attack_theory():
    """
    演示去认证攻击原理
    """
    print("\n=== 去认证攻击原理演示 ===")
    
    print("\n1. 去认证攻击概念:")
    print("- 发送伪造的去认证帧")
    print("- 强制断开客户端连接")
    print("- 不需要知道网络密码")
    print("- 利用802.11协议缺陷")
    
    if not WIRELESS_AVAILABLE:
        print("\n2. 去认证帧结构 (模拟):")
        print("帧类型: 管理帧 (0)")
        print("子类型: 去认证 (12)")
        print("目标: 客户端MAC地址")
        print("源: AP的BSSID")
        print("原因码: 各种断开原因")
        
        print("\n3. 常见原因码:")
        reason_codes = {
            1: "未指定原因",
            2: "先前认证无效",
            3: "因离开而去认证",
            4: "由于不活动而解除关联",
            5: "AP无法处理更多关联",
            6: "来自未认证站点的Class 2帧",
            7: "来自未关联站点的Class 3帧",
            8: "因离开而解除关联"
        }
        
        for code, description in reason_codes.items():
            print(f"  {code}: {description}")
        
        return
    
    # 创建去认证帧
    deauth = Dot11Deauth(reason=7)  # Class 3 frame from nonassociated station
    
    # 客户端 -> AP 去认证
    deauth_client_to_ap = Dot11(type=0, subtype=12, addr1="aa:bb:cc:dd:ee:ff", addr2="11:22:33:44:55:66", addr3="aa:bb:cc:dd:ee:ff")/deauth
    
    # AP -> 客户端 去认证
    deauth_ap_to_client = Dot11(type=0, subtype=12, addr1="11:22:33:44:55:66", addr2="aa:bb:cc:dd:ee:ff", addr3="aa:bb:cc:dd:ee:ff")/deauth
    
    print("\n2. 去认证帧示例:")
    print("客户端->AP去认证:")
    deauth_client_to_ap.show()
    
    print("\nAP->客户端去认证:")
    deauth_ap_to_client.show()
    
    print("\n3. 攻击效果:")
    print("- 强制断开WiFi连接")
    print("- 可能触发重新认证")
    print("- 用于捕获握手包")
    print("- 拒绝服务攻击")

def demo_wps_analysis():
    """
    演示WPS协议分析
    """
    print("\n=== WPS协议分析演示 ===")
    
    print("\n1. WPS (WiFi Protected Setup) 概述:")
    print("- 简化WiFi网络配置")
    print("- 支持PIN码和按钮方式")
    print("- 存在已知安全漏洞")
    
    print("\n2. WPS配置方法:")
    wps_methods = {
        "PBC": "按钮配置 (Push Button Configuration)",
        "PIN": "PIN码配置",
        "NFC": "近场通信配置",
        "USB": "USB配置"
    }
    
    for method, description in wps_methods.items():
        print(f"  {method}: {description}")
    
    print("\n3. WPS PIN码漏洞:")
    print("- 8位PIN码实际只有7位有效")
    print("- 前4位和后3位分别验证")
    print("- 大大减少了暴力破解时间")
    print("- 从11,000,000种可能减少到11,000种")
    
    print("\n4. WPS信息元素:")
    if WIRELESS_AVAILABLE:
        # 模拟WPS信息元素
        print("WPS版本: 1.0")
        print("WPS状态: 已配置")
        print("设备密码ID: PIN码")
        print("选择的注册器: False")
        print("设备名称: AP设备")
    else:
        print("(需要无线模块支持查看详细WPS信息)")
    
    print("\n5. 安全建议:")
    print("- 禁用WPS功能")
    print("- 使用强密码的WPA2/WPA3")
    print("- 定期更新固件")
    print("- 监控未授权接入")

def demo_wifi_channel_analysis():
    """
    演示WiFi信道分析
    """
    print("\n=== WiFi信道分析演示 ===")
    
    print("\n1. 2.4GHz频段信道:")
    channels_24ghz = {
        1: 2412, 2: 2417, 3: 2422, 4: 2427, 5: 2432, 6: 2437,
        7: 2442, 8: 2447, 9: 2452, 10: 2457, 11: 2462, 12: 2467, 13: 2472
    }
    
    print("信道\t频率(MHz)\t重叠情况")
    print("-" * 40)
    for channel, freq in channels_24ghz.items():
        if channel <= 11:  # 美国常用信道
            overlap = "无重叠" if channel in [1, 6, 11] else "有重叠"
            print(f"{channel}\t{freq}\t\t{overlap}")
    
    print("\n2. 5GHz频段信道 (部分):")
    channels_5ghz = {
        36: 5180, 40: 5200, 44: 5220, 48: 5240,
        149: 5745, 153: 5765, 157: 5785, 161: 5805
    }
    
    print("信道\t频率(MHz)\t带宽")
    print("-" * 30)
    for channel, freq in channels_5ghz.items():
        print(f"{channel}\t{freq}\t\t20/40/80MHz")
    
    # 模拟信道使用情况
    print("\n3. 模拟信道使用分析:")
    mock_channel_usage = {
        1: 3, 6: 5, 11: 2, 36: 1, 149: 2
    }
    
    print("信道\tAP数量\t拥塞程度")
    print("-" * 30)
    for channel, count in mock_channel_usage.items():
        congestion = "高" if count >= 4 else "中" if count >= 2 else "低"
        print(f"{channel}\t{count}\t{congestion}")
    
    print("\n4. 信道选择建议:")
    print("- 2.4GHz: 优先选择1、6、11信道")
    print("- 5GHz: 更多可用信道，干扰较少")
    print("- 避开雷达频段 (DFS信道)")
    print("- 考虑邻近AP的信道使用")

def demo_wireless_security_analysis():
    """
    演示无线安全分析
    """
    print("\n=== 无线安全分析演示 ===")
    
    print("\n1. 加密协议对比:")
    security_protocols = {
        "Open": {"加密": "无", "安全性": "极低", "建议": "避免使用"},
        "WEP": {"加密": "RC4", "安全性": "极低", "建议": "已被破解，禁用"},
        "WPA": {"加密": "TKIP", "安全性": "低", "建议": "升级到WPA2"},
        "WPA2": {"加密": "AES-CCMP", "安全性": "高", "建议": "推荐使用"},
        "WPA3": {"加密": "AES-GCMP", "安全性": "最高", "建议": "最新标准"}
    }
    
    print("协议\t加密算法\t安全性\t建议")
    print("-" * 50)
    for protocol, info in security_protocols.items():
        print(f"{protocol}\t{info['加密']}\t\t{info['安全性']}\t{info['建议']}")
    
    print("\n2. 常见安全威胁:")
    threats = [
        "恶意AP (Evil Twin)",
        "去认证攻击",
        "WPS PIN暴力破解",
        "握手包捕获和离线破解",
        "中间人攻击",
        "流量嗅探"
    ]
    
    for i, threat in enumerate(threats, 1):
        print(f"{i}. {threat}")
    
    print("\n3. 安全检测要点:")
    detection_points = [
        "检测未加密网络",
        "识别弱加密协议",
        "发现恶意AP",
        "监控异常流量",
        "检测去认证攻击",
        "分析客户端行为"
    ]
    
    for point in detection_points:
        print(f"- {point}")
    
    print("\n4. 防护建议:")
    protection_measures = [
        "使用WPA3或WPA2加密",
        "设置强密码",
        "禁用WPS功能",
        "隐藏SSID (有限效果)",
        "启用MAC地址过滤",
        "定期更新固件",
        "使用企业级认证",
        "部署无线入侵检测系统"
    ]
    
    for measure in protection_measures:
        print(f"- {measure}")

def demo_packet_injection_wireless():
    """
    演示无线数据包注入原理
    """
    print("\n=== 无线数据包注入原理演示 ===")
    
    print("\n1. 数据包注入要求:")
    requirements = [
        "支持监控模式的无线网卡",
        "支持数据包注入的驱动",
        "适当的天线和信号强度",
        "了解目标网络参数"
    ]
    
    for req in requirements:
        print(f"- {req}")
    
    print("\n2. 注入攻击类型:")
    injection_attacks = {
        "去认证攻击": "发送去认证帧断开连接",
        "虚假AP": "创建恶意接入点",
        "握手捕获": "强制重新认证捕获握手",
        "流量重放": "重放捕获的数据包"
    }
    
    for attack, description in injection_attacks.items():
        print(f"- {attack}: {description}")
    
    print("\n3. 监控模式 vs 管理模式:")
    print("管理模式 (Managed):")
    print("  - 正常WiFi连接模式")
    print("  - 只能接收发给自己的数据")
    print("  - 无法注入任意数据包")
    
    print("\n监控模式 (Monitor):")
    print("  - 被动监听所有无线流量")
    print("  - 可以捕获所有帧类型")
    print("  - 支持数据包注入")
    print("  - 不与任何AP关联")
    
    print("\n4. 注入检测:")
    detection_methods = [
        "异常帧速率检测",
        "重复序列号检测",
        "时间戳异常检测",
        "信号强度分析",
        "帧内容一致性检查"
    ]
    
    for method in detection_methods:
        print(f"- {method}")

def main():
    """
    主函数
    """
    print("Scapy无线网络分析演示")
    print("=" * 50)
    
    if not WIRELESS_AVAILABLE:
        print("\n⚠️  注意: 无线模块不可用")
        print("本演示将使用模拟数据展示无线网络分析概念")
        print("实际使用需要安装scapy的无线扩展模块")
        print("=" * 50)
    
    try:
        # WiFi基础分析
        demo_wifi_frame_structure()
        demo_beacon_frame_analysis()
        demo_probe_request_analysis()
        
        # 安全分析
        demo_deauth_attack_theory()
        demo_wps_analysis()
        demo_wireless_security_analysis()
        
        # 高级分析
        demo_wifi_channel_analysis()
        demo_packet_injection_wireless()
        
    except KeyboardInterrupt:
        print("\n演示被用户中断")
    except Exception as e:
        print(f"\n演示过程中发生错误: {e}")
        import traceback
        traceback.print_exc()
    
    print("\n演示完成!")
    print("\n无线网络分析要点:")
    print("1. 需要专门的硬件支持 (支持监控模式的网卡)")
    print("2. 了解802.11协议族的各种标准")
    print("3. 掌握不同帧类型的作用和结构")
    print("4. 理解无线安全协议的演进")
    print("5. 熟悉常见的无线攻击技术")
    
    print("\n法律和道德提醒:")
    print("1. 仅在授权网络中进行测试")
    print("2. 遵守当地无线电管理法规")
    print("3. 不要干扰他人的网络通信")
    print("4. 用于学习和合法的安全测试")
    print("5. 承担相应的法律责任")
    
    print("\n推荐工具和资源:")
    print("- Aircrack-ng套件")
    print("- Wireshark无线分析")
    print("- Kismet无线检测器")
    print("- WiFi Pineapple渗透测试")
    print("- 802.11标准文档")

if __name__ == "__main__":
    main()