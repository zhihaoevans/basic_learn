// builder.cpp
#include <iostream>
#include <string>
#include <memory>

class Pizza {
public:
    void setDough(const std::string& dough) { dough_ = dough; }
    void setSauce(const std::string& sauce) { sauce_ = sauce; }
    void setTopping(const std::string& topping) { topping_ = topping; }

    void showPizza() const {
        std::cout << "Pizza with " << dough_ << " dough, "
                  << sauce_ << " sauce and " << topping_ << std::endl;
    }

private:
    std::string dough_;
    std::string sauce_;
    std::string topping_;
};

class PizzaBuilder {
public:
    virtual ~PizzaBuilder() = default;
    void createNewPizza() { pizza_ = std::make_unique<Pizza>(); }
    Pizza* getPizza() { return pizza_.release(); }
    
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;

protected:
    std::unique_ptr<Pizza> pizza_;
};

class HawaiianPizzaBuilder : public PizzaBuilder {
public:
    void buildDough() override { pizza_->setDough("cross"); }
    void buildSauce() override { pizza_->setSauce("mild"); }
    void buildTopping() override { pizza_->setTopping("ham+pineapple"); }
};

class SpicyPizzaBuilder : public PizzaBuilder {
public:
    void buildDough() override { pizza_->setDough("pan baked"); }
    void buildSauce() override { pizza_->setSauce("hot"); }
    void buildTopping() override { pizza_->setTopping("pepperoni+chili"); }
};

class Cook {
public:
    void makePizza(PizzaBuilder* builder) {
        builder->createNewPizza();
        builder->buildDough();
        builder->buildSauce();
        builder->buildTopping();
    }
};

int main() {
    Cook cook;
    
    HawaiianPizzaBuilder hawaiianBuilder;
    cook.makePizza(&hawaiianBuilder);
    Pizza* hawaiian = hawaiianBuilder.getPizza();
    hawaiian->showPizza();

    SpicyPizzaBuilder spicyBuilder;
    cook.makePizza(&spicyBuilder);
    Pizza* spicy = spicyBuilder.getPizza();
    spicy->showPizza();

    delete hawaiian;
    delete spicy;
    return 0;
}