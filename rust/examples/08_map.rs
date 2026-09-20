// 主题说明：映射 —— HashMap 增删改查与 entry API、get 查询、遍历顺序不保证，BTreeMap 按 key 有序。
// 运行命令：cargo run --example 08_map
// 预期输出（关键行）：
//   Alice = 95
//   entry 累加后 Bob = Some(75)
//   BTreeMap 遍历（有序）：alice=95, bob=75, carol=60

use std::collections::{BTreeMap, HashMap};

fn main() {
    let mut scores: HashMap<String, i32> = HashMap::new();

    // ---- 插入与更新：同 key 再次 insert 直接覆盖 ----
    scores.insert(String::from("Alice"), 90);
    scores.insert(String::from("Alice"), 95); // 覆盖旧值
    println!("insert 后 Alice = {:?}", scores.get("Alice"));

    // ---- entry API：一步完成"不存在则初始化"，是计数/累加的惯用写法 ----
    let bob = scores.entry(String::from("Bob")).or_insert(0); // 不存在才插入 0
    *bob += 75; // 拿到 &mut i32 原地累加
    scores.entry(String::from("Carol")).or_insert(60); // 只初始化不修改
    println!("entry 累加后 Bob = {:?}", scores.get("Bob"));

    // ---- get：返回 Option<&V>，用类型系统表达"可能没有" ----
    if let Some(s) = scores.get("Alice") {
        println!("Alice = {}", s);
    }
    println!("Dave 存在吗？{}", scores.contains_key("Dave"));

    // ---- 修改与删除 ----
    if let Some(old) = scores.insert(String::from("Carol"), 61) {
        println!("insert 返回被覆盖的旧值：Carol 原 {}", old);
    }
    scores.insert(String::from("Carol"), 60); // 改回 60，保持数据稳定
    let removed = scores.remove("Nobody"); // 删除不存在的 key 返回 None
    println!("remove 不存在的 key = {:?}", removed);

    // ---- 遍历：HashMap 顺序不保证，需要顺序请用 BTreeMap ----
    println!("HashMap 遍历（顺序不保证，共 {} 项）：", scores.len());
    for (name, score) in &scores {
        println!("  {} -> {}", name, score);
    }

    // ---- BTreeMap：基于 B 树，按 key 有序遍历 ----
    let mut ranked: BTreeMap<String, i32> = BTreeMap::new();
    ranked.insert(String::from("carol"), 60);
    ranked.insert(String::from("alice"), 95);
    ranked.insert(String::from("bob"), 75);
    let line: String = ranked
        .iter()
        .map(|(k, v)| format!("{}={}", k, v))
        .collect::<Vec<_>>()
        .join(", ");
    println!("BTreeMap 遍历（有序）：{}", line);

    // 有序带来的能力：range 区间查询 [b, d)
    for (k, v) in ranked.range("b".to_string().."d".to_string()) {
        println!("range b..d 命中：{} = {}", k, v);
    }

    // ---- 典型应用：用 entry 统计字符频率 ----
    let mut freq: HashMap<char, i32> = HashMap::new();
    for c in "abracadabra".chars() {
        *freq.entry(c).or_insert(0) += 1;
    }
    println!("abracadabra 字频：{:?}", freq);
}
