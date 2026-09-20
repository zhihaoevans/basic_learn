# Phase 3：已有语言对齐实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Python 补基础 15 题 + 特色；Go/C/Shell 对照 TOPICS.md 补缺失主题；C++ 新建 basics 完整 15 题 + 特色；五个语言 README 对齐五段式；python/cpp workflow 收口；根 README 矩阵全部补齐。

**Architecture:** 六个任务：Python（最大缺口）→ Go（5 题）→ C（9 题 + pthread 链接）→ Shell（7 题）→ C++（16 题 + cpp/basics CMake + cpp.yml 步骤）→ 收尾全量验证。每任务更新自己语言的 README 与根 README 行，CI 除 python/cpp 外已被现有 glob/find 循环自动覆盖。

**Tech Stack:** Python 3.10+（match/类型标注）、Go 1.20+（泛型）、C17 + CMake + pthread、bash、C++17 + CMake。

## Global Constraints

- 主题与编号严格按 TOPICS.md 01-15 + 特色；不支持标 ➖。
- 每示例头注释三要素（主题说明/运行命令/预期输出关键行），中文注释，预期输出须与实际一致（先跑后写）。
- 每示例独立运行退出码 0；不引入第三方依赖。
- 各语言 README 按 TOPICS.md 五段式重写（现有专题/旧内容归入第 5 段进阶，不删除）。
- 每任务同步根 README：状态表与主题矩阵该语言行。
- 提交：`type(scope): 中文主题`；示例+README+矩阵+CI 一起提交。

---

### Task 1: Python 基础语法（15 题 + 特色）

**Files:**
- Create: `python/01_hello.py` ~ `python/15_generic.py` + `python/16_decorator_generator.py`（特色）
- Modify: `python/README.md`（五段式；ai/matplotlib/scapy/scrapy/chapters 归入进阶段）、根 `README.md`、`.github/workflows/python.yml`
- `python/chapters/` 保留不动（进阶段说明）

**知识点：** 01 print/f-string/注释；02 动态类型/类型标注/多重赋值/常量约定/类型转换；03 算术含 ** 与 //、is vs ==、海象运算符、字符串格式化表达式；04 切片/f-string/format/join/split/strip/replace/encode；05 if-elif/match-case/for-else/while/break-continue；06 def/默认/关键字参数/*args/**kwargs/lambda/闭包/函数标注；07 list/tuple/set/推导式/sort vs sorted/解包；08 dict 增删改查/get/defaultdict(dict 归 stdlib?)/遍历/推导/合并 | 运算符；09 class/继承/super/property/魔术方法 __repr__/dataclass；10 try/except 多类型/else/finally/raise from/自定义异常；11 with open 读写下/逐行/json.dump load/pathlib；12 import/from-import 双文件（12_module.py + mymath.py 同级，__name__ == "__main__" 演示）、包结构注释说明；13 stdlib 速览 collections.Counter/itertools/datetime/re/os/sys；14 threading+Lock/concurrent.futures/asyncio 入门各一小段；15 TypeVar/泛型函数/泛型类/Protocol 入门；16 装饰器（带参）/生成器与 yield/生成器表达式。

**python.yml 新增步骤**（在 unittest 步骤后）：
```yaml
      - name: Run python basics examples
        run: |
          for f in python/[0-9]*.py; do
            echo "== $f =="
            python3 "$f"
          done
```

**验证：** `for f in python/[0-9]*.py; do python3 "$f" >/dev/null || echo "FAIL: $f"; done` 零 FAIL；yaml 解析通过。

### Task 2: Go 补缺 5 题

**Files:**
- Create: `golang/03_operator.go`、`golang/04_string.go`、`golang/11_file_io.go`、`golang/13_stdlib.go`、`golang/15_generic.go`
- Modify: `golang/README.md`（五段式）、根 `README.md`（Go 行矩阵 03/04/11/13/15 → ✅）

**知识点：** 03 算术/比较/逻辑/位运算含 &^/++ 是语句不是表达式说明/运算符优先级；04 string 不可变/len 字节/rune 遍历/切片/strings 包常用/strconv 与 fmt 格式化；11 os.ReadFile/WriteFile/os.Create+bufio.Scanner 逐行/临时文件 os.CreateTemp 清理/defer Close；13 strings/slices/maps(Cloned/Keys 入门)/strconv/time.Format/常用速览；15 [T any] 泛型函数/[K comparable] 映射键约束/泛型类型 Stack[T]/constraints 说明。

**验证：** `for f in golang/*.go; do go vet "$f" && go run "$f" >/dev/null || echo "FAIL: $f"; done` 零 FAIL（26 文件全过——CI 同款门禁）。

### Task 3: C 补缺 9 题

**Files:**
- Create 目录+文件：`c/variable/variable_basics.c`、`c/operator/operator_basics.c`、`c/control/control_flow.c`、`c/function/function_basics.c`、`c/oop/struct_polymorphism.c`（struct+函数指针模拟封装与多态，范式适配）、`c/error/error_handling.c`、`c/file_io/file_io.c`、`c/module/module_demo.c` + `c/module/util.h` + `c/module/util.c`（extern/static/头文件）、`c/concurrency/pthread_basics.c`
- Modify: `c/CMakeLists.txt`（concurrency 链 pthread）、`c/README.md`（五段式；修正"推荐 Makefile"过时表述为 CMake）、根 `README.md`（C 行矩阵 02/03/05/06/09/10/11/12/14 → ✅）

