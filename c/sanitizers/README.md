# Sanitizers 示例集

本目录包含 GCC/Clang Sanitizers 的使用示例。Sanitizers 是用于检测 C/C++ 代码中各种错误的强大工具。

## 包含的示例

1.  **asan_oob.c**: AddressSanitizer (ASan) 示例，演示**堆缓冲区溢出 (Heap Buffer Overflow)**。
2.  **asan_uaf.c**: AddressSanitizer (ASan) 示例，演示**释放后使用 (Use-After-Free)**。
3.  **lsan_leak.c**: LeakSanitizer (LSan) 示例，演示**内存泄漏 (Memory Leak)**。
4.  **tsan_race.c**: ThreadSanitizer (TSan) 示例，演示**数据竞争 (Data Race)**。
5.  **ubsan_overflow.c**: UndefinedBehaviorSanitizer (UBSan) 示例，演示**有符号整数溢出 (Signed Integer Overflow)**。

## 如何编译和运行

本目录提供了一个 `Makefile` 来简化编译过程。

### 前提条件
你需要安装 GCC 或 Clang。

### 编译所有示例

```bash
make
```

### 运行示例

运行生成的可执行文件，观察 Sanitizer 的报错输出。

**注意**: 这些程序设计为会崩溃或报错，这是预期行为。

#### 1. 运行 ASan 示例 (越界访问)
```bash
./asan_oob
```
*预期输出*: `ERROR: AddressSanitizer: heap-buffer-overflow...`

#### 2. 运行 ASan 示例 (释放后使用)
```bash
./asan_uaf
```
*预期输出*: `ERROR: AddressSanitizer: heap-use-after-free...`

#### 3. 运行 LSan 示例 (内存泄漏)
```bash
./lsan_leak
```
*预期输出*: `ERROR: LeakSanitizer: detected memory leaks...`

#### 4. 运行 TSan 示例 (数据竞争)
```bash
./tsan_race
```
*预期输出*: `WARNING: ThreadSanitizer: data race...`

#### 5. 运行 UBSan 示例 (整数溢出)
```bash
./ubsan_overflow
```
*预期输出*: `runtime error: signed integer overflow...`

## 清理

```bash
make clean
```
