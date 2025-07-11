// template_method.cpp
#include <iostream>

class DataProcessor {
public:
    void process() {
        loadData();
        analyzeData();
        saveResult();
    }

    virtual ~DataProcessor() = default;

protected:
    virtual void loadData() = 0;
    virtual void analyzeData() = 0;
    void saveResult() {
        std::cout << "Saving results to database..." << std::endl;
    }
};

class CSVProcessor : public DataProcessor {
protected:
    void loadData() override {
        std::cout << "Loading CSV data..." << std::endl;
    }

    void analyzeData() override {
        std::cout << "Analyzing CSV data..." << std::endl;
    }
};

class XMLProcessor : public DataProcessor {
protected:
    void loadData() override {
        std::cout << "Loading XML data..." << std::endl;
    }

    void analyzeData() override {
        std::cout << "Analyzing XML data..." << std::endl;
    }
};

int main() {
    CSVProcessor csv;
    csv.process();

    XMLProcessor xml;
    xml.process();
    
    return 0;
}