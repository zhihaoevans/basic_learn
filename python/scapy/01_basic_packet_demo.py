#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scapy基础网络包构造和发送演示
演示Scapy的核心功能：构造、发送和接收网络包
"""

from scapy.all import *
import time
import sys

def demo_basic_packet_construction():
    """
    演示基础网络包构造
    """
    print("\n=== 基础网络包构造演示 ===")
    
    # 1. 构造以太网帧
    print("\n1. 构造以太网帧:")
    eth = Ether(dst="ff:ff:ff:ff:ff:ff", src="00:11:22:33:44:55")
    print(f"以太网帧: {eth.summary()}")
    eth.show()
    
    # 2. 构造IP包
    print("\n2. 构造IP包:")
    ip = IP(dst="8.8.8.8", src="192.168.1.100")
    print(f"IP包: {ip.summary()}")
    ip.show()
    
    # 3. 构造TCP包
    print("\n3. 构造TCP包:")
    tcp = TCP(dport=80, sport=12345, flags="S")
    print(f"TCP包: {tcp.summary()}")
    tcp.show()
    
    # 4. 构造UDP包
    print("\n4. 构造UDP包:")
    udp = UDP(dport=53, sport=12345)
    print(f"UDP包: {udp.summary()}")
    udp.show()
    
    # 5. 构造ICMP包
    print("\n5. 构造ICMP包:")
    icmp = ICMP(type=8, code=0)  # Echo Request
    print(f"ICMP包: {icmp.summary()}")
    icmp.show()

def demo_packet_layering():
    """
    演示网络包分层构造
    """
    print("\n=== 网络包分层构造演示 ===")
    
    # 1. IP + TCP 包
    print("\n1. 构造完整的TCP SYN包:")
    packet1 = IP(dst="www.google.com")/TCP(dport=80, flags="S")
    print(f"完整包: {packet1.summary()}")
    packet1.show()
    
    # 2. IP + UDP + DNS 包
    print("\n2. 构造DNS查询包:")
    dns_query = DNS(rd=1, qd=DNSQR(qname="www.example.com"))
    packet2 = IP(dst="8.8.8.8")/UDP(dport=53)/dns_query
    print(f"DNS查询包: {packet2.summary()}")
    packet2.show()
    
    # 3. IP + ICMP 包
    print("\n3. 构造ICMP Ping包:")
    packet3 = IP(dst="8.8.8.8")/ICMP()
    print(f"Ping包: {packet3.summary()}")
    packet3.show()
    
    # 4. 带载荷的包
    print("\n4. 构造带载荷的HTTP请求包:")
    http_payload = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n"
    packet4 = IP(dst="93.184.216.34")/TCP(dport=80, flags="PA")/Raw(load=http_payload)
    print(f"HTTP请求包: {packet4.summary()}")
    packet4.show()

def demo_packet_sending():
    """
    演示网络包发送（需要管理员权限）
    """
    print("\n=== 网络包发送演示 ===")
    
    try:
        # 1. 发送ICMP ping包
        print("\n1. 发送ICMP ping包到8.8.8.8:")
        ping_packet = IP(dst="8.8.8.8")/ICMP()
        response = sr1(ping_packet, timeout=2, verbose=0)
        
        if response:
            print(f"收到回复: {response.summary()}")
            print(f"RTT: {response.time - ping_packet.sent_time:.3f}s")
        else:
            print("未收到回复")
            
    except Exception as e:
        print(f"发送ping包失败: {e}")
        print("提示: 需要管理员权限才能发送原始网络包")
    
    try:
        # 2. 发送TCP SYN包进行端口探测
        print("\n2. 发送TCP SYN包探测端口:")
        syn_packet = IP(dst="www.google.com")/TCP(dport=80, flags="S")
        response = sr1(syn_packet, timeout=2, verbose=0)
        
        if response:
            if response[TCP].flags == 18:  # SYN-ACK
                print("端口80开放 (收到SYN-ACK)")
            elif response[TCP].flags == 4:  # RST
                print("端口80关闭 (收到RST)")
            print(f"响应: {response.summary()}")
        else:
            print("未收到响应")
            
    except Exception as e:
        print(f"端口探测失败: {e}")

def demo_packet_analysis():
    """
    演示网络包分析
    """
    print("\n=== 网络包分析演示 ===")
    
    # 创建一个复杂的包进行分析
    packet = Ether()/IP(dst="192.168.1.1", src="192.168.1.100")/TCP(dport=443, sport=12345, flags="PA")/Raw(load="Hello World")
    
    print("\n1. 包的基本信息:")
    print(f"包摘要: {packet.summary()}")
    print(f"包长度: {len(packet)} 字节")
    
    print("\n2. 包的详细信息:")
    packet.show()
    
    print("\n3. 访问包的各层:")
    if packet.haslayer(Ether):
        print(f"以太网层 - 源MAC: {packet[Ether].src}, 目标MAC: {packet[Ether].dst}")
    
    if packet.haslayer(IP):
        print(f"IP层 - 源IP: {packet[IP].src}, 目标IP: {packet[IP].dst}")
        print(f"IP层 - 协议: {packet[IP].proto}, TTL: {packet[IP].ttl}")
    
    if packet.haslayer(TCP):
        print(f"TCP层 - 源端口: {packet[TCP].sport}, 目标端口: {packet[TCP].dport}")
        print(f"TCP层 - 标志位: {packet[TCP].flags}, 序列号: {packet[TCP].seq}")
    
    if packet.haslayer(Raw):
        print(f"载荷: {packet[Raw].load}")
    
    print("\n4. 包的十六进制表示:")
    hexdump(packet)
    
    print("\n5. 包的字节表示:")
    print(f"原始字节: {bytes(packet)[:50]}...")

def demo_packet_modification():
    """
    演示网络包修改
    """
    print("\n=== 网络包修改演示 ===")
    
    # 创建原始包
    original_packet = IP(dst="192.168.1.1")/TCP(dport=80)/Raw(load="Original Data")
    print("\n1. 原始包:")
    print(f"原始包: {original_packet.summary()}")
    
    # 修改IP地址
    modified_packet = original_packet.copy()
    modified_packet[IP].dst = "10.0.0.1"
    print("\n2. 修改目标IP后:")
    print(f"修改后: {modified_packet.summary()}")
    
    # 修改端口
    modified_packet[TCP].dport = 443
    print("\n3. 修改目标端口后:")
    print(f"修改后: {modified_packet.summary()}")
    
    # 修改载荷
    modified_packet[Raw].load = "Modified Data"
    print("\n4. 修改载荷后:")
    print(f"修改后: {modified_packet.summary()}")
    
    # 添加新层
    modified_packet = modified_packet/Raw(load=" Additional Data")
    print("\n5. 添加额外载荷后:")
    print(f"最终包: {modified_packet.summary()}")

def demo_packet_fields():
    """
    演示网络包字段操作
    """
    print("\n=== 网络包字段操作演示 ===")
    
    # 创建包
    packet = IP()/TCP()/Raw(load="Test Data")
    
    print("\n1. 查看所有字段:")
    print("IP层字段:")
    for field in packet[IP].fields_desc:
        field_name = field.name
        field_value = getattr(packet[IP], field_name)
        print(f"  {field_name}: {field_value}")
    
    print("\nTCP层字段:")
    for field in packet[TCP].fields_desc:
        field_name = field.name
        field_value = getattr(packet[TCP], field_name)
        print(f"  {field_name}: {field_value}")
    
    print("\n2. 字段默认值和自动计算:")
    print(f"IP版本: {packet[IP].version}")
    print(f"IP头长度: {packet[IP].ihl}")
    print(f"IP总长度: {packet[IP].len}")
    print(f"IP校验和: {packet[IP].chksum}")
    print(f"TCP校验和: {packet[TCP].chksum}")
    
    # 重新计算校验和
    del packet[IP].len
    del packet[IP].chksum
    del packet[TCP].chksum
    packet = packet.__class__(bytes(packet))
    
    print("\n3. 重新计算后的字段:")
    print(f"IP总长度: {packet[IP].len}")
    print(f"IP校验和: {packet[IP].chksum}")
    print(f"TCP校验和: {packet[TCP].chksum}")

def main():
    """
    主函数
    """
    print("Scapy基础网络包构造和发送演示")
    print("=" * 50)
    
    try:
        demo_basic_packet_construction()
        demo_packet_layering()
        demo_packet_analysis()
        demo_packet_modification()
        demo_packet_fields()
        demo_packet_sending()  # 需要管理员权限
        
    except KeyboardInterrupt:
        print("\n演示被用户中断")
    except Exception as e:
        print(f"\n演示过程中发生错误: {e}")
        import traceback
        traceback.print_exc()
    
    print("\n演示完成!")

if __name__ == "__main__":
    main()