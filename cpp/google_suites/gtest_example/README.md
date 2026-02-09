# Google Test 示例项目

## 依赖安装
- Ubuntu
  - sudo apt update
  - sudo apt install -y build-essential cmake git python3
- Windows
  - 安装 Visual Studio 2019/2022（含 C++ 桌面开发组件，v142 工具集）
  - 安装 CMake（添加到 PATH）
- macOS
  - brew install cmake git

本项目使用 CMake FetchContent 自动获取 googletest，无需手动安装。

## 构建
- Debug
  - Linux/macOS: ./build/build_debug.sh
  - Windows: PowerShell 执行 ./build/build_debug.ps1
- Release
  - Linux/macOS: ./build/build_release.sh
  - Windows: PowerShell 执行 ./build/build_release.ps1

## 运行测试
- Linux/macOS
  - ctest --test-dir build -C Debug
- Windows
  - ctest --test-dir build -C Debug

## 覆盖率
- 仅在 GCC 下支持，示例：
  - cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
  - cmake --build build -j
  - lcov --capture --directory build --output-file coverage.info
  - genhtml coverage.info --output-directory coverage_html

## 展示点
- 测试夹具
- 参数化测试
- 死亡测试
- 至少 10 个测试用例，覆盖率目标≥90%
