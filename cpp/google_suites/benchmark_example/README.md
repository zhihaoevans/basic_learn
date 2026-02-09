# Google Benchmark 示例项目

## 依赖安装
- Ubuntu
  - sudo apt update
  - sudo apt install -y build-essential cmake git
- Windows
  - 安装 Visual Studio 2019/2022（含 C++ 桌面开发组件，v142 工具集）
  - 安装 CMake（添加到 PATH）
- macOS
  - brew install cmake git

本项目使用 CMake FetchContent 自动获取 google benchmark，无需手动安装。

## 构建
- Debug
  - Linux/macOS: ./build/build_debug.sh
  - Windows: PowerShell 执行 ./build/build_debug.ps1
- Release
  - Linux/macOS: ./build/build_release.sh
  - Windows: PowerShell 执行 ./build/build_release.ps1

## 运行与JSON报告
- 运行：
  - ./build/bench_suite --benchmark_out=report.json --benchmark_out_format=json
- 展示点：
  - 基本性能测试
  - 自定义计时器（ManualTime）
  - 复杂度分析（Complexity）
  - 对比测试（不同实现）
