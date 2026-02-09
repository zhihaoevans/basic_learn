# Google Log（glog）示例项目

## 依赖安装
- Ubuntu
  - sudo apt update
  - sudo apt install -y build-essential cmake git
- Windows
  - 安装 Visual Studio 2019/2022（含 C++ 桌面开发组件，v142 工具集）
  - 安装 CMake（添加到 PATH）
- macOS
  - brew install cmake git

本项目使用 CMake FetchContent 自动获取 glog，无需手动安装。

## 构建
- Debug
  - Linux/macOS: ./build/build_debug.sh
  - Windows: PowerShell 执行 ./build/build_debug.ps1
- Release
  - Linux/macOS: ./build/build_release.sh
  - Windows: PowerShell 执行 ./build/build_release.ps1

## 运行与配置
- 运行：
  - ./build/logging_example [log_dir]
- 展示点：
  - 日志分级（INFO/WARNING/ERROR）
  - 条件日志（LOG_IF）
  - 日志文件配置（FLAGS_log_dir）
  - 日志滚动策略（FLAGS_max_log_size，按大小滚动）
