/*
 * stdint.h 演示程序
 * 
 * stdint.h 定义了固定宽度的整数类型，这些类型在不同平台上具有相同的大小
 * 主要包含：
 * - 精确宽度整数类型：int8_t, int16_t, int32_t, int64_t 及其无符号版本
 * - 最小宽度整数类型：int_least8_t, int_least16_t 等
 * - 最快整数类型：int_fast8_t, int_fast16_t 等
 * - 指针大小整数类型：intptr_t, uintptr_t
 * - 最大整数类型：intmax_t, uintmax_t
 * - 各种限制宏：INT8_MAX, UINT16_MAX 等
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>  // 用于printf格式化宏

// 简单的哈希函数
static size_t hash_func(uint32_t key, size_t table_size) {
    return key % table_size;
}

// 演示精确宽度整数类型
void demo_exact_width_types(void) {
    printf("=== 精确宽度整数类型演示 ===\n");
    
    // 8位整数
    int8_t i8 = -128;
    uint8_t u8 = 255;
    printf("int8_t:  大小=%zu字节, 值=%d, 范围=[%d, %d]\n", 
           sizeof(int8_t), i8, INT8_MIN, INT8_MAX);
    printf("uint8_t: 大小=%zu字节, 值=%u, 范围=[0, %u]\n", 
           sizeof(uint8_t), u8, UINT8_MAX);
    
    // 16位整数
    int16_t i16 = -32768;
    uint16_t u16 = 65535;
    printf("int16_t:  大小=%zu字节, 值=%d, 范围=[%d, %d]\n", 
           sizeof(int16_t), i16, INT16_MIN, INT16_MAX);
    printf("uint16_t: 大小=%zu字节, 值=%u, 范围=[0, %u]\n", 
           sizeof(uint16_t), u16, UINT16_MAX);
    
    // 32位整数
    int32_t i32 = -2147483648;
    uint32_t u32 = 4294967295U;
    printf("int32_t:  大小=%zu字节, 值=%" PRId32 ", 范围=[%" PRId32 ", %" PRId32 "]\n", 
           sizeof(int32_t), i32, INT32_MIN, INT32_MAX);
    printf("uint32_t: 大小=%zu字节, 值=%" PRIu32 ", 范围=[0, %" PRIu32 "]\n", 
           sizeof(uint32_t), u32, UINT32_MAX);
    
    // 64位整数
    int64_t i64 = -9223372036854775807LL - 1;
    uint64_t u64 = 18446744073709551615ULL;
    printf("int64_t:  大小=%zu字节, 值=%" PRId64 ", 范围=[%" PRId64 ", %" PRId64 "]\n", 
           sizeof(int64_t), i64, INT64_MIN, INT64_MAX);
    printf("uint64_t: 大小=%zu字节, 值=%" PRIu64 ", 范围=[0, %" PRIu64 "]\n", 
           sizeof(uint64_t), u64, UINT64_MAX);
    
    printf("\n");
}

// 演示最小宽度整数类型
void demo_least_width_types(void) {
    printf("=== 最小宽度整数类型演示 ===\n");
    printf("这些类型保证至少有指定的位数，但可能更大以提高效率\n");
    
    printf("int_least8_t:  大小=%zu字节\n", sizeof(int_least8_t));
    printf("int_least16_t: 大小=%zu字节\n", sizeof(int_least16_t));
    printf("int_least32_t: 大小=%zu字节\n", sizeof(int_least32_t));
    printf("int_least64_t: 大小=%zu字节\n", sizeof(int_least64_t));
    
    // 实际使用示例
    int_least16_t pixel_value = 32767;  // 用于图像处理
    int_least32_t file_size = 1048576;  // 用于文件大小
    
    printf("像素值: %" PRIdLEAST16 "\n", pixel_value);
    printf("文件大小: %" PRIdLEAST32 " 字节\n", file_size);
    
    printf("\n");
}

// 演示最快整数类型
void demo_fast_types(void) {
    printf("=== 最快整数类型演示 ===\n");
    printf("这些类型在目标平台上操作最快，至少有指定的位数\n");
    
    printf("int_fast8_t:  大小=%zu字节\n", sizeof(int_fast8_t));
    printf("int_fast16_t: 大小=%zu字节\n", sizeof(int_fast16_t));
    printf("int_fast32_t: 大小=%zu字节\n", sizeof(int_fast32_t));
    printf("int_fast64_t: 大小=%zu字节\n", sizeof(int_fast64_t));
    
    // 性能关键的计算示例
    int_fast32_t counter = 0;
    int_fast32_t limit = 1000000;
    
    printf("开始快速计数...\n");
    for (int_fast32_t i = 0; i < limit; i++) {
        counter += i;
    }
    printf("计数结果: %" PRIdFAST32 "\n", counter);
    
    printf("\n");
}

// 演示指针大小整数类型
void demo_pointer_types(void) {
    printf("=== 指针大小整数类型演示 ===\n");
    
    printf("intptr_t:  大小=%zu字节\n", sizeof(intptr_t));
    printf("uintptr_t: 大小=%zu字节\n", sizeof(uintptr_t));
    printf("指针大小:  %zu字节\n", sizeof(void*));
    
    // 指针与整数的转换
    int value = 42;
    int *ptr = &value;
    
    // 将指针转换为整数
    uintptr_t ptr_as_int = (uintptr_t)ptr;
    printf("指针地址: %p\n", (void*)ptr);
    printf("转换为整数: %" PRIuPTR "\n", ptr_as_int);
    
    // 将整数转换回指针
    int *restored_ptr = (int*)ptr_as_int;
    printf("恢复的指针: %p\n", (void*)restored_ptr);
    printf("指针值相等: %s\n", (ptr == restored_ptr) ? "是" : "否");
    printf("通过恢复指针访问值: %d\n", *restored_ptr);
    
    // 指针算术示例
    int arr[] = {10, 20, 30, 40, 50};
    int *start = arr;
    int *end = arr + 4;
    
    intptr_t diff = (intptr_t)end - (intptr_t)start;
    printf("指针差值(字节): %" PRIdPTR "\n", diff);
    printf("元素差值: %td\n", end - start);
    
    printf("\n");
}

// 演示最大整数类型
void demo_max_types(void) {
    printf("=== 最大整数类型演示 ===\n");
    
    printf("intmax_t:  大小=%zu字节\n", sizeof(intmax_t));
    printf("uintmax_t: 大小=%zu字节\n", sizeof(uintmax_t));
    
    intmax_t max_signed = INTMAX_MAX;
    uintmax_t max_unsigned = UINTMAX_MAX;
    
    printf("最大有符号整数: %" PRIdMAX "\n", max_signed);
    printf("最大无符号整数: %" PRIuMAX "\n", max_unsigned);
    
    // 大数计算示例
    intmax_t factorial = 1;
    int n = 20;
    
    printf("计算 %d! = ", n);
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    printf("%" PRIdMAX "\n", factorial);
    
    printf("\n");
}

// 演示常量宏的使用
void demo_constant_macros(void) {
    printf("=== 常量宏演示 ===\n");
    
    // 整数常量宏
    printf("使用常量宏定义值:\n");
    
    int8_t small = INT8_C(-100);
    uint8_t usmall = UINT8_C(200);
    int32_t medium = INT32_C(1000000);
    uint32_t umedium = UINT32_C(2000000);
    int64_t large = INT64_C(9000000000000000000);
    uint64_t ularge = UINT64_C(18000000000000000000);
    
    printf("INT8_C(-100) = %d\n", small);
    printf("UINT8_C(200) = %u\n", usmall);
    printf("INT32_C(1000000) = %" PRId32 "\n", medium);
    printf("UINT32_C(2000000) = %" PRIu32 "\n", umedium);
    printf("INT64_C(9000000000000000000) = %" PRId64 "\n", large);
    printf("UINT64_C(18000000000000000000) = %" PRIu64 "\n", ularge);
    
    // 最大值常量宏
    intmax_t max_val = INTMAX_C(9223372036854775807);
    uintmax_t umax_val = UINTMAX_C(18446744073709551615);
    
    printf("INTMAX_C(9223372036854775807) = %" PRIdMAX "\n", max_val);
    printf("UINTMAX_C(18446744073709551615) = %" PRIuMAX "\n", umax_val);
    
    printf("\n");
}

// 演示位操作和掩码
void demo_bit_operations(void) {
    printf("=== 位操作演示 ===\n");
    
    // 使用固定宽度类型进行位操作
    uint32_t flags = 0;
    
    // 定义一些标志位
    const uint32_t FLAG_READ    = UINT32_C(0x00000001);  // 位0
    const uint32_t FLAG_WRITE   = UINT32_C(0x00000002);  // 位1
    const uint32_t FLAG_EXECUTE = UINT32_C(0x00000004);  // 位2
    const uint32_t FLAG_HIDDEN  = UINT32_C(0x00000008);  // 位3
    
    printf("初始标志: 0x%08" PRIX32 "\n", flags);
    
    // 设置标志
    flags |= FLAG_READ | FLAG_WRITE;
    printf("设置读写权限: 0x%08" PRIX32 "\n", flags);
    
    // 检查标志
    printf("是否可读: %s\n", (flags & FLAG_READ) ? "是" : "否");
    printf("是否可写: %s\n", (flags & FLAG_WRITE) ? "是" : "否");
    printf("是否可执行: %s\n", (flags & FLAG_EXECUTE) ? "是" : "否");
    printf("是否隐藏: %s\n", (flags & FLAG_HIDDEN) ? "是" : "否");
    
    // 清除标志
    flags &= ~FLAG_WRITE;
    printf("清除写权限: 0x%08" PRIX32 "\n", flags);
    
    // 切换标志
    flags ^= FLAG_EXECUTE;
    printf("切换执行权限: 0x%08" PRIX32 "\n", flags);
    
    printf("\n");
}

// 演示跨平台兼容性
void demo_portability(void) {
    printf("=== 跨平台兼容性演示 ===\n");
    
    // 显示当前平台的类型大小
    printf("当前平台类型大小:\n");
    printf("  char: %zu字节\n", sizeof(char));
    printf("  short: %zu字节\n", sizeof(short));
    printf("  int: %zu字节\n", sizeof(int));
    printf("  long: %zu字节\n", sizeof(long));
    printf("  long long: %zu字节\n", sizeof(long long));
    printf("  指针: %zu字节\n", sizeof(void*));
    
    printf("\n固定宽度类型大小:\n");
    printf("  int8_t: %zu字节\n", sizeof(int8_t));
    printf("  int16_t: %zu字节\n", sizeof(int16_t));
    printf("  int32_t: %zu字节\n", sizeof(int32_t));
    printf("  int64_t: %zu字节\n", sizeof(int64_t));
    
    // 网络字节序转换示例（需要额外的头文件，这里只是概念演示）
    uint32_t host_value = UINT32_C(0x12345678);
    printf("\n网络字节序示例:\n");
    printf("主机字节序: 0x%08" PRIX32 "\n", host_value);
    
    // 手动字节序转换（简化版）
    uint32_t network_value = ((host_value & 0xFF000000) >> 24) |
                            ((host_value & 0x00FF0000) >> 8)  |
                            ((host_value & 0x0000FF00) << 8)  |
                            ((host_value & 0x000000FF) << 24);
    printf("网络字节序: 0x%08" PRIX32 "\n", network_value);
    
    printf("\n");
}

// 实际应用示例：简单的哈希表
void demo_practical_example(void) {
    printf("=== 实际应用示例：简单哈希表 ===\n");
    
    // 使用固定宽度类型定义哈希表
    const size_t TABLE_SIZE = 16;
    typedef struct {
        uint32_t key;
        int32_t value;
        uint8_t used;
    } hash_entry_t;
    
    hash_entry_t table[TABLE_SIZE] = {0};
    
    // 插入一些数据
    uint32_t keys[] = {UINT32_C(123), UINT32_C(456), UINT32_C(789)};
    int32_t values[] = {INT32_C(100), INT32_C(200), INT32_C(300)};
    
    for (size_t i = 0; i < 3; i++) {
        size_t index = hash_func(keys[i], TABLE_SIZE);
        
        // 简单的线性探测
        while (table[index].used) {
            index = (index + 1) % TABLE_SIZE;
        }
        
        table[index].key = keys[i];
        table[index].value = values[i];
        table[index].used = 1;
        
        printf("插入: key=%" PRIu32 ", value=%" PRId32 ", index=%zu\n", 
               keys[i], values[i], index);
    }
    
    // 查找数据
    uint32_t search_key = UINT32_C(456);
    size_t index = hash_func(search_key, TABLE_SIZE);
    
    while (table[index].used && table[index].key != search_key) {
        index = (index + 1) % TABLE_SIZE;
    }
    
    if (table[index].used && table[index].key == search_key) {
        printf("找到: key=%" PRIu32 ", value=%" PRId32 "\n", 
               search_key, table[index].value);
    } else {
        printf("未找到 key=%" PRIu32 "\n", search_key);
    }
    
    printf("\n");
}

int main(void) {
    printf("C标准库 stdint.h 演示程序\n");
    printf("=========================\n\n");
    
    demo_exact_width_types();
    demo_least_width_types();
    demo_fast_types();
    demo_pointer_types();
    demo_max_types();
    demo_constant_macros();
    demo_bit_operations();
    demo_portability();
    demo_practical_example();
    
    printf("stdint.h 演示完成！\n");
    printf("\n重要提示:\n");
    printf("1. 使用固定宽度类型确保跨平台一致性\n");
    printf("2. 选择合适的类型：exact(精确)、least(最小)、fast(最快)\n");
    printf("3. 使用 inttypes.h 中的格式化宏进行printf\n");
    printf("4. intptr_t/uintptr_t用于指针与整数转换\n");
    printf("5. 常量宏确保字面量有正确的类型\n");
    
    return 0;
}