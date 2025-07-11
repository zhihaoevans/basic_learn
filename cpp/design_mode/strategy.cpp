#include <iostream>
#include <vector>
#include <algorithm>

// 策略接口
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

// 具体策略
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Bubble Sort" << std::endl;
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data.size()-i-1; ++j) {
                if (data[j] > data[j+1]) {
                    std::swap(data[j], data[j+1]);
                }
            }
        }
    }
};

class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Quick Sort" << std::endl;
        std::sort(data.begin(), data.end());
    }
};

// 上下文类
class Sorter {
    std::unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(std::unique_ptr<SortStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }
    
    void executeSort(std::vector<int>& data) {
        strategy->sort(data);
    }
};

int main() {
    Sorter sorter;
    std::vector<int> data = {5, 2, 9, 1, 5, 6};

    sorter.setStrategy(std::make_unique<BubbleSort>());
    sorter.executeSort(data);
    for (int num : data) std::cout << num << " ";
    std::cout << std::endl;

    data = {5, 2, 9, 1, 5, 6};
    sorter.setStrategy(std::make_unique<QuickSort>());
    sorter.executeSort(data);
    for (int num : data) std::cout << num << " ";
    
    return 0;
}