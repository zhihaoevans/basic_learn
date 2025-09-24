/*
 * signal.h 演示程序
 * 
 * signal.h 定义了信号处理机制，用于处理程序执行过程中的异步事件
 * 主要包含：
 * - signal(): 设置信号处理函数
 * - raise(): 向当前进程发送信号
 * - 信号常量：SIGINT, SIGTERM, SIGABRT, SIGFPE, SIGILL, SIGSEGV
 * - 特殊处理器：SIG_DFL (默认), SIG_IGN (忽略)
 * - sig_atomic_t: 原子操作类型
 * 
 * 注意：信号处理是平台相关的，某些功能在不同系统上可能有差异
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep() - 在某些系统上可能需要
#include <string.h>

// 全局变量，用于信号处理器中的安全操作
volatile sig_atomic_t signal_received = 0;
volatile sig_atomic_t interrupt_count = 0;

// 简单的信号处理器
void simple_handler(int sig) {
    signal_received = sig;
    printf("\n收到信号 %d\n", sig);
}

// SIGINT (Ctrl+C) 处理器
void sigint_handler(int sig) {
    interrupt_count++;
    printf("\n收到中断信号 (Ctrl+C) - 第 %d 次\n", (int)interrupt_count);
    printf("再按一次 Ctrl+C 退出程序\n");
    
    if (interrupt_count >= 2) {
        printf("程序即将退出...\n");
        exit(0);
    }
    
    // 重新安装信号处理器（在某些系统上需要）
    signal(SIGINT, sigint_handler);
}

// 浮点异常处理器
void sigfpe_handler(int sig) {
    printf("\n捕获到浮点异常 (SIGFPE)\n");
    printf("这通常由除零或其他数学错误引起\n");
    
    // 注意：从SIGFPE处理器返回通常是不安全的
    // 在实际应用中，应该进行清理并退出
    signal_received = sig;
}

// 非法指令处理器
void sigill_handler(int sig) {
    printf("\n捕获到非法指令 (SIGILL)\n");
    printf("程序尝试执行非法指令\n");
    signal_received = sig;
}

// 段错误处理器
void sigsegv_handler(int sig) {
    printf("\n捕获到段错误 (SIGSEGV)\n");
    printf("程序访问了无效内存地址\n");
    printf("注意：从段错误处理器返回通常是不安全的\n");
    signal_received = sig;
    
    // 在实际应用中，应该进行清理并退出
    exit(1);
}

// 演示基本信号处理
void demo_basic_signal_handling(void) {
    printf("=== 基本信号处理演示 ===\n");
    
    // 显示信号常量的值
    printf("标准信号常量:\n");
    printf("  SIGINT (中断): %d\n", SIGINT);
    printf("  SIGTERM (终止): %d\n", SIGTERM);
    printf("  SIGABRT (异常终止): %d\n", SIGABRT);
    printf("  SIGFPE (浮点异常): %d\n", SIGFPE);
    printf("  SIGILL (非法指令): %d\n", SIGILL);
    printf("  SIGSEGV (段错误): %d\n", SIGSEGV);
    
    // 设置简单的信号处理器
    printf("\n设置SIGTERM信号处理器...\n");
    if (signal(SIGTERM, simple_handler) == SIG_ERR) {
        printf("设置SIGTERM处理器失败\n");
        return;
    }
    
    printf("向自己发送SIGTERM信号...\n");
    if (raise(SIGTERM) != 0) {
        printf("发送信号失败\n");
        return;
    }
    
    printf("信号处理完成，收到的信号: %d\n", (int)signal_received);
    
    // 恢复默认处理器
    signal(SIGTERM, SIG_DFL);
    printf("SIGTERM处理器已恢复为默认\n");
    
    printf("\n");
}

// 演示中断信号处理
void demo_interrupt_handling(void) {
    printf("=== 中断信号处理演示 ===\n");
    printf("设置SIGINT (Ctrl+C) 处理器\n");
    printf("请按 Ctrl+C 测试中断处理 (按两次退出)\n");
    printf("或等待5秒自动继续...\n");
    
    // 设置SIGINT处理器
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        printf("设置SIGINT处理器失败\n");
        return;
    }
    
    // 等待一段时间，让用户测试
    for (int i = 0; i < 5; i++) {
        printf("等待中... %d/5\n", i + 1);
        sleep(1);
        
        if (interrupt_count > 0) {
            break;
        }
    }
    
    if (interrupt_count == 0) {
        printf("没有收到中断信号\n");
    } else {
        printf("总共收到 %d 次中断信号\n", (int)interrupt_count);
    }
    
    // 恢复默认处理器
    signal(SIGINT, SIG_DFL);
    interrupt_count = 0;  // 重置计数器
    
    printf("\n");
}

// 演示异常信号处理
void demo_exception_handling(void) {
    printf("=== 异常信号处理演示 ===\n");
    
    // 设置浮点异常处理器
    printf("设置SIGFPE处理器并触发除零异常...\n");
    signal(SIGFPE, sigfpe_handler);
    
    // 注意：整数除零在某些系统上可能不会产生SIGFPE
    // 浮点除零更可能产生信号
    signal_received = 0;
    
    // 使用raise直接发送信号，因为除零行为是未定义的
    printf("使用raise()发送SIGFPE信号...\n");
    raise(SIGFPE);
    
    if (signal_received == SIGFPE) {
        printf("成功处理了SIGFPE信号\n");
    }
    
    // 恢复默认处理器
    signal(SIGFPE, SIG_DFL);
    
    // 设置非法指令处理器
    printf("\n设置SIGILL处理器...\n");
    signal(SIGILL, sigill_handler);
    signal_received = 0;
    
    printf("使用raise()发送SIGILL信号...\n");
    raise(SIGILL);
    
    if (signal_received == SIGILL) {
        printf("成功处理了SIGILL信号\n");
    }
    
    signal(SIGILL, SIG_DFL);
    
    printf("\n");
}

// 演示信号忽略
void demo_signal_ignore(void) {
    printf("=== 信号忽略演示 ===\n");
    
    printf("设置忽略SIGTERM信号...\n");
    if (signal(SIGTERM, SIG_IGN) == SIG_ERR) {
        printf("设置信号忽略失败\n");
        return;
    }
    
    printf("发送SIGTERM信号（应该被忽略）...\n");
    raise(SIGTERM);
    printf("程序继续运行，信号被忽略\n");
    
    // 恢复默认处理器
    signal(SIGTERM, SIG_DFL);
    printf("SIGTERM处理器已恢复为默认\n");
    
    printf("\n");
}

// 演示原子类型操作
volatile sig_atomic_t atomic_counter = 0;
volatile sig_atomic_t atomic_flag = 0;

void atomic_signal_handler(int sig) {
    atomic_counter++;
    atomic_flag = 1;
    printf("原子信号处理器: 计数器 = %d\n", (int)atomic_counter);
}

void demo_atomic_operations(void) {
    printf("=== 原子操作演示 ===\n");
    
    printf("sig_atomic_t类型大小: %zu 字节\n", sizeof(sig_atomic_t));
    
    // 设置使用原子变量的信号处理器
    signal(SIGUSR1, atomic_signal_handler);
    
    printf("发送多个SIGUSR1信号...\n");
    for (int i = 0; i < 3; i++) {
        printf("发送信号 %d...\n", i + 1);
        raise(SIGUSR1);
        
        // 等待信号处理完成
        while (atomic_flag == 0) {
            // 忙等待（在实际应用中应该使用更好的同步机制）
        }
        atomic_flag = 0;
    }
    
    printf("最终计数器值: %d\n", (int)atomic_counter);
    
    // 恢复默认处理器
    signal(SIGUSR1, SIG_DFL);
    atomic_counter = 0;
    
    printf("\n");
}

// 信号处理的最佳实践示例
volatile sig_atomic_t cleanup_requested = 0;
volatile sig_atomic_t emergency_exit = 0;

void cleanup_handler(int sig) {
    if (sig == SIGTERM) {
        cleanup_requested = 1;
        printf("\n收到终止信号，请求清理...\n");
    } else if (sig == SIGINT) {
        emergency_exit = 1;
        printf("\n收到中断信号，紧急退出...\n");
    }
}

void demo_best_practices(void) {
    printf("=== 信号处理最佳实践演示 ===\n");
    
    // 设置清理处理器
    signal(SIGTERM, cleanup_handler);
    signal(SIGINT, cleanup_handler);
    
    printf("程序运行中，可以发送信号测试:\n");
    printf("- SIGTERM: 请求正常清理\n");
    printf("- SIGINT (Ctrl+C): 紧急退出\n");
    printf("程序将运行3秒...\n");
    
    // 模拟程序主循环
    for (int i = 0; i < 30; i++) {
        // 检查信号标志
        if (emergency_exit) {
            printf("执行紧急退出...\n");
            break;
        }
        
        if (cleanup_requested) {
            printf("执行正常清理...\n");
            // 在这里进行资源清理
            printf("清理完成，程序退出\n");
            break;
        }
        
        // 模拟工作
        printf("工作中... %d/30\n", i + 1);
        usleep(100000);  // 0.1秒
    }
    
    if (!cleanup_requested && !emergency_exit) {
        printf("程序正常完成\n");
    }
    
    // 恢复默认处理器
    signal(SIGTERM, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    
    printf("\n");
}

// 实际应用示例：简单的服务器信号处理
typedef struct {
    int running;
    int connections;
    char status[64];
} server_state_t;

server_state_t server = {1, 0, "运行中"};
volatile sig_atomic_t server_shutdown = 0;
volatile sig_atomic_t server_reload = 0;

void server_signal_handler(int sig) {
    switch (sig) {
        case SIGTERM:
        case SIGINT:
            server_shutdown = 1;
            break;
        case SIGUSR1:
            server_reload = 1;
            break;
        default:
            break;
    }
}

void demo_practical_example(void) {
    printf("=== 实际应用示例：服务器信号处理 ===\n");
    
    // 设置信号处理器
    signal(SIGTERM, server_signal_handler);
    signal(SIGINT, server_signal_handler);
    signal(SIGUSR1, server_signal_handler);
    
    printf("模拟服务器启动...\n");
    printf("支持的信号:\n");
    printf("- SIGTERM/SIGINT: 优雅关闭\n");
    printf("- SIGUSR1: 重新加载配置\n");
    
    // 模拟服务器主循环
    int cycle = 0;
    while (server.running && cycle < 20) {
        // 检查信号
        if (server_shutdown) {
            printf("收到关闭信号，开始优雅关闭...\n");
            
            // 停止接受新连接
            strcpy(server.status, "关闭中");
            
            // 等待现有连接完成
            while (server.connections > 0) {
                printf("等待 %d 个连接完成...\n", server.connections);
                server.connections--;  // 模拟连接完成
                sleep(1);
            }
            
            printf("所有连接已关闭，服务器停止\n");
            server.running = 0;
            break;
        }
        
        if (server_reload) {
            printf("收到重载信号，重新加载配置...\n");
            strcpy(server.status, "重载配置中");
            
            // 模拟配置重载
            sleep(1);
            
            strcpy(server.status, "运行中");
            printf("配置重载完成\n");
            server_reload = 0;
        }
        
        // 模拟服务器工作
        cycle++;
        server.connections = (cycle % 5) + 1;  // 模拟连接数变化
        printf("服务器状态: %s, 连接数: %d, 周期: %d\n", 
               server.status, server.connections, cycle);
        
        sleep(1);
    }
    
    if (cycle >= 20) {
        printf("演示完成，服务器正常停止\n");
    }
    
    // 恢复默认处理器
    signal(SIGTERM, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGUSR1, SIG_DFL);
    
    printf("\n");
}

int main(void) {
    printf("C标准库 signal.h 演示程序\n");
    printf("=========================\n\n");
    
    demo_basic_signal_handling();
    demo_interrupt_handling();
    demo_exception_handling();
    demo_signal_ignore();
    demo_atomic_operations();
    demo_best_practices();
    demo_practical_example();
    
    printf("signal.h 演示完成！\n");
    printf("\n重要提示:\n");
    printf("1. 信号处理器应该尽可能简单，避免调用非异步安全函数\n");
    printf("2. 在信号处理器中只使用sig_atomic_t类型的变量\n");
    printf("3. 某些信号（如SIGKILL, SIGSTOP）无法被捕获或忽略\n");
    printf("4. 信号处理是平台相关的，移植时需要注意\n");
    printf("5. 现代程序更倾向于使用signalfd或类似机制而不是传统信号\n");
    
    return 0;
}
