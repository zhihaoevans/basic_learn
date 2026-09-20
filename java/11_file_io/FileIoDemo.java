/*
 * 主题说明：Java 文件读写 —— Files.writeString/readString 一写一读、
 *           BufferedReader 逐行读取、java.io.File 遍历目录；临时文件用
 *           Files.createTempFile 创建并显式清理，不留垃圾。
 * 运行命令：java java/11_file_io/FileIoDemo.java
 * 预期输出（关键行）：
 *   写入并读回（Files.readString）: 第一行：Hello 文件
 *   BufferedReader 逐行读到 3 行
 *   目录内文件数 = 3
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileIoDemo {

    public static void main(String[] args) throws IOException {
        // 知识点 1：Files.writeString / readString —— 最简单的一写一读（JDK 11+）
        Path tmp = Files.createTempFile("demo", ".txt");     // 在系统临时目录创建空文件
        try {
            Files.writeString(tmp, "第一行：Hello 文件\n第二行：NIO 读写\n第三行：end\n",
                    StandardCharsets.UTF_8);                  // 整个字符串一次写入
            String back = Files.readString(tmp, StandardCharsets.UTF_8);
            System.out.println("[1] 写入并读回（Files.readString）: "
                    + back.split("\n")[0]);

            // 知识点 2：BufferedReader 逐行读取 —— 适合大文件，流式处理不占内存
            try (BufferedReader br = Files.newBufferedReader(tmp, StandardCharsets.UTF_8)) {
                int lines = 0;
                String line;
                while ((line = br.readLine()) != null) {      // readLine 到结尾返回 null
                    lines++;
                    System.out.println("    第 " + lines + " 行内容: " + line);
                }
                System.out.println("[2] BufferedReader 逐行读到 " + lines + " 行");
            }

            // 知识点 3：追加写入 —— 第三个参数传 StandardOpenOption.APPEND
            Files.writeString(tmp, "第四行：追加\n", StandardCharsets.UTF_8,
                    java.nio.file.StandardOpenOption.APPEND);
            System.out.println("[3] 追加后总行数 = "
                    + Files.readAllLines(tmp, StandardCharsets.UTF_8).size());
        } finally {
            // 临时文件清理：finally 里保证删除，不留垃圾
            Files.deleteIfExists(tmp);
            System.out.println("    临时文件已清理: " + tmp.getFileName());
        }

        // 知识点 4：File 遍历目录 —— listFiles() 列出直接子项；配合 isFile/isDirectory 过滤
        Path tmpDir = Files.createTempDirectory("demo-dir"); // 自建临时目录做演示
        try {
            for (String name : new String[]{"a.txt", "b.txt", "c.log"}) {
                Files.writeString(tmpDir.resolve(name), name);   // 在临时目录里造三个文件
            }
            File dir = tmpDir.toFile();                          // Path 转 java.io.File
            File[] files = dir.listFiles();
            System.out.println("[4] 目录内文件数 = " + (files == null ? 0 : files.length));
            if (files != null) {
                for (File f : files) {
                    System.out.println("    " + f.getName() + " isFile=" + f.isFile()
                            + " 大小=" + f.length() + "B");
                }
            }
        } finally {
            // 清理：先删文件再删目录
            try (var stream = Files.list(tmpDir)) {
                stream.forEach(p -> p.toFile().delete());
            }
            Files.deleteIfExists(tmpDir);
            System.out.println("    临时目录已清理");
        }
    }
}
