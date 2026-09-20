# 主题说明：Python 文件读写 —— with open 文本读/写/追加、逐行遍历、json 序列化与 pathlib 路径操作。
#           示例全部写入系统临时目录并自动清理，不污染仓库。
# 运行命令：python3 python/11_file_io.py
# 预期输出（关键行）：
#   read_text 全文：'第一行：hello\n第二行：file io\n'
#     第 3 行：第三行：appended
#   json.load 读回 port=8080，tags=['py', '基础']

import json
import tempfile
from pathlib import Path

with tempfile.TemporaryDirectory() as tmp:      # 退出 with 时自动删除整个目录
    work = Path(tmp)                            # pathlib：面向对象的路径操作

    # 写：pathlib 一行写文本（底层等价于 open + write + close）
    note = work / "notes.txt"                   # / 运算符拼接路径
    note.write_text("第一行：hello\n第二行：file io\n", encoding="utf-8")

    # 读：一次读入整个文件
    print(f"read_text 全文：{note.read_text(encoding='utf-8')!r}")

    # 追加写 + with open 逐行读取（大文件友好，内存每次只留一行）
    with open(note, "a", encoding="utf-8") as f:
        f.write("第三行：appended\n")
    with open(note, encoding="utf-8") as f:
        for lineno, line in enumerate(f, start=1):
            print(f"  第 {lineno} 行：{line.rstrip()}")   # rstrip 去掉行尾换行

    # with 的意义：无论是否抛异常都自动关闭文件（等价于 try/finally f.close()）
    # 常用模式：r 读 / w 覆盖写 / a 追加 / x 独占创建，加 b 为二进制（如 rb/wb）
    binary = work / "data.bin"
    binary.write_bytes(b"\x89PNG\r\n")
    print(f"二进制读回：{binary.read_bytes()!r}")

    # json：dump/load 面向文件，dumps/loads 面向字符串
    config = {"host": "localhost", "port": 8080, "tags": ["py", "基础"], "debug": False}
    cfg_path = work / "config.json"
    with open(cfg_path, "w", encoding="utf-8") as f:
        json.dump(config, f, ensure_ascii=False, indent=2)   # ensure_ascii=False 保留中文
    with open(cfg_path, encoding="utf-8") as f:
        loaded = json.load(f)
    print(f"json.load 读回 port={loaded['port']}，tags={loaded['tags']}")
    print(f"json.dumps 字符串：{json.dumps(config, ensure_ascii=False, sort_keys=True)}")
    json_text = '{"a": 1}'
    print(f"json.loads 逆操作：{json.loads(json_text)}")

    # pathlib 常用属性与操作
    print(f"路径信息：name={note.name}，suffix={note.suffix}，stem={note.stem}")
    print(f"父目录是临时目录：{note.parent == work}，存在：{note.exists()}")
    print(f"目录清单（排序）：{sorted(p.name for p in work.iterdir())}")
