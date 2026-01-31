# Protobuf 示例

本目录包含 Protocol Buffers 的基础示例与生成代码。

## 目录结构

```
protobuf/
├── person.proto   # 协议定义
├── person.pb.h    # 生成的头文件
├── person.pb.cc   # 生成的实现
└── main.cpp       # 使用示例
```

## 使用方式

```bash
# 生成代码（需安装 protoc）
protoc --cpp_out=. person.proto

# 编译示例（需安装 protobuf C++ 库）
# g++ main.cpp person.pb.cc -lprotobuf -o demo
```
