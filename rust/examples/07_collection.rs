// 主题说明：集合 —— 定长数组 [T; N]、动态数组 Vec 的增删改查与迭代、切片 &[] 作为函数参数。
// 运行命令：cargo run --example 07_collection
// 预期输出（关键行）：
//   arr = [10, 20, 30, 40, 50]
//   insert/pop/remove 后 v = [0, 2, 3, 4]，popped = Some(5)，removed = 1
//   切片 [1..4] = [20, 30, 40]，求和 = 90

// 切片参数：&[i32] 同时接受数组与 Vec 的引用，是最通用的写法
fn sum_slice(nums: &[i32]) -> i32 {
    nums.iter().sum()
}

fn main() {
    // ---- 数组 [T; N]：长度是类型的一部分，栈上分配 ----
    let arr: [i32; 5] = [10, 20, 30, 40, 50];
    let zeros = [0; 3]; // [元素; 重复次数] 初始化
    println!("arr = {:?}，长度 {}，首元素 {}", arr, arr.len(), arr[0]);
    println!("zeros = {:?}，占 {} 字节", zeros, std::mem::size_of_val(&zeros));

    // ---- Vec：堆上动态数组，最常用的列表 ----
    let mut v: Vec<i32> = Vec::new(); // 空向量，靠类型标注/后续插入确定元素类型
    v.push(1);
    v.push(2);
    println!("v = {:?}，容量 {}", v, v.capacity());

    let mut v2 = vec![3, 4, 5]; // vec! 宏快速创建
    v.append(&mut v2); // 整体拼接，v2 被清空（所有权转移）
    println!("append 后 v = {:?}，v2 = {:?}", v, v2);

    v.insert(0, 0); // 指定下标插入
    let popped = v.pop(); // 弹出末尾，返回 Option
    let removed = v.remove(1); // 移除指定下标，后面元素前移
    println!("insert/pop/remove 后 v = {:?}，popped = {:?}，removed = {}", v, popped, removed);

    // 越界访问：[] 会 panic，get 返回 Option 更安全
    let last = v.get(v.len().saturating_sub(1));
    println!("安全取末尾 get = {:?}，越界 get = {:?}", last, v.get(99));

    // ---- 遍历：for &不可变引用（只读）/ &mut（可改）----
    let mut nums = vec![10, 20, 30];
    for x in &nums {
        print!("{} ", x); // 迭代 &Vec<T>，不夺所有权
    }
    println!();
    for x in &mut nums {
        *x *= 10; // 解引用修改
    }
    println!("原地乘 10 = {:?}", nums);
    // for x in nums { ... } // 按值迭代会夺走所有权，之后 nums 不可再用

    // 常用操作：contains / iter().max / len / 是否为空
    println!("包含 200？{}，最大值 = {:?}", nums.contains(&200), nums.iter().max());

    // ---- 切片：数组的视图 ----
    let slice = &arr[1..4]; // 借用 arr 的一段
    println!("切片 [1..4] = {:?}，求和 = {}", slice, sum_slice(slice));
    println!("数组也能传给切片函数 = {}", sum_slice(&arr));
    println!("Vec 传 &v[..] 同样可以 = {}", sum_slice(&nums[..]));
}
