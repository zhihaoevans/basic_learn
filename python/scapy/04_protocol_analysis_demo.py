#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scapy协议分析和解析演示
演示使用Scapy进行各种网络协议的深度分析和解析
"""

from scapy.all import *
import binascii
import struct
import json
from collections import defaultdict
import re

def demo_ethernet_analysis():
    """
    演示以太网帧分析
    """
    print("\n=== 以太网帧分析演示 ===")
    
    # 创建以太网帧
    eth_frame = Ether(dst="ff:ff:ff:ff:ff:ff", src="00:11:22:33:44:55", type=0x0800)
    
    print("\n1. 以太网帧结构:")
    eth_frame.show()
    
    print("\n2. 以太网帧字段分析:")
    print(f"目标MAC地址: {eth_frame.dst}")
    print(f"源MAC地址: {eth_frame.src}")
    print(f"以太网类型: 0x{eth_frame.type:04x} ({eth_frame.type})")
    
    # 以太网类型解释
    ether_types = {
        0x0800: "IPv4",
        0x0806: "ARP",
        0x86DD: "IPv6",
        0x8100: "VLAN标签"
    }
    
    if eth_frame.type in ether_types:
        print(f"协议类型: {ether_types[eth_frame.type]}")
    
    print("\n3. MAC地址分析:")
    src_mac = eth_frame.src
    oui = src_mac[:8].replace(':', '')
    print(f"源MAC OUI: {oui} (制造商标识)")
    
    # 检查是否为广播或组播
    dst_mac_int = int(eth_frame.dst.replace(':', ''), 16)
    if dst_mac_int == 0xffffffffffff:
        print("目标地址: 广播地址")
    elif dst_mac_int & 0x010000000000:
        print("目标地址: 组播地址")
    else:
        print("目标地址: 单播地址")

def demo_ip_analysis():
    """
    演示IP协议分析
    """
    print("\n=== IP协议分析演示 ===")
    
    # 创建IP包
    ip_packet = IP(dst="192.168.1.100", src="10.0.0.1", ttl=64, tos=0x10)
    
    print("\n1. IP包结构:")
    ip_packet.show()
    
    print("\n2. IP头部字段分析:")
    print(f"版本: {ip_packet.version}")
    print(f"头部长度: {ip_packet.ihl} (实际长度: {ip_packet.ihl * 4} 字节)")
    print(f"服务类型: 0x{ip_packet.tos:02x}")
    print(f"总长度: {ip_packet.len} 字节")
    print(f"标识: {ip_packet.id}")
    print(f"标志位: 0x{ip_packet.flags:x}")
    print(f"片偏移: {ip_packet.frag}")
    print(f"生存时间: {ip_packet.ttl}")
    print(f"协议: {ip_packet.proto}")
    print(f"头部校验和: 0x{ip_packet.chksum:04x}")
    print(f"源IP: {ip_packet.src}")
    print(f"目标IP: {ip_packet.dst}")
    
    print("\n3. IP地址分析:")
    import ipaddress
    
    src_ip = ipaddress.IPv4Address(ip_packet.src)
    dst_ip = ipaddress.IPv4Address(ip_packet.dst)
    
    print(f"源IP类型: {'私有' if src_ip.is_private else '公有'}")
    print(f"目标IP类型: {'私有' if dst_ip.is_private else '公有'}")
    
    # 协议类型分析
    ip_protocols = {
        1: "ICMP",
        6: "TCP",
        17: "UDP",
        2: "IGMP",
        89: "OSPF"
    }
    
    if ip_packet.proto in ip_protocols:
        print(f"上层协议: {ip_protocols[ip_packet.proto]}")
    
    print("\n4. TOS字段分析:")
    tos = ip_packet.tos
    precedence = (tos >> 5) & 0x7
    delay = (tos >> 4) & 0x1
    throughput = (tos >> 3) & 0x1
    reliability = (tos >> 2) & 0x1
    
    print(f"优先级: {precedence}")
    print(f"延迟要求: {'低延迟' if delay else '正常延迟'}")
    print(f"吞吐量要求: {'高吞吐量' if throughput else '正常吞吐量'}")
    print(f"可靠性要求: {'高可靠性' if reliability else '正常可靠性'}")

def demo_tcp_analysis():
    """
    演示TCP协议分析
    """
    print("\n=== TCP协议分析演示 ===")
    
    # 创建TCP包
    tcp_packet = TCP(sport=12345, dport=80, flags="PA", seq=1000, ack=2000, window=8192)
    
    print("\n1. TCP包结构:")
    tcp_packet.show()
    
    print("\n2. TCP头部字段分析:")
    print(f"源端口: {tcp_packet.sport}")
    print(f"目标端口: {tcp_packet.dport}")
    print(f"序列号: {tcp_packet.seq}")
    print(f"确认号: {tcp_packet.ack}")
    print(f"数据偏移: {tcp_packet.dataofs} (头部长度: {tcp_packet.dataofs * 4} 字节)")
    print(f"保留位: {tcp_packet.reserved}")
    print(f"标志位: 0x{tcp_packet.flags:02x}")
    print(f"窗口大小: {tcp_packet.window}")
    print(f"校验和: 0x{tcp_packet.chksum:04x}")
    print(f"紧急指针: {tcp_packet.urgptr}")
    
    print("\n3. TCP标志位分析:")
    flags = tcp_packet.flags
    flag_names = ['FIN', 'SYN', 'RST', 'PSH', 'ACK', 'URG', 'ECE', 'CWR']
    
    for i, flag_name in enumerate(flag_names):
        if flags & (1 << i):
            print(f"  {flag_name}: 设置")
        else:
            print(f"  {flag_name}: 未设置")
    
    print("\n4. 端口服务分析:")
    common_ports = {
        20: "FTP数据", 21: "FTP控制", 22: "SSH", 23: "Telnet",
        25: "SMTP", 53: "DNS", 80: "HTTP", 110: "POP3",
        143: "IMAP", 443: "HTTPS", 993: "IMAPS", 995: "POP3S"
    }
    
    if tcp_packet.dport in common_ports:
        print(f"目标端口服务: {common_ports[tcp_packet.dport]}")
    if tcp_packet.sport in common_ports:
        print(f"源端口服务: {common_ports[tcp_packet.sport]}")
    
    print("\n5. TCP选项分析:")
    if tcp_packet.options:
        for option in tcp_packet.options:
            print(f"  选项: {option}")
    else:
        print("  无TCP选项")

def demo_udp_analysis():
    """
    演示UDP协议分析
    """
    print("\n=== UDP协议分析演示 ===")
    
    # 创建UDP包
    udp_packet = UDP(sport=12345, dport=53)
    
    print("\n1. UDP包结构:")
    udp_packet.show()
    
    print("\n2. UDP头部字段分析:")
    print(f"源端口: {udp_packet.sport}")
    print(f"目标端口: {udp_packet.dport}")
    print(f"长度: {udp_packet.len} 字节")
    print(f"校验和: 0x{udp_packet.chksum:04x}")
    
    print("\n3. UDP特性分析:")
    print("- 无连接协议")
    print("- 不保证可靠传输")
    print("- 头部开销小 (8字节)")
    print("- 适用于实时应用")
    
    print("\n4. 常见UDP服务:")
    udp_services = {
        53: "DNS", 67: "DHCP服务器", 68: "DHCP客户端",
        69: "TFTP", 123: "NTP", 161: "SNMP", 162: "SNMP Trap",
        514: "Syslog", 1194: "OpenVPN"
    }
    
    if udp_packet.dport in udp_services:
        print(f"目标端口服务: {udp_services[udp_packet.dport]}")

def demo_icmp_analysis():
    """
    演示ICMP协议分析
    """
    print("\n=== ICMP协议分析演示 ===")
    
    # 创建不同类型的ICMP包
    icmp_types = [
        (8, 0, "Echo Request (Ping)"),
        (0, 0, "Echo Reply (Pong)"),
        (3, 0, "Destination Unreachable - Network"),
        (3, 1, "Destination Unreachable - Host"),
        (3, 3, "Destination Unreachable - Port"),
        (11, 0, "Time Exceeded - TTL"),
        (5, 0, "Redirect")
    ]
    
    for icmp_type, icmp_code, description in icmp_types:
        print(f"\n{description}:")
        icmp_packet = ICMP(type=icmp_type, code=icmp_code)
        
        print(f"  类型: {icmp_packet.type}")
        print(f"  代码: {icmp_packet.code}")
        print(f"  校验和: 0x{icmp_packet.chksum:04x}")
        
        if icmp_type == 8 or icmp_type == 0:  # Echo Request/Reply
            print(f"  标识符: {icmp_packet.id}")
            print(f"  序列号: {icmp_packet.seq}")
    
    print("\n常见ICMP消息类型:")
    icmp_messages = {
        0: "Echo Reply",
        3: "Destination Unreachable",
        4: "Source Quench",
        5: "Redirect",
        8: "Echo Request",
        11: "Time Exceeded",
        12: "Parameter Problem",
        13: "Timestamp Request",
        14: "Timestamp Reply"
    }
    
    for msg_type, description in icmp_messages.items():
        print(f"  类型 {msg_type}: {description}")

def demo_dns_analysis():
    """
    演示DNS协议分析
    """
    print("\n=== DNS协议分析演示 ===")
    
    # 创建DNS查询
    dns_query = DNS(
        id=12345,
        qr=0,  # 查询
        opcode=0,  # 标准查询
        rd=1,  # 递归查询
        qd=DNSQR(qname="www.example.com", qtype="A")
    )
    
    print("\n1. DNS查询包结构:")
    dns_query.show()
    
    print("\n2. DNS头部字段分析:")
    print(f"事务ID: {dns_query.id}")
    print(f"查询/响应标志: {'响应' if dns_query.qr else '查询'}")
    print(f"操作码: {dns_query.opcode}")
    print(f"权威答案: {'是' if dns_query.aa else '否'}")
    print(f"截断标志: {'是' if dns_query.tc else '否'}")
    print(f"递归期望: {'是' if dns_query.rd else '否'}")
    print(f"递归可用: {'是' if dns_query.ra else '否'}")
    print(f"响应码: {dns_query.rcode}")
    
    print("\n3. DNS查询部分:")
    if dns_query.qd:
        print(f"查询名称: {dns_query.qd.qname.decode('utf-8')}")
        print(f"查询类型: {dns_query.qd.qtype}")
        print(f"查询类: {dns_query.qd.qclass}")
    
    # 创建DNS响应
    dns_response = DNS(
        id=12345,
        qr=1,  # 响应
        aa=1,  # 权威答案
        rd=1,
        ra=1,
        qd=DNSQR(qname="www.example.com", qtype="A"),
        an=DNSRR(rrname="www.example.com", type="A", rdata="93.184.216.34", ttl=3600)
    )
    
    print("\n4. DNS响应包分析:")
    print(f"答案记录数: {dns_response.ancount}")
    if dns_response.an:
        print(f"答案名称: {dns_response.an.rrname.decode('utf-8')}")
        print(f"记录类型: {dns_response.an.type}")
        print(f"TTL: {dns_response.an.ttl} 秒")
        print(f"数据: {dns_response.an.rdata}")
    
    print("\n5. DNS记录类型:")
    dns_types = {
        1: "A (IPv4地址)",
        2: "NS (名称服务器)",
        5: "CNAME (别名)",
        6: "SOA (授权开始)",
        12: "PTR (指针记录)",
        15: "MX (邮件交换)",
        16: "TXT (文本记录)",
        28: "AAAA (IPv6地址)"
    }
    
    for record_type, description in dns_types.items():
        print(f"  类型 {record_type}: {description}")

def demo_arp_analysis():
    """
    演示ARP协议分析
    """
    print("\n=== ARP协议分析演示 ===")
    
    # 创建ARP请求
    arp_request = ARP(
        hwtype=1,  # 以太网
        ptype=0x0800,  # IPv4
        hwlen=6,  # MAC地址长度
        plen=4,  # IP地址长度
        op=1,  # ARP请求
        hwsrc="00:11:22:33:44:55",
        psrc="192.168.1.100",
        hwdst="00:00:00:00:00:00",
        pdst="192.168.1.1"
    )
    
    print("\n1. ARP请求包结构:")
    arp_request.show()
    
    print("\n2. ARP头部字段分析:")
    print(f"硬件类型: {arp_request.hwtype} ({'以太网' if arp_request.hwtype == 1 else '其他'})")
    print(f"协议类型: 0x{arp_request.ptype:04x} ({'IPv4' if arp_request.ptype == 0x0800 else '其他'})")
    print(f"硬件地址长度: {arp_request.hwlen} 字节")
    print(f"协议地址长度: {arp_request.plen} 字节")
    print(f"操作码: {arp_request.op}")
    
    # 操作码解释
    arp_ops = {
        1: "ARP请求",
        2: "ARP响应",
        3: "RARP请求",
        4: "RARP响应"
    }
    
    if arp_request.op in arp_ops:
        print(f"操作类型: {arp_ops[arp_request.op]}")
    
    print(f"发送方MAC: {arp_request.hwsrc}")
    print(f"发送方IP: {arp_request.psrc}")
    print(f"目标MAC: {arp_request.hwdst}")
    print(f"目标IP: {arp_request.pdst}")
    
    # 创建ARP响应
    arp_response = ARP(
        op=2,  # ARP响应
        hwsrc="aa:bb:cc:dd:ee:ff",
        psrc="192.168.1.1",
        hwdst="00:11:22:33:44:55",
        pdst="192.168.1.100"
    )
    
    print("\n3. ARP响应包分析:")
    print(f"操作类型: {arp_ops[arp_response.op]}")
    print(f"响应方MAC: {arp_response.hwsrc}")
    print(f"响应方IP: {arp_response.psrc}")

def demo_http_analysis():
    """
    演示HTTP协议分析
    """
    print("\n=== HTTP协议分析演示 ===")
    
    # 创建HTTP请求
    http_request = """GET /index.html HTTP/1.1\r
