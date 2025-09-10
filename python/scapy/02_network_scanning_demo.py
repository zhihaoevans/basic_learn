#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scapy网络扫描功能演示
演示使用Scapy进行各种网络扫描：端口扫描、主机发现、服务识别等
"""

from scapy.all import *
import threading
import time
import random
import ipaddress
from concurrent.futures import ThreadPoolExecutor, as_completed

def demo_ping_sweep():
    """
    演示Ping扫描（主机发现）
    """
    print("\n=== Ping扫描演示 ===")
    
    # 扫描本地网段的一小部分
    network = "8.8.8.0/30"  # 只扫描4个地址
    print(f"\n正在扫描网段: {network}")
    
    alive_hosts = []
    
    try:
        for ip in ipaddress.IPv4Network(network, strict=False):
            ip_str = str(ip)
            print(f"正在ping {ip_str}...", end=" ")
            
            # 发送ICMP Echo Request
            packet = IP(dst=ip_str)/ICMP()
            response = sr1(packet, timeout=1, verbose=0)
            
            if response and response.haslayer(ICMP):
                if response[ICMP].type == 0:  # Echo Reply
                    print("✓ 在线")
                    alive_hosts.append(ip_str)
                else:
                    print("✗ 离线")
            else:
                print("✗ 无响应")
    
    except Exception as e:
        print(f"\nPing扫描失败: {e}")
        print("提示: 需要管理员权限")
        return []
    
    print(f"\n发现 {len(alive_hosts)} 个在线主机: {alive_hosts}")
    return alive_hosts

def demo_tcp_port_scan(target_ip="www.google.com", ports=None):
    """
    演示TCP端口扫描
    """
    print(f"\n=== TCP端口扫描演示 (目标: {target_ip}) ===")
    
    if ports is None:
        ports = [21, 22, 23, 25, 53, 80, 110, 143, 443, 993, 995]
    
    open_ports = []
    closed_ports = []
    filtered_ports = []
    
    print(f"\n正在扫描端口: {ports}")
    
    try:
        for port in ports:
            print(f"扫描端口 {port}...", end=" ")
            
            # 发送TCP SYN包
            packet = IP(dst=target_ip)/TCP(dport=port, flags="S")
            response = sr1(packet, timeout=1, verbose=0)
            
            if response:
                if response.haslayer(TCP):
                    if response[TCP].flags == 18:  # SYN-ACK
                        print("✓ 开放")
                        open_ports.append(port)
                        
                        # 发送RST关闭连接
                        rst_packet = IP(dst=target_ip)/TCP(dport=port, flags="R")
                        send(rst_packet, verbose=0)
                        
                    elif response[TCP].flags == 4:  # RST
                        print("✗ 关闭")
                        closed_ports.append(port)
                elif response.haslayer(ICMP):
                    print("⚠ 被过滤")
                    filtered_ports.append(port)
            else:
                print("? 无响应")
                filtered_ports.append(port)
            
            time.sleep(0.1)  # 避免过快扫描
    
    except Exception as e:
        print(f"\nTCP扫描失败: {e}")
        print("提示: 需要管理员权限")
        return [], [], []
    
    print(f"\n扫描结果:")
    print(f"开放端口: {open_ports}")
    print(f"关闭端口: {closed_ports}")
    print(f"被过滤端口: {filtered_ports}")
    
    return open_ports, closed_ports, filtered_ports

def demo_udp_port_scan(target_ip="8.8.8.8", ports=None):
    """
    演示UDP端口扫描
    """
    print(f"\n=== UDP端口扫描演示 (目标: {target_ip}) ===")
    
    if ports is None:
        ports = [53, 67, 68, 69, 123, 161, 162]
    
    open_ports = []
    closed_ports = []
    filtered_ports = []
    
    print(f"\n正在扫描UDP端口: {ports}")
    
    try:
        for port in ports:
            print(f"扫描UDP端口 {port}...", end=" ")
            
            # 发送UDP包
            packet = IP(dst=target_ip)/UDP(dport=port)
            response = sr1(packet, timeout=2, verbose=0)
            
            if response:
                if response.haslayer(ICMP):
                    if response[ICMP].type == 3 and response[ICMP].code == 3:
                        print("✗ 关闭")
                        closed_ports.append(port)
                    else:
                        print("⚠ 被过滤")
                        filtered_ports.append(port)
                elif response.haslayer(UDP):
                    print("✓ 开放")
                    open_ports.append(port)
            else:
                print("? 开放或被过滤")
                filtered_ports.append(port)
            
            time.sleep(0.1)
    
    except Exception as e:
        print(f"\nUDP扫描失败: {e}")
        print("提示: 需要管理员权限")
        return [], [], []
    
    print(f"\n扫描结果:")
    print(f"开放端口: {open_ports}")
    print(f"关闭端口: {closed_ports}")
    print(f"开放或被过滤端口: {filtered_ports}")
    
    return open_ports, closed_ports, filtered_ports

def demo_stealth_scan(target_ip="www.google.com", ports=None):
    """
    演示隐蔽扫描技术
    """
    print(f"\n=== 隐蔽扫描演示 (目标: {target_ip}) ===")
    
    if ports is None:
        ports = [80, 443, 22]
    
    print("\n1. SYN扫描 (半开连接):")
    try:
        for port in ports:
            packet = IP(dst=target_ip)/TCP(dport=port, flags="S")
            response = sr1(packet, timeout=1, verbose=0)
            
            if response and response.haslayer(TCP):
                if response[TCP].flags == 18:  # SYN-ACK
                    print(f"端口 {port}: 开放")
                    # 发送RST而不是ACK，避免建立完整连接
                    rst = IP(dst=target_ip)/TCP(dport=port, flags="R")
                    send(rst, verbose=0)
                elif response[TCP].flags == 4:  # RST
                    print(f"端口 {port}: 关闭")
    except Exception as e:
        print(f"SYN扫描失败: {e}")
    
    print("\n2. FIN扫描:")
    try:
        for port in ports:
            packet = IP(dst=target_ip)/TCP(dport=port, flags="F")
            response = sr1(packet, timeout=1, verbose=0)
            
            if response and response.haslayer(TCP):
                if response[TCP].flags == 4:  # RST
                    print(f"端口 {port}: 关闭")
            else:
                print(f"端口 {port}: 可能开放")
    except Exception as e:
        print(f"FIN扫描失败: {e}")
    
    print("\n3. NULL扫描:")
    try:
        for port in ports:
            packet = IP(dst=target_ip)/TCP(dport=port, flags=0)
            response = sr1(packet, timeout=1, verbose=0)
            
            if response and response.haslayer(TCP):
                if response[TCP].flags == 4:  # RST
                    print(f"端口 {port}: 关闭")
            else:
                print(f"端口 {port}: 可能开放")
    except Exception as e:
        print(f"NULL扫描失败: {e}")

def demo_os_fingerprinting(target_ip="www.google.com"):
    """
    演示操作系统指纹识别
    """
    print(f"\n=== 操作系统指纹识别演示 (目标: {target_ip}) ===")
    
    try:
        print("\n1. TCP窗口大小检测:")
        packet = IP(dst=target_ip)/TCP(dport=80, flags="S")
        response = sr1(packet, timeout=2, verbose=0)
        
        if response and response.haslayer(TCP):
            window_size = response[TCP].window
            print(f"TCP窗口大小: {window_size}")
            
            # 简单的窗口大小判断
            if window_size == 65535:
                print("可能的操作系统: Linux/Unix")
            elif window_size == 8192:
                print("可能的操作系统: Windows")
            else:
                print(f"未知操作系统 (窗口大小: {window_size})")
        
        print("\n2. TTL值检测:")
        packet = IP(dst=target_ip)/ICMP()
        response = sr1(packet, timeout=2, verbose=0)
        
        if response and response.haslayer(IP):
            ttl = response[IP].ttl
            print(f"TTL值: {ttl}")
            
            # 简单的TTL判断
            if ttl <= 64:
                print("可能的操作系统: Linux/Unix")
            elif ttl <= 128:
                print("可能的操作系统: Windows")
            else:
                print(f"未知操作系统 (TTL: {ttl})")
        
        print("\n3. TCP选项检测:")
        packet = IP(dst=target_ip)/TCP(dport=80, flags="S", options=[("MSS", 1460)])
        response = sr1(packet, timeout=2, verbose=0)
        
        if response and response.haslayer(TCP):
            options = response[TCP].options
            print(f"TCP选项: {options}")
            
            if options:
                print("检测到TCP选项，可能支持高级TCP特性")
    
    except Exception as e:
        print(f"操作系统指纹识别失败: {e}")

def demo_service_detection(target_ip="www.google.com", port=80):
    """
    演示服务识别
    """
    print(f"\n=== 服务识别演示 (目标: {target_ip}:{port}) ===")
    
    try:
        # 1. 发送HTTP请求
        if port == 80 or port == 443:
            print("\n检测HTTP服务:")
            http_request = "GET / HTTP/1.1\r\nHost: {}\r\n\r\n".format(target_ip)
            packet = IP(dst=target_ip)/TCP(dport=port, flags="S")
            
            # 建立连接
            syn_ack = sr1(packet, timeout=2, verbose=0)
            if syn_ack and syn_ack.haslayer(TCP) and syn_ack[TCP].flags == 18:
                print(f"端口 {port} 开放，尝试HTTP请求...")
                
                # 这里只是演示，实际需要完整的TCP握手
                print("HTTP服务检测需要完整的TCP连接")
                print("建议使用socket库进行实际的服务检测")
        
        # 2. 检测SSH服务
        elif port == 22:
            print("\n检测SSH服务:")
            packet = IP(dst=target_ip)/TCP(dport=22, flags="S")
            response = sr1(packet, timeout=2, verbose=0)
            
            if response and response.haslayer(TCP) and response[TCP].flags == 18:
                print("检测到SSH服务 (端口22开放)")
        
        # 3. 检测DNS服务
        elif port == 53:
            print("\n检测DNS服务:")
            dns_query = DNS(rd=1, qd=DNSQR(qname="www.example.com"))
            packet = IP(dst=target_ip)/UDP(dport=53)/dns_query
            response = sr1(packet, timeout=2, verbose=0)
            
            if response and response.haslayer(DNS):
                print("检测到DNS服务")
                print(f"DNS响应: {response[DNS].summary()}")
    
    except Exception as e:
        print(f"服务识别失败: {e}")

def demo_traceroute(target_ip="8.8.8.8"):
    """
    演示路由跟踪
    """
    print(f"\n=== 路由跟踪演示 (目标: {target_ip}) ===")
    
    try:
        print(f"\n正在跟踪到 {target_ip} 的路由:")
        
        max_hops = 10  # 限制跳数
        for ttl in range(1, max_hops + 1):
            packet = IP(dst=target_ip, ttl=ttl)/ICMP()
            response = sr1(packet, timeout=2, verbose=0)
            
            if response:
                if response.haslayer(ICMP):
                    if response[ICMP].type == 11:  # Time Exceeded
                        print(f"{ttl:2d}. {response.src}")
                    elif response[ICMP].type == 0:  # Echo Reply
                        print(f"{ttl:2d}. {response.src} (目标到达)")
                        break
                else:
                    print(f"{ttl:2d}. {response.src}")
            else:
                print(f"{ttl:2d}. * * * (超时)")
            
            time.sleep(0.1)
    
    except Exception as e:
        print(f"路由跟踪失败: {e}")

def demo_arp_scan():
    """
    演示ARP扫描（局域网主机发现）
    """
    print("\n=== ARP扫描演示 ===")
    
    try:
        # 获取本机IP和网络
        import socket
        hostname = socket.gethostname()
        local_ip = socket.gethostbyname(hostname)
        print(f"本机IP: {local_ip}")
        
        # 构造ARP请求
        network = "192.168.1.0/28"  # 扫描小范围
        print(f"\n扫描网络: {network}")
        
        arp_request = ARP(pdst=network)
        broadcast = Ether(dst="ff:ff:ff:ff:ff:ff")
        arp_request_broadcast = broadcast / arp_request
        
        answered_list = srp(arp_request_broadcast, timeout=2, verbose=0)[0]
        
        print("\n发现的主机:")
        print("IP地址\t\t\tMAC地址")
        print("-" * 40)
        
        for element in answered_list:
            client_dict = {
                "ip": element[1].psrc,
                "mac": element[1].hwsrc
            }
            print(f"{client_dict['ip']}\t\t{client_dict['mac']}")
    
    except Exception as e:
        print(f"ARP扫描失败: {e}")
        print("提示: ARP扫描需要在局域网中运行")

def main():
    """
    主函数
    """
    print("Scapy网络扫描功能演示")
    print("=" * 50)
    
    try:
        # 基础扫描演示
        demo_ping_sweep()
        demo_tcp_port_scan()
        demo_udp_port_scan()
        
        # 高级扫描技术
        demo_stealth_scan()
        demo_os_fingerprinting()
        demo_service_detection()
        
        # 网络拓扑
        demo_traceroute()
        demo_arp_scan()
        
    except KeyboardInterrupt:
        print("\n演示被用户中断")
    except Exception as e:
        print(f"\n演示过程中发生错误: {e}")
        import traceback
        traceback.print_exc()
    
    print("\n演示完成!")
    print("\n注意事项:")
    print("1. 大部分扫描功能需要管理员权限")
    print("2. 请仅在授权的网络环境中使用")
    print("3. 扫描可能被防火墙或IDS检测到")
    print("4. 请遵守相关法律法规")

if __name__ == "__main__":
    main()