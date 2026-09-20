// 主题说明：C++ 常用容器 —— std::array 定长数组、vector 动态数组、list 双向链表、
//           set 有序去重集合，以及迭代器遍历与 range-for 两种访问方式。
// 运行命令：./cpp/basics/build/07_collection
// 预期输出（关键行）：
//   array: 1 2 3 4 5（定长，size 编译期已知）
//   vector 尾部追加后: 10 20 30 40
//   list 头尾插入: head 10 20 30 tail
//   set 自动排序去重: 2 3 5 7 11
//   迭代器访问第 3 个元素 = 30；反向遍历: 40 30 20 10
//   迭代器循环求和 = 100

#include <array>
#include <iostream>
#include <iterator>  // std::rbegin/rbegin
#include <list>
#include <set>
#include <vector>

int main() {
    // ---- 1. std::array：定长数组，长度是模板参数，栈上分配无堆开销 ----
    std::array<int, 5> arr{1, 2, 3, 4, 5};
    std::cout << "array:";
    for (int v : arr) {
        std::cout << " " << v;
    }
    std::cout << "（定长，size 编译期已知）\n";

    // ---- 2. std::vector：最常用的动态数组，尾部追加均摊 O(1) ----
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.emplace_back(30);  // 原地构造，效果同 push_back(30)
    vec.push_back(40);
    std::cout << "vector 尾部追加后:";
    for (int v : vec) {
        std::cout << " " << v;
    }
    std::cout << "\n";
    vec.pop_back();  // 删除尾部：40 移除
    std::cout << "pop_back 后 size = " << vec.size() << "，back = " << vec.back() << "\n";

    // ---- 3. std::list：双向链表，头尾插入都是 O(1)，不支持随机下标 ----
    std::list<std::string> lst{"10", "20", "30"};
    lst.push_front("head");
    lst.push_back("tail");
    std::cout << "list 头尾插入:";
    for (const std::string& v : lst) {
        std::cout << " " << v;
    }
    std::cout << "\n";

    // ---- 4. std::set：按键排序、自动去重的集合 ----
    std::set<int> s{5, 3, 11, 2, 7, 3, 2};  // 重复的 3、2 只保留一个
    std::cout << "set 自动排序去重:";
    for (int v : s) {
        std::cout << " " << v;
    }
    std::cout << "\n";

    // ---- 5. 迭代器：容器的通用“指针”，begin 指向首元素、end 指向末尾之后 ----
    std::vector<int> demo{10, 20, 30, 40};
    auto it = demo.begin() + 2;  // vector 迭代器支持随机移动
    std::cout << "迭代器访问第 3 个元素 = " << *it << "；";
    std::cout << "反向遍历:";
    for (auto rit = demo.rbegin(); rit != demo.rend(); ++rit) {  // 反向迭代器
        std::cout << " " << *rit;
    }
    std::cout << "\n";
    // 经典循环写法（range-for 之外的另一种通用形式）：
    int sum = 0;
    for (auto i = demo.begin(); i != demo.end(); ++i) {
        sum += *i;
    }
    std::cout << "迭代器循环求和 = " << sum << "\n";

    // ---- 附：at 越界抛异常，[] 越界是未定义行为 ----
    std::cout << "demo.at(1) = " << demo.at(1) << "，demo[0] = " << demo[0] << "\n";

    return 0;
}
