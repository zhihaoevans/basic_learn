// chain.cpp
#include <iostream>
#include <memory>

class Handler {
public:
    virtual void handleRequest(int level) = 0;
    void setNext(std::shared_ptr<Handler> next) { next_ = next; }
    virtual ~Handler() = default;

protected:
    std::shared_ptr<Handler> next_;
};

class ConcreteHandler1 : public Handler {
public:
    void handleRequest(int level) override {
        if (level <= 3) {
            std::cout << "Handler1 processed level " << level << std::endl;
        } else if (next_) {
            next_->handleRequest(level);
        }
    }
};

class ConcreteHandler2 : public Handler {
public:
    void handleRequest(int level) override {
        if (level <= 6) {
            std::cout << "Handler2 processed level " << level << std::endl;
        } else if (next_) {
            next_->handleRequest(level);
        }
    }
};

class ConcreteHandler3 : public Handler {
public:
    void handleRequest(int level) override {
        if (level <= 9) {
            std::cout << "Handler3 processed level " << level << std::endl;
        } else {
            std::cout << "No handler for level " << level << std::endl;
        }
    }
};

int main() {
    auto h1 = std::make_shared<ConcreteHandler1>();
    auto h2 = std::make_shared<ConcreteHandler2>();
    auto h3 = std::make_shared<ConcreteHandler3>();

    h1->setNext(h2);
    h2->setNext(h3);

    h1->handleRequest(2);  // Handler1
    h1->handleRequest(5);  // Handler2
    h1->handleRequest(7);  // Handler3
    h1->handleRequest(10); // No handler

    return 0;
}