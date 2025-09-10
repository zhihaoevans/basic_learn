#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scapy网络嗅探和包捕获演示
演示使用Scapy进行网络包嗅探、捕获、过滤和分析
"""

from scapy.all import *
import threading
import time
import signal
import sys
from collections import defaultdict, Counter
import json
from datetime import datetime

# 全局变量用于控制嗅探
sniffing_active = False
packet_count = 0
packet_stats = defaultdict(int)
captured_packets = []

def demo_basic_sniffing():
    """
    演示基础包嗅探
    """
    print("\n=== 基础包嗅探演示 ===")
    
    def packet_handler(packet):
        global packet_count
        packet_count += 1
        print(f"[{packet_count}] {packet.summary()}")
        
        # 显示包的基本信息
        if packet.haslayer(IP):
            print(f"    源IP: {packet[IP].src} -> 目标IP: {packet[IP].dst}")
        
        if packet.haslayer(TCP):
            print(f"    TCP: {packet[TCP].sport} -> {packet[TCP].dport}")
        elif packet.haslayer(UDP):
            print(f"    UDP: {packet[UDP].sport} -> {packet[UDP].dport}")
        elif packet.haslayer(ICMP):
            print(f"    ICMP: 类型={packet[ICMP].type}, 代码={packet[ICMP].code}")
        
        print("-" * 60)
    
    try:
        print("\n开始基础包嗅探 (按Ctrl+C停止)...")
        print("注意: 需要管理员权限")
        
        # 嗅探5个包
        sniff(prn=packet_handler, count=5, timeout=10)
        
    except Exception as e:
        print(f"\n嗅探失败: {e}")
        print("提示: 需要管理员权限才能进行包嗅探")

def demo_filtered_sniffing():
    """
    演示过滤嗅探
    """
    print("\n=== 过滤嗅探演示 ===")
    
    filters = [
        ("tcp", "TCP流量"),
        ("udp", "UDP流量"),
        ("icmp", "ICMP流量"),
        ("port 80", "HTTP流量"),
        ("port 443", "HTTPS流量"),
        ("port 53", "DNS流量"),
        ("host 8.8.8.8", "与8.8.8.8的通信")
    ]
    
    def filtered_packet_handler(packet, filter_name):
        print(f"[{filter_name}] {packet.summary()}")
        if packet.haslayer(IP):
            print(f"    {packet[IP].src} -> {packet[IP].dst}")
    
    try:
        for bpf_filter, description in filters:
            print(f"\n正在嗅探: {description} (过滤器: {bpf_filter})")
            print("等待数据包... (3秒超时)")
            
            packets = sniff(filter=bpf_filter, count=2, timeout=3)
            
            if packets:
                for packet in packets:
                    filtered_packet_handler(packet, description)
            else:
                print("    未捕获到匹配的数据包")
            
            print("-" * 50)
    
    except Exception as e:
        print(f"\n过滤嗅探失败: {e}")

def demo_protocol_specific_sniffing():
    """
    演示特定协议嗅探
    """
    print("\n=== 特定协议嗅探演示 ===")
    
    def http_handler(packet):
        if packet.haslayer(Raw):
            payload = packet[Raw].load.decode('utf-8', errors='ignore')
            if 'HTTP' in payload:
                print(f"\n[HTTP] {packet[IP].src}:{packet[TCP].sport} -> {packet[IP].dst}:{packet[TCP].dport}")
                lines = payload.split('\r\n')
                for line in lines[:5]:  # 只显示前5行
                    if line.strip():
                        print(f"    {line}")
                print("    ...")
    
    def dns_handler(packet):
        if packet.haslayer(DNS):
            dns = packet[DNS]
            if dns.qr == 0:  # 查询
                print(f"\n[DNS查询] {packet[IP].src} -> {packet[IP].dst}")
                if dns.qd:
                    print(f"    查询: {dns.qd.qname.decode('utf-8')}")
            else:  # 响应
                print(f"\n[DNS响应] {packet[IP].src} -> {packet[IP].dst}")
                if dns.an:
                    for i in range(dns.ancount):
                        if i < len(dns.an):
                            print(f"    答案: {dns.an[i].rrname.decode('utf-8')} -> {dns.an[i].rdata}")
    
    def arp_handler(packet):
        if packet.haslayer(ARP):
            arp = packet[ARP]
            if arp.op == 1:  # ARP请求
                print(f"\n[ARP请求] 谁有 {arp.pdst}? 告诉 {arp.psrc} ({arp.hwsrc})")
            elif arp.op == 2:  # ARP响应
                print(f"\n[ARP响应] {arp.psrc} 在 {arp.hwsrc}")
    
    try:
        print("\n1. HTTP流量嗅探:")
        print("等待HTTP数据包... (5秒超时)")
        sniff(filter="tcp port 80", prn=http_handler, count=2, timeout=5)
        
        print("\n2. DNS流量嗅探:")
        print("等待DNS数据包... (5秒超时)")
        sniff(filter="udp port 53", prn=dns_handler, count=3, timeout=5)
        
        print("\n3. ARP流量嗅探:")
        print("等待ARP数据包... (5秒超时)")
        sniff(filter="arp", prn=arp_handler, count=2, timeout=5)
        
    except Exception as e:
        print(f"\n协议嗅探失败: {e}")

def demo_packet_statistics():
    """
    演示包统计分析
    """
    print("\n=== 包统计分析演示 ===")
    
    global packet_stats, captured_packets
    packet_stats.clear()
    captured_packets.clear()
    
    def stats_handler(packet):
        global packet_stats, captured_packets
        
        # 保存包用于后续分析
        captured_packets.append(packet)
        
        # 统计协议类型
        if packet.haslayer(TCP):
            packet_stats['TCP'] += 1
        elif packet.haslayer(UDP):
            packet_stats['UDP'] += 1
        elif packet.haslayer(ICMP):
            packet_stats['ICMP'] += 1
        elif packet.haslayer(ARP):
            packet_stats['ARP'] += 1
        else:
            packet_stats['其他'] += 1
        
        # 统计IP地址
        if packet.haslayer(IP):
            src_ip = packet[IP].src
            dst_ip = packet[IP].dst
            packet_stats[f'源IP_{src_ip}'] += 1
            packet_stats[f'目标IP_{dst_ip}'] += 1
        
        # 统计端口
        if packet.haslayer(TCP):
            packet_stats[f'TCP端口_{packet[TCP].dport}'] += 1
        elif packet.haslayer(UDP):
            packet_stats[f'UDP端口_{packet[UDP].dport}'] += 1
    
    try:
        print("\n开始收集网络流量统计... (10秒)")
        sniff(prn=stats_handler, timeout=10, count=20)
        
        print("\n=== 统计结果 ===")
        
        # 协议统计
        print("\n协议分布:")
        protocol_stats = {k: v for k, v in packet_stats.items() if k in ['TCP', 'UDP', 'ICMP', 'ARP', '其他']}
        for protocol, count in protocol_stats.items():
            print(f"  {protocol}: {count} 个包")
        
        # 热门IP地址
        print("\n热门源IP地址:")
        src_ips = {k.replace('源IP_', ''): v for k, v in packet_stats.items() if k.startswith('源IP_')}
        for ip, count in sorted(src_ips.items(), key=lambda x: x[1], reverse=True)[:5]:
            print(f"  {ip}: {count} 个包")
        
        # 热门端口
        print("\n热门目标端口:")
        ports = {k.split('_')[1]: v for k, v in packet_stats.items() if 'TCP端口_' in k or 'UDP端口_' in k}
        for port, count in sorted(ports.items(), key=lambda x: x[1], reverse=True)[:5]:
            print(f"  端口 {port}: {count} 个包")
        
        # 包大小统计
        if captured_packets:
            sizes = [len(packet) for packet in captured_packets]
            print(f"\n包大小统计:")
            print(f"  平均大小: {sum(sizes)/len(sizes):.1f} 字节")
            print(f"  最小包: {min(sizes)} 字节")
            print(f"  最大包: {max(sizes)} 字节")
            print(f"  总流量: {sum(sizes)} 字节")
    
    except Exception as e:
        print(f"\n统计分析失败: {e}")

def demo_packet_capture_to_file():
    """
    演示包捕获到文件
    """
    print("\n=== 包捕获到文件演示 ===")
    
    try:
        filename = "captured_packets.pcap"
        print(f"\n开始捕获包到文件: {filename} (5秒)")
        
        # 捕获包到文件
        packets = sniff(timeout=5, count=10)
        
        if packets:
            wrpcap(filename, packets)
            print(f"成功捕获 {len(packets)} 个包到文件 {filename}")
            
            # 读取并分析文件
            print(f"\n从文件读取包:")
            read_packets = rdpcap(filename)
            print(f"从文件读取了 {len(read_packets)} 个包")
            
            # 显示前几个包的摘要
            for i, packet in enumerate(read_packets[:3]):
                print(f"  包 {i+1}: {packet.summary()}")
            
            # 删除临时文件
            import os
            if os.path.exists(filename):
                os.remove(filename)
                print(f"\n已删除临时文件 {filename}")
        else:
            print("未捕获到任何包")
    
    except Exception as e:
        print(f"\n文件捕获失败: {e}")

def demo_live_packet_analysis():
    """
    演示实时包分析
    """
    print("\n=== 实时包分析演示 ===")
    
    analysis_stats = {
        'total_packets': 0,
        'protocols': Counter(),
        'top_talkers': Counter(),
        'suspicious_activity': []
    }
    
    def live_analyzer(packet):
        analysis_stats['total_packets'] += 1
        
        # 协议分析
        if packet.haslayer(TCP):
            analysis_stats['protocols']['TCP'] += 1
            
            # 检测可疑活动
            if packet[TCP].flags == 2:  # SYN包
                src_ip = packet[IP].src if packet.haslayer(IP) else "未知"
                analysis_stats['top_talkers'][src_ip] += 1
                
                # 简单的端口扫描检测
                if analysis_stats['top_talkers'][src_ip] > 5:
                    if src_ip not in [item['ip'] for item in analysis_stats['suspicious_activity']]:
                        analysis_stats['suspicious_activity'].append({
                            'ip': src_ip,
                            'activity': '可能的端口扫描',
                            'count': analysis_stats['top_talkers'][src_ip]
                        })
        
        elif packet.haslayer(UDP):
            analysis_stats['protocols']['UDP'] += 1
        elif packet.haslayer(ICMP):
            analysis_stats['protocols']['ICMP'] += 1
        
        # 每10个包显示一次统计
        if analysis_stats['total_packets'] % 10 == 0:
            print(f"\n--- 实时统计 (总包数: {analysis_stats['total_packets']}) ---")
            print(f"协议分布: {dict(analysis_stats['protocols'])}")
            
            if analysis_stats['suspicious_activity']:
                print("可疑活动:")
                for activity in analysis_stats['suspicious_activity'][-3:]:  # 显示最近3个
                    print(f"  {activity['ip']}: {activity['activity']} ({activity['count']}次)")
    
    try:
        print("\n开始实时包分析... (10秒)")
        sniff(prn=live_analyzer, timeout=10, count=30)
        
        print("\n=== 最终分析报告 ===")
        print(f"总包数: {analysis_stats['total_packets']}")
        print(f"协议分布: {dict(analysis_stats['protocols'])}")
        print(f"活跃主机: {len(analysis_stats['top_talkers'])}")
        print(f"可疑活动: {len(analysis_stats['suspicious_activity'])}")
        
    except Exception as e:
        print(f"\n实时分析失败: {e}")

def demo_custom_packet_filter():
    """
    演示自定义包过滤
    """
    print("\n=== 自定义包过滤演示 ===")
    
    def custom_filter(packet):
        """自定义过滤函数"""
        # 过滤条件1: 只要TCP包
        if not packet.haslayer(TCP):
            return False
        
        # 过滤条件2: 只要特定端口
        common_ports = [80, 443, 22, 21, 25, 53]
        if packet[TCP].dport not in common_ports and packet[TCP].sport not in common_ports:
            return False
        
        # 过滤条件3: 包大小大于100字节
        if len(packet) < 100:
            return False
        
        return True
    
    def filtered_handler(packet):
        print(f"[自定义过滤] {packet.summary()}")
        print(f"    大小: {len(packet)} 字节")
        if packet.haslayer(TCP):
            print(f"    端口: {packet[TCP].sport} -> {packet[TCP].dport}")
        print("-" * 40)
    
    try:
        print("\n应用自定义过滤器 (TCP + 常见端口 + 大小>100字节)")
        print("等待匹配的数据包... (10秒)")
        
        # 使用自定义过滤器
        sniff(lfilter=custom_filter, prn=filtered_handler, timeout=10, count=5)
        
    except Exception as e:
        print(f"\n自定义过滤失败: {e}")

def demo_packet_replay():
    """
    演示包重放
    """
    print("\n=== 包重放演示 ===")
    
    try:
        # 首先捕获一些包
        print("\n1. 捕获包用于重放...")
        captured = sniff(timeout=3, count=3)
        
        if captured:
            print(f"捕获了 {len(captured)} 个包")
            
            # 显示捕获的包
            print("\n2. 捕获的包:")
            for i, packet in enumerate(captured):
                print(f"  包 {i+1}: {packet.summary()}")
            
            # 重放包（注意：这需要管理员权限）
            print("\n3. 重放包...")
            print("注意: 包重放需要管理员权限")
            
            # 这里只是演示，实际重放可能影响网络
            print("演示模式: 不实际发送包")
            for i, packet in enumerate(captured):
                print(f"  模拟重放包 {i+1}: {packet.summary()}")
                # send(packet, verbose=0)  # 实际重放时取消注释
        else:
            print("未捕获到包")
    
    except Exception as e:
        print(f"\n包重放演示失败: {e}")

def signal_handler(sig, frame):
    """
    信号处理函数
    """
    global sniffing_active
    print("\n\n收到中断信号，停止嗅探...")
    sniffing_active = False
    sys.exit(0)

def main():
    """
    主函数
    """
    print("Scapy网络嗅探和包捕获演示")
    print("=" * 50)
    
    # 设置信号处理
    signal.signal(signal.SIGINT, signal_handler)
    
    try:
        # 基础嗅探演示
        demo_basic_sniffing()
        demo_filtered_sniffing()
        demo_protocol_specific_sniffing()
        
        # 高级分析演示
        demo_packet_statistics()
        demo_live_packet_analysis()
        demo_custom_packet_filter()
        
        # 文件操作演示
        demo_packet_capture_to_file()
        demo_packet_replay()
        
    except KeyboardInterrupt:
        print("\n演示被用户中断")
    except Exception as e:
        print(f"\n演示过程中发生错误: {e}")
        import traceback
        traceback.print_exc()
    
    print("\n演示完成!")
    print("\n注意事项:")
    print("1. 包嗅探需要管理员权限")
    print("2. 在某些系统上可能需要禁用网络接口的混杂模式")
    print("3. 嗅探可能会捕获敏感信息，请谨慎使用")
    print("4. 请遵守相关法律法规和隐私政策")
    print("5. 建议在测试环境中运行")

if __name__ == "__main__":
    main()