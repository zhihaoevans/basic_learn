#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

// Helper function to print containers
template<typename Container>
void printContainer(const std::string& name, const Container& c) {
    std::cout << name << ": ";
    for (const auto& element : c) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Helper function to print pairs (for map)
template<typename Map>
void printMap(const std::string& name, const Map& m) {
    std::cout << name << ": ";
    for (const auto& pair : m) {
        std::cout << "{" << pair.first << ":" << pair.second << "} ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== STL Containers and Algorithms Examples ===" << std::endl;

    // 1. Vector examples
    std::cout << "\n1. Vector:" << std::endl;
    std::vector<int> vec = {5, 2, 8, 1, 9};
    printContainer("Original vector", vec);
    
    vec.push_back(6);
    std::sort(vec.begin(), vec.end());
    printContainer("Sorted vector", vec);
    
    // Vector algorithms
    auto sum = std::accumulate(vec.begin(), vec.end(), 0);
    auto max = *std::max_element(vec.begin(), vec.end());
    std::cout << "Sum: " << sum << ", Max: " << max << std::endl;

    // 2. List examples
    std::cout << "\n2. List:" << std::endl;
    std::list<std::string> lst = {"apple", "banana", "orange"};
    printContainer("Original list", lst);
    
    lst.push_front("grape");
    lst.push_back("mango");
    printContainer("Modified list", lst);
    
    lst.sort();
    printContainer("Sorted list", lst);

    // 3. Deque (double-ended queue)
    std::cout << "\n3. Deque:" << std::endl;
    std::deque<int> deq = {1, 2, 3};
    deq.push_front(0);
    deq.push_back(4);
    printContainer("Deque", deq);

    // 4. Set examples
    std::cout << "\n4. Set:" << std::endl;
    std::set<int> set1 = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    printContainer("Set (automatically sorted and unique)", set1);
    
    set1.insert(7);
    auto found = set1.find(4);
    if (found != set1.end()) {
        std::cout << "Found 4 in set" << std::endl;
    }

    // 5. Map examples
    std::cout << "\n5. Map:" << std::endl;
    std::map<std::string, int> map1 = {
        {"apple", 1},
        {"banana", 2},
        {"orange", 3}
    };
    printMap("Original map", map1);
    
    map1["grape"] = 4;
    printMap("Modified map", map1);

    // 6. Algorithm examples
    std::cout << "\n6. Algorithms:" << std::endl;
    std::vector<int> algo_vec = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    printContainer("Original vector", algo_vec);
    
    // Count
    auto count_1 = std::count(algo_vec.begin(), algo_vec.end(), 1);
    std::cout << "Count of 1: " << count_1 << std::endl;
    
    // Find
    auto it = std::find(algo_vec.begin(), algo_vec.end(), 5);
    if (it != algo_vec.end()) {
        std::cout << "Found 5 at position: " << std::distance(algo_vec.begin(), it) << std::endl;
    }
    
    // Transform
    std::vector<int> transformed(algo_vec.size());
    std::transform(algo_vec.begin(), algo_vec.end(), transformed.begin(),
                  [](int x) { return x * 2; });
    printContainer("Transformed vector (x2)", transformed);
    
    // Remove-erase idiom
    algo_vec.erase(std::remove(algo_vec.begin(), algo_vec.end(), 1),
                   algo_vec.end());
    printContainer("Vector after removing 1s", algo_vec);

    // 7. More advanced algorithms
    std::cout << "\n7. More algorithms:" << std::endl;
    std::vector<int> adv_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Partition
    auto it_partition = std::partition(adv_vec.begin(), adv_vec.end(),
                                     [](int x) { return x % 2 == 0; });
    std::vector<int> even_numbers(adv_vec.begin(), it_partition);
    printContainer("Even numbers", even_numbers);
    
    // Generate
    std::vector<int> generated(5);
    int value = 0;
    std::generate(generated.begin(), generated.end(),
                 [&value]() { return value++; });
    printContainer("Generated sequence", generated);
    
    // For_each
    std::cout << "Square of each number: ";
    std::for_each(generated.begin(), generated.end(),
                 [](int x) { std::cout << x * x << " "; });
    std::cout << std::endl;

    return 0;
} 