**知识点：** 02 基本类型/sizeof/const vs #define/隐式与显式转换/溢出演示（注释）；03 算术/位运算/自增/条件表达式/优先级；05 if/switch（含 fallthrough 说明）/三种循环/break-continue/goto 一例；06 原型/定义/static 函数/递归/函数指针入门；09 struct 封装+函数指针字段实现"方法"+不同形状同一接口（多态模拟）；10 errno/perror/strerror/返回码约定/EXIT_FAILURE；11 fopen 模式/fwrite fread/fprintf/fgets/fclose+错误检查；12 util.h 声明+util.c 定义+extern 变量/static 隐藏+include guard；14 pthread_create/join/mutex 互斥计数。

**CMakeLists 修改**（顶层 m 链接行后加）：
```cmake
  if(src MATCHES "/concurrency/")
    target_link_libraries(${exe} pthread)
  endif()
```

**验证：** `cmake -S c -B c/build && cmake --build c/build -j8` 零错误；`for b in c/build/bin/*; do "$b" >/dev/null 2>&1 || echo "NONZERO: $b"; done` 零失败（65+ 产物）；module 双文件由 CMake 分别建 target。

### Task 4: Shell 补缺 7 题

**Files:**
- Create: `scripts/shell/hello/hello.sh`、`scripts/shell/function/function_basics.sh`、`scripts/shell/error/error_handling.sh`、`scripts/shell/file_io/file_io.sh`、`scripts/shell/module/module_source.sh` + `scripts/shell/module/sourced.sh`（被 source 的模块）、`scripts/shell/stdlib/builtin_tour.sh`、`scripts/shell/concurrency/background_wait.sh`
- Modify: `scripts/shell/README.md`（五段式）、根 `README.md`（Shell 行 01/06/10/11/12/13/14 → ✅）

**知识点：** 01 shebang/echo vs printf/注释/运行方式；06 函数定义/位置参数/$?/local/返回值 return vs echo 输出；10 set -e 说明/退出码约定/2>/dev/null/|| 兜底/trap ERR 一例；11 重定向 >/>>//dev/null、cat 写文件/read 逐行/here-doc/追加；12 source vs 执行区别/被 source 文件提供函数/子 shell 括号隔离/export 可见性；13 test 与 [[ ]]/参数扩展 ${var:-default} 等/cd 与 pushd/getopts 一例；14 & 后台/wait 收割/jobs/管道并行一例。

**验证：** `find scripts/shell -name '*.sh' | sort | while read -r f; do bash "$f" >/dev/null 2>&1 || echo "FAIL: $f"; done` 零 FAIL（CI 同款门禁）。

### Task 5: C++ basics 完整 16 题

**Files:**
- Create: `cpp/basics/CMakeLists.txt`（glob *.cpp→executable，C++17，链 pthread）+ `cpp/basics/01_hello.cpp` ~ `cpp/basics/15_generic.cpp` + `cpp/basics/16_raii.cpp`（特色）
- Modify: `cpp/README.md`（五段式；cpptest/google_suites 等归进阶段）、`.github/workflows/cpp.yml`（新增 basics 构建运行步骤）、根 `README.md`（C++ 行 01-15+特色 → ✅）

**知识点：** 01 iostream/注释/endl；02 auto/基本类型/const/constexpr/统一初始化/类型转换 static_cast；03 算术/比较/位/自增/三元/优先级；04 string 拼接/substr/find/replace/to_string/stoi/原始字符串；05 if/switch 初始化器/range-for/while/break-continue；06 重载/默认参/内联/lambda 捕获列表/函数对象；07 array/vector/list/set/迭代器/基于 range 遍历；08 map/unordered_map/[] vs at/insert/遍历/统计单词经典例；09 class 封装/构造析构/继承 virtual/override/纯虚抽象类/多态；10 异常层次/throw/try-catch 引用捕获/自定义异常类/noexcept 说明；11 ofstream 写/ifstream 读/逐行/stringstream；12 namespace/头文件声明定义分离（单文件内演示+多文件注释说明）/using 声明与指令；13 algorithm sort/find_if/count/accumulate/chrono/string_view 速览；14 thread/mutex/lock_guard/async future 入门；15 函数模板/类模板/非类型参数/auto 返回；16 RAII 构造获取析构释放/unique_ptr/lock_guard 原理/异常安全。

**cpp.yml 新增步骤**（置于 cpptest 步骤之前）：
```yaml
      - name: Build and run basics examples
        run: |
          cmake -S cpp/basics -B cpp/basics/build
          cmake --build cpp/basics/build -j"$(nproc)"
          for b in cpp/basics/build/*; do
            [ -f "$b" ] && [ -x "$b" ] || continue
            echo "== $b =="
            "$b"
          done
```

**验证：** `cmake -S cpp/basics -B cpp/basics/build && cmake --build cpp/basics/build -j8` 零错误零 warning；全部产物运行退出码 0；yaml 解析通过。

### Task 6: 收尾——全量验证与推送准备

- 复核根 README：状态表 10 行全 ✅ 完整；矩阵逐行 16 列；链接检查脚本零 BROKEN
- 五语言新示例本地全量门禁重放（python/go/c/shell/cpp 各自循环）
- 全部 workflow yaml 解析
- 台账更新；整体审查（控制器在任务全完后派发）

### 收尾（控制器执行）

整体分支审查 → 修复 → 合回 main（--no-ff）→ 推送 → `gh run list` 确认全绿。
