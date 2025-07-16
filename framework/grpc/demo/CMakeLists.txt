cmake_minimum_required(VERSION 3.15)
project(grpc_example)

set(CMAKE_CXX_STANDARD 17)

# 添加自定义查找路径
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

# 查找依赖 - 使用新的查找方式
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# 设置生成的文件
set(PROTO_SRCS math.pb.cc math.grpc.pb.cc)
set(PROTO_HDRS math.pb.h math.grpc.pb.h)

# 添加服务端可执行文件
add_executable(server
    server.cpp
    ${PROTO_SRCS}
)

# 添加客户端可执行文件
add_executable(client
    client.cpp
    ${PROTO_SRCS}
)

# 链接库 - 使用目标名称
target_link_libraries(server PRIVATE
    gRPC::grpc++
    gRPC::grpc
    gRPC::gpr
    protobuf::libprotobuf
)

target_link_libraries(client PRIVATE
    gRPC::grpc++
    gRPC::grpc
    gRPC::gpr
    protobuf::libprotobuf
)
