# Scapy库完整功能演示程序

这是一个全面展示Python Scapy库功能的演示程序集合，包含6个主要模块，涵盖了网络包处理、协议分析、网络扫描、安全测试等各个方面。

## 📋 目录

- [功能模块](#功能模块)
- [安装要求](#安装要求)
- [快速开始](#快速开始)
- [模块详解](#模块详解)
- [使用说明](#使用说明)
- [注意事项](#注意事项)
- [常见问题](#常见问题)
- [参考资源](#参考资源)

## 🚀 功能模块

### 1. 基础网络包构造和操作 (`01_basic_packet_demo.py`)
- 网络包的创建、修改和发送
- 协议分层和封装
- 包字段操作和分析
- 包的序列化和反序列化

### 2. 网络扫描功能 (`02_network_scanning_demo.py`)
- Ping扫描和主机发现
- TCP/UDP端口扫描
- 隐蔽扫描技术
- 操作系统指纹识别
- 服务版本检测
- 路由跟踪

### 3. 网络嗅探和包捕获 (`03_packet_sniffing_demo.py`)
- 实时网络流量监听
- 包过滤和筛选
- 流量统计分析
- 包捕获到文件
- 离线包分析
- 自定义协议解析

### 4. 协议分析和解析 (`04_protocol_analysis_demo.py`)
- 以太网帧分析
- IP协议详解
- TCP/UDP传输层分析
- ICMP协议处理
- DNS查询分析
- HTTP协议解析
- ARP协议操作

### 5. 网络攻击模拟 (`05_attack_simulation_demo.py`) ⚠️
- ARP欺骗攻击原理
- DNS欺骗技术
- TCP会话劫持
- SYN洪水攻击
- 中间人攻击模拟
- 攻击检测技术

**注意**: 此模块仅用于学习和授权测试，请勿用于非法用途！

### 6. 无线网络分析 (`06_wireless_analysis_demo.py`)
- WiFi帧结构分析
- Beacon帧解析
- Probe Request分析
- 去认证攻击原理
- WPS协议分析
- 无线安全评估

### 7. 主程序 (`main.py`)
- 统一的菜单界面
- 模块化加载
- 系统环境检查
- 安全运行控制

## 💻 安装要求

### 系统要求
- **操作系统**: Windows 10+, macOS 10.14+, Linux (Ubuntu 18.04+)
- **Python版本**: Python 3.6 或更高版本
- **权限**: 管理员/root权限 (用于原始套接字操作)

### Python依赖
```bash
# 安装所有依赖
pip install -r requirements.txt

# 或者手动安装核心依赖
pip install scapy netifaces cryptography matplotlib numpy
```

### 系统依赖

#### Windows
```bash
# 安装 Npcap (推荐) 或 WinPcap
# 下载地址: https://npcap.com/
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install python3-pip libpcap-dev
```

#### macOS
```bash
# 通常无需额外安装，系统已包含必要库
# 如需要，可通过 Homebrew 安装
brew install libpcap
```

## 🏃 快速开始

### 1. 克隆或下载项目
```bash
# 如果是从Git仓库
git clone <repository-url>
cd scapy-demo

# 或者直接下载文件到目录
```

### 2. 安装依赖
```bash
pip install -r requirements.txt
```

### 3. 运行主程序
```bash
# 推荐以管理员权限运行
# Windows (以管理员身份运行命令提示符)
python main.py

# Linux/macOS
sudo python3 main.py
```

### 4. 选择演示模块
程序会显示菜单，选择相应数字即可运行对应的演示模块。

## 📖 模块详解

### 基础包操作模块
```python
# 运行基础包演示
python 01_basic_packet_demo.py
```
学习内容:
- 如何创建各种协议的数据包
- 包的分层结构理解
- 字段修改和自定义
- 包的发送和接收

### 网络扫描模块
```python
# 运行网络扫描演示
python 02_network_scanning_demo.py
```
学习内容:
- 主机存活检测技术
- 端口扫描的各种方法
- 服务识别和版本检测
- 操作系统指纹识别

### 包嗅探模块
```python
# 运行包嗅探演示
python 03_packet_sniffing_demo.py
```
学习内容:
- 网络流量实时监控
- 包过滤器的使用
- 流量统计和分析
- 包的存储和回放

### 协议分析模块
```python
# 运行协议分析演示
python 04_protocol_analysis_demo.py
```
学习内容:
- 各层协议的详细结构
- 协议字段的含义和作用
- 协议间的交互关系
- 异常协议的识别

### 攻击模拟模块 ⚠️
```python
# 运行攻击模拟演示 (需要特别注意)
python 05_attack_simulation_demo.py
```
学习内容:
- 网络攻击的技术原理
- 攻击检测和防护方法
- 安全漏洞的识别
- 渗透测试技术

### 无线分析模块
```python
# 运行无线分析演示
python 06_wireless_analysis_demo.py
```
学习内容:
- 802.11协议族理解
- WiFi安全机制分析
- 无线攻击技术原理
- 无线网络安全评估

## 📝 使用说明

### 权限要求
大多数功能需要管理员权限，因为涉及:
- 原始套接字操作
- 网络接口直接访问
- 包注入功能
- 系统级网络操作

### 网络环境
- **测试环境**: 建议在隔离的测试网络中运行
- **生产环境**: 谨慎使用扫描功能，避免影响正常业务
- **无线测试**: 需要支持监控模式的无线网卡

### 安全考虑
- 仅在授权的网络环境中使用
- 遵守当地法律法规
- 不要用于恶意攻击
- 注意保护个人隐私和数据安全

## ⚠️ 注意事项

### 法律声明
- 本程序仅用于学习和研究目的
- 用户需对使用本程序的行为负责
- 禁止用于任何非法活动
- 请遵守当地网络安全法律法规

### 技术限制
- 某些功能在虚拟机中可能受限
- 无线功能需要特定硬件支持
- 防火墙可能阻止某些操作
- 不同操作系统的行为可能有差异

### 性能影响
- 网络扫描可能产生大量流量
- 包嗅探会消耗系统资源
- 某些演示可能影响网络性能
- 建议在测试环境中运行

## 🔧 常见问题

### Q: 提示权限不足怎么办？
A: 需要以管理员/root权限运行程序，因为Scapy需要访问原始套接字。

### Q: Windows上无法捕获包？
A: 需要安装Npcap或WinPcap驱动程序。

### Q: 无线功能不工作？
A: 需要支持监控模式的无线网卡和相应驱动。

### Q: 扫描功能没有结果？
A: 检查防火墙设置，确保网络连通性。

### Q: 程序运行很慢？
A: 某些演示涉及网络操作，需要等待网络响应。

### Q: 如何在虚拟机中使用？
A: 确保虚拟机网络设置为桥接模式，并安装相应的网络驱动。

## 📚 学习建议

### 学习路径
1. **基础知识**: 先学习网络协议基础理论
2. **动手实践**: 按模块顺序逐一学习
3. **深入理解**: 阅读源代码，理解实现原理
4. **扩展应用**: 尝试修改代码，实现自定义功能

### 推荐资源
- **书籍**: 《TCP/IP详解》、《网络安全技术与实践》
- **文档**: Scapy官方文档、RFC协议标准
- **工具**: Wireshark、Nmap、tcpdump
- **实验**: 搭建虚拟实验环境

## 🔗 参考资源

### 官方资源
- [Scapy官网](https://scapy.net/)
- [Scapy文档](https://scapy.readthedocs.io/)
- [GitHub仓库](https://github.com/secdev/scapy)

### 学习资源
- [RFC文档](https://www.rfc-editor.org/)
- [Wireshark用户指南](https://www.wireshark.org/docs/)
- [网络协议学习](https://www.iana.org/protocols)

### 工具资源
- [Nmap网络扫描](https://nmap.org/)
- [Aircrack-ng无线工具](https://www.aircrack-ng.org/)
- [tcpdump包分析](https://www.tcpdump.org/)

## 📄 许可证

本项目仅用于教育和学习目的。使用者需要:
- 遵守当地法律法规
- 仅在授权环境中使用
- 承担使用责任
- 不用于恶意目的

## 🤝 贡献

欢迎提交问题报告和改进建议！

---

**免责声明**: 本程序仅用于学习和研究目的，使用者需对其行为承担全部责任。作者不对任何误用或滥用承担责任。