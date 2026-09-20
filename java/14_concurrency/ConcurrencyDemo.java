/*
 * 主题说明：Java 并发入门 —— 创建线程的两种方式（继承 Thread / 实现 Runnable）、
 *           线程池 ExecutorService 与 Future 取结果、synchronized 修复
 *           多线程计数器的竞态问题，以及 join 等待线程结束。
 * 运行命令：java java/14_concurrency/ConcurrencyDemo.java
 * 预期输出（关键行）：
 *   两条线程各自在跑（输出顺序可能交错）
 *   join 后: 两条线程都结束了，加锁线程写入的共享数据 = 50000
 *   未同步计数 = xxxxx（通常 < 100000，丢更新）
 *   synchronized 计数 = 100000（永远正确）
 */

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class ConcurrencyDemo {

    // 两个线程共享的对象 —— 演示数据可见性与竞态
    static int sharedCounter = 0;
    static final int LOOPS = 50_000;              // 每条线程自增的次数

    // 知识点 1a：方式一 —— 继承 Thread，重写 run()
    static class HelloThread extends Thread {
        @Override
        public void run() {
            System.out.println("    [Thread 子类] " + getName() + " 在跑");
            long local = 0;
            for (int i = 0; i < LOOPS; i++) {
                local++;                          // 局部变量各线程私有，互不干扰
            }
        }
    }

    // 知识点 1b：方式二 —— 实现 Runnable（更推荐：不占用继承位，任务与线程解耦）
    static class CountTask implements Runnable {
        @Override
        public void run() {
            for (int i = 0; i < LOOPS; i++) {
                synchronized (ConcurrencyDemo.class) {   // 知识点 4：synchronized 互斥锁
                    sharedCounter++;
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        System.out.println("[1] 创建线程的两种方式：");

        // 方式一：new 一个 Thread 子类并 start()（不是 run()！run 只是普通方法调用）
        Thread t1 = new HelloThread();

        // 方式二：把 Runnable 任务交给 Thread
        Thread t2 = new Thread(new CountTask(), "runnable-线程");

        t1.start();
        t2.start();
        System.out.println("[2] 两条线程各自在跑（输出顺序可能交错）");

        // 知识点 5：join —— 阻塞等待某条线程结束，再继续主线程
        t1.join();
        t2.join();
        System.out.println("[3] join 后: 两条线程都结束了，加锁线程写入的共享数据 = " + sharedCounter
                + "（正好 " + LOOPS + "，无丢失）");

        // 知识点 4（对照实验）：synchronized 与非同步的差别
        System.out.println("[4] 对照实验开始：各起 2 条线程对同一个 int 自增 " + LOOPS + " 次");
        int unsync = runRace(false);              // 不加锁：大概率丢更新
        int sync = runRace(true);                 // 加锁：结果一定正确
        System.out.println("[4] 未同步计数 = " + unsync + "（通常 < " + (LOOPS * 2) + "，丢更新）");
        System.out.println("[4] synchronized 计数 = " + sync + "（永远正确）");

        // 知识点 3：线程池 + Future —— 生产推荐的用法：提交 Callable 任务，拿返回值
        ExecutorService pool = Executors.newFixedThreadPool(2);   // 固定 2 条线程的池
        try {
            Future<Integer> f1 = pool.submit(new SquareTask(12));          // 提交有返回值的任务
            Future<String> f2 = pool.submit(() -> "Lambda 也能当任务");     // Lambda 即 Runnable/Callable
            System.out.println("[5] Future.get() 取结果: 12 的平方 = " + f1.get());  // get 会阻塞到完成
            System.out.println("[5] Future.get() 取结果: " + f2.get());
        } finally {
            pool.shutdown();                      // 用完必须关闭线程池
            pool.awaitTermination(5, TimeUnit.SECONDS);
        }
        System.out.println("[5] 线程池已关闭，main 结束");
    }

    /** 对照实验：incSynchronized 决定自增是否加锁，返回最终计数 */
    static int runRace(boolean useLock) throws InterruptedException {
        sharedCounter = 0;
        Runnable task = () -> {
            for (int i = 0; i < LOOPS; i++) {
                if (useLock) {
                    synchronized (ConcurrencyDemo.class) {
                        sharedCounter++;
                    }
                } else {
                    sharedCounter++;              // 无锁版本：并发下会丢更新
                }
            }
        };
        Thread a = new Thread(task);
        Thread b = new Thread(task);
        a.start();
        b.start();
        a.join();
        b.join();
        return sharedCounter;
    }

    /** Callable<V>：带返回值的任务，可抛受检异常，交给线程池执行 */
    static class SquareTask implements Callable<Integer> {
        private final int n;
        SquareTask(int n) { this.n = n; }
        @Override
        public Integer call() {
            return n * n;
        }
    }
}
