#include <iostream>
#include <vector>
#include <functional>

class StockMarket {
    std::vector<std::function<void(double)>> observers;
    double price = 100.0;
    
public:
    void addObserver(const std::function<void(double)>& observer) {
        observers.push_back(observer);
    }

    void setPrice(double newPrice) {
        price = newPrice;
        notify();
    }

private:
    void notify() {
        for (const auto& observer : observers) {
            observer(price);
        }
    }
};

int main() {
    StockMarket market;
    
    // 添加观察者（Lambda表达式）
    market.addObserver([](double price) {
        std::cout << "Mobile App: Price updated to $" << price << std::endl;
    });
    
    market.addObserver([](double price) {
        std::cout << "Web Dashboard: New stock price $" << price << std::endl;
    });

    market.setPrice(105.5);
    market.setPrice(98.75);
    
    return 0;
}