Host: www.example.com\r
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)\r
Accept: text/html,application/xhtml+xml\r
Accept-Language: en-US,en;q=0.9\r
Connection: keep-alive\r
\r
"""
    
    print("\n1. HTTP请求分析:")
    lines = http_request.strip().split('\r\n')
    
    # 解析请求行
    request_line = lines[0]
    method, path, version = request_line.split(' ')
    print(f"请求方法: {method}")
    print(f"请求路径: {path}")
    print(f"HTTP版本: {version}")
    
    # 解析头部
    print("\n请求头部:")
    for line in lines[1:]:
        if line:
            if ':' in line:
                header, value = line.split(':', 1)
                print(f"  {header.strip()}: {value.strip()}")
    
    # HTTP响应
    http_response = """HTTP/1.1 200 OK\r
Content-Type: text/html; charset=UTF-8\r
Content-Length: 1234\r
Server: Apache/2.4.41\r
Date: Mon, 01 Jan 2024 12:00:00 GMT\r
Connection: keep-alive\r
\r
<html><body>Hello World</body></html>"""
    
    print("\n2. HTTP响应分析:")
    response_lines = http_response.split('\r\n')
    
    # 解析状态行
    status_line = response_lines[0]
    version, status_code, reason_phrase = status_line.split(' ', 2)
    print(f"HTTP版本: {version}")
    print(f"状态码: {status_code}")
    print(f"原因短语: {reason_phrase}")
    
    # 状态码分析
    status_categories = {
        '1': '信息性响应',
        '2': '成功响应',
        '3': '重定向',
        '4': '客户端错误',
        '5': '服务器错误'
    }
    
    category = status_categories.get(status_code[0], '未知')
    print(f"状态类别: {category}")
    
    # 解析响应头部
    print("\n响应头部:")
    body_start = False
    for line in response_lines[1:]:
        if not line:
            body_start = True
            continue
        if not body_start and ':' in line:
            header, value = line.split(':', 1)
            print(f"  {header.strip()}: {value.strip()}")
        elif body_start:
            print(f"\n响应体: {line[:50]}...")
            break

def demo_packet_payload_analysis():
    """
    演示数据包载荷分析
    """
    print("\n=== 数据包载荷分析演示 ===")
    
    # 创建带载荷的包
    payload_data = b"Hello, this is test data for payload analysis!"
    packet = IP(dst="192.168.1.1")/TCP(dport=80)/Raw(load=payload_data)
    
    print("\n1. 载荷基本信息:")
    if packet.haslayer(Raw):
        payload = packet[Raw].load
        print(f"载荷长度: {len(payload)} 字节")
        print(f"载荷类型: {type(payload)}")
        
        # 尝试解码为文本
        try:
            text = payload.decode('utf-8')
            print(f"文本内容: {text}")
        except UnicodeDecodeError:
            print("载荷包含二进制数据")
        
        # 十六进制显示
        print(f"十六进制: {payload.hex()}")
        
        # 字节分析
        print("\n2. 载荷字节分析:")
        printable_chars = sum(1 for b in payload if 32 <= b <= 126)
        print(f"可打印字符: {printable_chars}/{len(payload)} ({printable_chars/len(payload)*100:.1f}%)")
        
        # 熵分析（简单版本）
        byte_counts = [0] * 256
        for byte in payload:
            byte_counts[byte] += 1
        
        entropy = 0
        for count in byte_counts:
            if count > 0:
                p = count / len(payload)
                entropy -= p * (p.bit_length() - 1)
        
        print(f"数据熵: {entropy:.2f} (0-8, 越高越随机)")
        
        # 模式检测
        print("\n3. 载荷模式检测:")
        
        # 检测常见协议特征
        payload_str = payload.decode('utf-8', errors='ignore')
        
        if 'HTTP/' in payload_str:
            print("检测到: HTTP协议")
        elif payload_str.startswith('GET ') or payload_str.startswith('POST '):
            print("检测到: HTTP请求")
        elif 'Content-Type:' in payload_str:
            print("检测到: HTTP头部")
        elif payload[:4] == b'\x89PNG':
            print("检测到: PNG图像")
        elif payload[:2] == b'\xff\xd8':
            print("检测到: JPEG图像")
        elif payload[:4] == b'%PDF':
            print("检测到: PDF文档")
        else:
            print("未识别的载荷类型")

def demo_protocol_stack_analysis():
    """
    演示协议栈分析
    """
    print("\n=== 协议栈分析演示 ===")
    
    # 创建复杂的协议栈
    packet = Ether()/IP()/TCP()/Raw(load="HTTP data")
    
    print("\n1. 协议栈层次:")
    layer_num = 0
    current_layer = packet
    
    while current_layer:
        layer_num += 1
        layer_name = current_layer.__class__.__name__
        print(f"第{layer_num}层: {layer_name}")
        
        # 显示该层的关键字段
        if hasattr(current_layer, 'fields_desc'):
            key_fields = []
            for field in current_layer.fields_desc[:3]:  # 只显示前3个字段
                field_name = field.name
                field_value = getattr(current_layer, field_name, 'N/A')
                key_fields.append(f"{field_name}={field_value}")
            print(f"    关键字段: {', '.join(key_fields)}")
        
        current_layer = current_layer.payload if current_layer.payload else None
    
    print("\n2. 协议封装分析:")
    print(f"总包长度: {len(packet)} 字节")
    
    # 计算各层开销
    if packet.haslayer(Ether):
        eth_overhead = 14  # 以太网头部
        print(f"以太网开销: {eth_overhead} 字节")
    
    if packet.haslayer(IP):
        ip_overhead = packet[IP].ihl * 4
        print(f"IP开销: {ip_overhead} 字节")
    
    if packet.haslayer(TCP):
        tcp_overhead = packet[TCP].dataofs * 4
        print(f"TCP开销: {tcp_overhead} 字节")
    
    if packet.haslayer(Raw):
        payload_size = len(packet[Raw].load)
        print(f"实际载荷: {payload_size} 字节")
        
        total_overhead = len(packet) - payload_size
        efficiency = (payload_size / len(packet)) * 100
        print(f"协议开销: {total_overhead} 字节")
        print(f"传输效率: {efficiency:.1f}%")
    
    print("\n3. 协议关系分析:")
    print("Ethernet -> IP -> TCP -> Application Data")
    print("每层都为上层提供服务，同时添加自己的控制信息")

def main():
    """
    主函数
    """
    print("Scapy协议分析和解析演示")
    print("=" * 50)
    
    try:
        # 链路层协议
        demo_ethernet_analysis()
        demo_arp_analysis()
        
        # 网络层协议
        demo_ip_analysis()
        demo_icmp_analysis()
        
        # 传输层协议
        demo_tcp_analysis()
        demo_udp_analysis()
        
        # 应用层协议
        demo_dns_analysis()
        demo_http_analysis()
        
        # 高级分析
        demo_packet_payload_analysis()
        demo_protocol_stack_analysis()
        
    except KeyboardInterrupt:
        print("\n演示被用户中断")
    except Exception as e:
        print(f"\n演示过程中发生错误: {e}")
        import traceback
        traceback.print_exc()
    
    print("\n演示完成!")
    print("\n协议分析要点:")
    print("1. 理解各层协议的作用和字段含义")
    print("2. 掌握协议封装和解封装过程")
    print("3. 学会识别异常和恶意流量")
    print("4. 熟悉常见协议的特征和行为")
    print("5. 注意协议版本和扩展的差异")

if __name__ == "__main__":
    main()