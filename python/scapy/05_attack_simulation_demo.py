#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scapy网络攻击模拟演示
演示使用Scapy进行各种网络攻击技术的模拟（仅用于教学和安全研究）

警告：本代码仅用于教育目的和授权的安全测试环境
请勿在未经授权的网络中使用这些技术
"""

from scapy.all import *
import threading
import time
import random
import sys
from collections import defaultdict

# 全局变量
attack_active = False
arp_table = {}

def demo_arp_spoofing_theory():
    """
    演示ARP欺骗原理（理论演示）
    """
    print("\n=== ARP欺骗原理演示 ===")
    
    print("\n1. ARP协议基础:")
    print("- ARP用于将IP地址解析为MAC地址")
    print("- 主机维护ARP缓存表")
    print("- ARP请求是广播，ARP响应是单播")
    print("- ARP协议没有身份验证机制")
    
    print("\n2. ARP欺骗原理:")
    print("- 攻击者发送虚假的ARP响应")
    print("- 将目标IP地址映射到攻击者的MAC地址")
    print("- 受害者更新ARP缓存表")
    print("- 流量被重定向到攻击者")
    
    # 创建正常的ARP响应
    print("\n3. 正常ARP响应示例:")
    normal_arp = ARP(
        op=2,  # ARP响应
        hwsrc="aa:bb:cc:dd:ee:ff",  # 网关真实MAC
        psrc="192.168.1.1",        # 网关IP
        hwdst="11:22:33:44:55:66",  # 受害者MAC
        pdst="192.168.1.100"       # 受害者IP
    )
    print(f"正常响应: {normal_arp.summary()}")
    
    # 创建恶意的ARP响应
    print("\n4. 恶意ARP响应示例:")
    malicious_arp = ARP(
        op=2,  # ARP响应
        hwsrc="99:88:77:66:55:44",  # 攻击者MAC
        psrc="192.168.1.1",        # 网关IP（伪造）
        hwdst="11:22:33:44:55:66",  # 受害者MAC
        pdst="192.168.1.100"       # 受害者IP
    )
    print(f"恶意响应: {malicious_arp.summary()}")
    
    print("\n5. 攻击效果:")
    print("- 受害者认为网关MAC地址是攻击者的MAC")
    print("- 发往网关的数据包被发送到攻击者")
    print("- 攻击者可以截获、修改或转发数据包")

def demo_arp_scan_and_discovery():
    """
    演示ARP扫描和网络发现
    """
    print("\n=== ARP扫描和网络发现演示 ===")
    
    # 模拟本地网络扫描
    target_network = "192.168.1.0/28"  # 小范围扫描
    
    print(f"\n扫描网络: {target_network}")
    print("注意: 这是模拟演示，不会发送实际数据包")
    
    # 创建ARP扫描包
    arp_request = ARP(pdst=target_network)
    broadcast = Ether(dst="ff:ff:ff:ff:ff:ff")
    arp_request_broadcast = broadcast / arp_request
    
    print("\n1. ARP扫描包结构:")
    arp_request_broadcast.show()
    
    print("\n2. 模拟扫描结果:")
    # 模拟发现的主机
    discovered_hosts = [
        {"ip": "192.168.1.1", "mac": "aa:bb:cc:dd:ee:ff", "vendor": "路由器"},
        {"ip": "192.168.1.100", "mac": "11:22:33:44:55:66", "vendor": "Windows PC"},
        {"ip": "192.168.1.101", "mac": "66:77:88:99:aa:bb", "vendor": "iPhone"},
    ]
    
    print("发现的活跃主机:")
    print("IP地址\t\t\tMAC地址\t\t\t设备类型")
    print("-" * 60)
    for host in discovered_hosts:
        print(f"{host['ip']}\t\t{host['mac']}\t{host['vendor']}")
    
    print("\n3. 扫描技术要点:")
    print("- ARP扫描只能发现同一网段的主机")
    print("- 比ping扫描更可靠（绕过ICMP过滤）")
    print("- 可以获取MAC地址信息")
    print("- 速度快，开销小")

def demo_dns_spoofing_theory():
    """
    演示DNS欺骗原理
    """
    print("\n=== DNS欺骗原理演示 ===")
    
    print("\n1. DNS查询过程:")
    print("- 客户端发送DNS查询请求")
    print("- DNS服务器返回IP地址")
    print("- 客户端使用返回的IP地址建立连接")
    
    print("\n2. DNS欺骗原理:")
    print("- 攻击者监听DNS查询")
    print("- 抢在真实DNS服务器之前响应")
    print("- 返回恶意IP地址")
    print("- 客户端被重定向到恶意服务器")
    
    # 创建正常DNS查询
    print("\n3. 正常DNS查询示例:")
    dns_query = DNS(
        id=12345,
        qr=0,  # 查询
        rd=1,  # 递归查询
        qd=DNSQR(qname="www.example.com", qtype="A")
    )
    query_packet = IP(dst="8.8.8.8")/UDP(dport=53)/dns_query
    print(f"DNS查询: {query_packet.summary()}")
    
    # 创建正常DNS响应
    print("\n4. 正常DNS响应示例:")
    normal_response = DNS(
        id=12345,
        qr=1,  # 响应
        aa=1,  # 权威答案
        rd=1,
        ra=1,
        qd=DNSQR(qname="www.example.com", qtype="A"),
        an=DNSRR(rrname="www.example.com", type="A", rdata="93.184.216.34", ttl=3600)
    )
    normal_packet = IP(src="8.8.8.8")/UDP(sport=53)/normal_response
    print(f"正常响应: {normal_packet.summary()}")
    
    # 创建恶意DNS响应
    print("\n5. 恶意DNS响应示例:")
    malicious_response = DNS(
        id=12345,
        qr=1,  # 响应
        aa=1,  # 权威答案
        rd=1,
        ra=1,
        qd=DNSQR(qname="www.example.com", qtype="A"),
        an=DNSRR(rrname="www.example.com", type="A", rdata="192.168.1.200", ttl=3600)  # 恶意IP
    )
    malicious_packet = IP(src="8.8.8.8")/UDP(sport=53)/malicious_response
    print(f"恶意响应: {malicious_packet.summary()}")
    
    print("\n6. 攻击效果:")
    print("- 用户访问www.example.com时被重定向")
    print("- 可能访问到钓鱼网站")
    print("- 攻击者可以窃取用户凭据")

def demo_tcp_hijacking_theory():
    """
    演示TCP会话劫持原理
    """
    print("\n=== TCP会话劫持原理演示 ===")
    
    print("\n1. TCP连接基础:")
    print("- TCP使用序列号和确认号维护连接状态")
    print("- 每个数据包都有唯一的序列号")
    print("- 接收方期望特定的序列号")
    
    print("\n2. TCP劫持原理:")
    print("- 攻击者嗅探TCP连接")
    print("- 获取当前序列号和确认号")
    print("- 构造恶意TCP包插入连接")
    print("- 破坏或控制TCP会话")
    
    # 模拟正常TCP连接
    print("\n3. 正常TCP连接示例:")
    
    # SYN包
    syn_packet = IP(src="192.168.1.100", dst="192.168.1.200")/TCP(sport=12345, dport=80, flags="S", seq=1000)
    print(f"SYN: {syn_packet.summary()}")
    
    # SYN-ACK包
    syn_ack_packet = IP(src="192.168.1.200", dst="192.168.1.100")/TCP(sport=80, dport=12345, flags="SA", seq=2000, ack=1001)
    print(f"SYN-ACK: {syn_ack_packet.summary()}")
    
    # ACK包
    ack_packet = IP(src="192.168.1.100", dst="192.168.1.200")/TCP(sport=12345, dport=80, flags="A", seq=1001, ack=2001)
    print(f"ACK: {ack_packet.summary()}")
    
    # 数据包
    data_packet = IP(src="192.168.1.100", dst="192.168.1.200")/TCP(sport=12345, dport=80, flags="PA", seq=1001, ack=2001)/Raw(load="GET / HTTP/1.1\r\n\r\n")
    print(f"数据: {data_packet.summary()}")
    
    print("\n4. TCP劫持攻击示例:")
    # 攻击者插入恶意数据
    hijack_packet = IP(src="192.168.1.100", dst="192.168.1.200")/TCP(sport=12345, dport=80, flags="PA", seq=1020, ack=2001)/Raw(load="GET /malicious HTTP/1.1\r\n\r\n")
    print(f"劫持包: {hijack_packet.summary()}")
    
    # RST攻击
    rst_packet = IP(src="192.168.1.100", dst="192.168.1.200")/TCP(sport=12345, dport=80, flags="R", seq=1020)
    print(f"RST攻击: {rst_packet.summary()}")
    
    print("\n5. 攻击效果:")
    print("- 插入恶意数据到TCP流")
    print("- 重置TCP连接")
    print("- 劫持用户会话")

def demo_syn_flood_theory():
    """
    演示SYN洪水攻击原理
    """
    print("\n=== SYN洪水攻击原理演示 ===")
    
    print("\n1. TCP三次握手回顾:")
    print("- 客户端发送SYN")
    print("- 服务器响应SYN-ACK并分配资源")
    print("- 客户端发送ACK完成握手")
    
    print("\n2. SYN洪水攻击原理:")
    print("- 攻击者发送大量SYN包")
    print("- 使用伪造的源IP地址")
    print("- 服务器等待不会到来的ACK")
    print("- 耗尽服务器连接资源")
    
    print("\n3. SYN洪水攻击包示例:")
    target_ip = "192.168.1.200"
    target_port = 80
    
    for i in range(5):  # 只演示5个包
        # 随机源IP和端口
        fake_src_ip = f"10.{random.randint(1,254)}.{random.randint(1,254)}.{random.randint(1,254)}"
        fake_src_port = random.randint(1024, 65535)
        
        syn_packet = IP(src=fake_src_ip, dst=target_ip)/TCP(sport=fake_src_port, dport=target_port, flags="S")
        print(f"SYN包 {i+1}: {syn_packet.summary()}")
    
    print("\n4. 攻击特征:")
    print("- 大量来自不同IP的SYN包")
    print("- 源IP地址通常是伪造的")
    print("- 没有对应的ACK包")
    print("- 服务器半开连接数量激增")
    
    print("\n5. 防护措施:")
    print("- SYN Cookie技术")
    print("- 连接速率限制")
    print("- 防火墙过滤")
    print("- 负载均衡")

def demo_icmp_redirect_theory():
    """
    演示ICMP重定向攻击原理
    """
    print("\n=== ICMP重定向攻击原理演示 ===")
    
    print("\n1. ICMP重定向功能:")
    print("- 路由器通知主机更好的路由路径")
    print("- 优化网络路由")
    print("- 减少不必要的跳转")
    
    print("\n2. ICMP重定向攻击原理:")
    print("- 攻击者发送伪造的ICMP重定向消息")
    print("- 修改受害者的路由表")
    print("- 将流量重定向到攻击者")
    
    print("\n3. 正常ICMP重定向示例:")
    # 原始数据包（触发重定向）
    original_packet = IP(src="192.168.1.100", dst="10.0.0.1")/TCP(dport=80)
    
    # 正常的ICMP重定向
    normal_redirect = IP(src="192.168.1.1", dst="192.168.1.100")/ICMP(type=5, code=1, gw="192.168.1.254")/original_packet
    print(f"正常重定向: {normal_redirect.summary()}")
    
    print("\n4. 恶意ICMP重定向示例:")
    # 恶意的ICMP重定向
    malicious_redirect = IP(src="192.168.1.1", dst="192.168.1.100")/ICMP(type=5, code=1, gw="192.168.1.200")/original_packet
    print(f"恶意重定向: {malicious_redirect.summary()}")
    
    print("\n5. ICMP重定向类型:")
    redirect_types = {
        0: "网络重定向",
        1: "主机重定向",
        2: "服务类型和网络重定向",
        3: "服务类型和主机重定向"
    }
    
    for code, description in redirect_types.items():
        print(f"  代码 {code}: {description}")
    
    print("\n6. 攻击效果:")
    print("- 修改受害者路由表")
    print("- 流量被重定向到攻击者")
    print("- 可能导致中间人攻击")

def demo_packet_injection_theory():
    """
    演示数据包注入攻击原理
    """
    print("\n=== 数据包注入攻击原理演示 ===")
    
    print("\n1. 数据包注入基础:")
    print("- 攻击者构造恶意数据包")
    print("- 将数据包注入网络")
    print("- 伪造源地址和其他信息")
    print("- 影响网络通信")
    
    print("\n2. 常见注入攻击类型:")
    
    # ARP注入
    print("\nARP注入示例:")
    arp_inject = Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(op=2, hwsrc="aa:bb:cc:dd:ee:ff", psrc="192.168.1.1", pdst="192.168.1.100")
    print(f"ARP注入: {arp_inject.summary()}")
    
    # DNS注入
    print("\nDNS注入示例:")
    dns_inject = IP(src="8.8.8.8", dst="192.168.1.100")/UDP(sport=53, dport=12345)/DNS(id=12345, qr=1, an=DNSRR(rrname="www.example.com", rdata="192.168.1.200"))
    print(f"DNS注入: {dns_inject.summary()}")
    
    # TCP注入
    print("\nTCP注入示例:")
    tcp_inject = IP(src="192.168.1.200", dst="192.168.1.100")/TCP(sport=80, dport=12345, flags="PA", seq=1000, ack=2000)/Raw(load="HTTP/1.1 200 OK\r\n\r\nMalicious Content")
    print(f"TCP注入: {tcp_inject.summary()}")
    
    print("\n3. 注入攻击要求:")
    print("- 网络访问权限")
    print("- 了解目标协议")
    print("- 准确的时序控制")
    print("- 合适的网络位置")

def demo_mitm_attack_theory():
    """
    演示中间人攻击原理
    """
    print("\n=== 中间人攻击原理演示 ===")
    
    print("\n1. 中间人攻击概念:")
    print("- 攻击者位于通信双方之间")
    print("- 截获、修改、转发数据")
    print("- 双方都认为在与对方直接通信")
    
    print("\n2. 中间人攻击步骤:")
    print("步骤1: 获取网络访问权限")
    print("步骤2: 执行ARP欺骗")
    print("步骤3: 启用IP转发")
    print("步骤4: 截获和分析流量")
    print("步骤5: 可选择修改数据")
    
    print("\n3. 攻击场景模拟:")
    
    # 受害者 -> 攻击者 (以为是网关)
    victim_to_attacker = Ether(src="11:22:33:44:55:66", dst="99:88:77:66:55:44")/IP(src="192.168.1.100", dst="8.8.8.8")/TCP(dport=80)/Raw(load="GET /login HTTP/1.1")
    print(f"受害者->攻击者: {victim_to_attacker.summary()}")
    
    # 攻击者 -> 网关 (转发数据)
    attacker_to_gateway = Ether(src="99:88:77:66:55:44", dst="aa:bb:cc:dd:ee:ff")/IP(src="192.168.1.100", dst="8.8.8.8")/TCP(dport=80)/Raw(load="GET /login HTTP/1.1")
    print(f"攻击者->网关: {attacker_to_gateway.summary()}")
    
    # 网关 -> 攻击者 (响应)
    gateway_to_attacker = Ether(src="aa:bb:cc:dd:ee:ff", dst="99:88:77:66:55:44")/IP(src="8.8.8.8", dst="192.168.1.100")/TCP(sport=80)/Raw(load="HTTP/1.1 200 OK")
    print(f"网关->攻击者: {gateway_to_attacker.summary()}")
    
    # 攻击者 -> 受害者 (修改后的响应)
    attacker_to_victim = Ether(src="99:88:77:66:55:44", dst="11:22:33:44:55:66")/IP(src="8.8.8.8", dst="192.168.1.100")/TCP(sport=80)/Raw(load="HTTP/1.1 200 OK (Modified)")
    print(f"攻击者->受害者: {attacker_to_victim.summary()}")
    
    print("\n4. 攻击能力:")
    print("- 窃取敏感信息")
    print("- 修改传输数据")
    print("- 注入恶意内容")
    print("- 会话劫持")
    
    print("\n5. 防护措施:")
    print("- 使用HTTPS/TLS加密")
    print("- 静态ARP表")
    print("- 网络分段")
    print("- 入侵检测系统")

def demo_attack_detection():
    """
    演示攻击检测技术
    """
    print("\n=== 攻击检测技术演示 ===")
    
    print("\n1. ARP欺骗检测:")
    print("检测方法:")
    print("- 监控ARP表变化")
    print("- 检测重复IP-MAC映射")
    print("- 异常ARP流量分析")
    
    # 模拟ARP异常检测
    print("\n异常ARP活动示例:")
    normal_arp = ARP(op=2, hwsrc="aa:bb:cc:dd:ee:ff", psrc="192.168.1.1")
    suspicious_arp = ARP(op=2, hwsrc="99:88:77:66:55:44", psrc="192.168.1.1")  # 同一IP，不同MAC
    
    print(f"正常ARP: {normal_arp.summary()}")
    print(f"可疑ARP: {suspicious_arp.summary()}")
    print("检测到: 同一IP地址对应不同MAC地址")
    
    print("\n2. DNS欺骗检测:")
    print("检测方法:")
    print("- 监控DNS响应时间")
    print("- 检查DNS响应来源")
    print("- 验证DNS记录一致性")
    
    print("\n3. 端口扫描检测:")
    print("检测方法:")
    print("- 监控连接尝试频率")
    print("- 检测SYN包模式")
    print("- 分析端口访问序列")
    
    print("\n4. DDoS攻击检测:")
    print("检测方法:")
    print("- 流量速率分析")
    print("- 连接数统计")
    print("- 源IP分布分析")
    
    print("\n5. 异常流量特征:")
    print("- 突发性大流量")
    print("- 异常协议使用")
    print("- 不寻常的通信模式")
    print("- 重复的数据包")

def main():
    """
    主函数
    """
    print("Scapy网络攻击模拟演示")
    print("=" * 50)
    print("\n⚠️  重要声明 ⚠️")
    print("本演示仅用于教育目的和授权的安全测试环境")
    print("请勿在未经授权的网络中使用这些技术")
    print("使用者需承担相应的法律责任")
    print("=" * 50)
    
    try:
        # 攻击原理演示
        demo_arp_spoofing_theory()
        demo_arp_scan_and_discovery()
        demo_dns_spoofing_theory()
        demo_tcp_hijacking_theory()
        demo_syn_flood_theory()
        demo_icmp_redirect_theory()
        demo_packet_injection_theory()
        demo_mitm_attack_theory()
        
        # 防护和检测
        demo_attack_detection()
        
    except KeyboardInterrupt:
        print("\n演示被用户中断")
    except Exception as e:
        print(f"\n演示过程中发生错误: {e}")
        import traceback
        traceback.print_exc()
    
    print("\n演示完成!")
    print("\n安全提醒:")
    print("1. 这些技术仅用于学习网络安全原理")
    print("2. 在生产环境中使用需要适当授权")
    print("3. 了解攻击原理有助于更好地防护")
    print("4. 建议在隔离的测试环境中实验")
    print("5. 遵守相关法律法规和道德准则")
    
    print("\n防护建议:")
    print("1. 使用加密通信协议 (HTTPS, SSH, VPN)")
    print("2. 部署网络监控和入侵检测系统")
    print("3. 定期更新系统和安全补丁")
    print("4. 实施网络分段和访问控制")
    print("5. 进行定期的安全评估和渗透测试")

if __name__ == "__main__":
    main()