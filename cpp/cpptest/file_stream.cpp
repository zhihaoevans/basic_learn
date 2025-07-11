#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

// Structure for demonstration
struct Person {
    std::string name;
    int age;
    double salary;

    Person(const std::string& n = "", int a = 0, double s = 0.0)
        : name(n), age(a), salary(s) {}
};

// Stream insertion operator overloading
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.name << "," << p.age << "," << std::fixed << std::setprecision(2) << p.salary;
    return os;
}

// Stream extraction operator overloading
std::istream& operator>>(std::istream& is, Person& p) {
    std::string line;
    if (std::getline(is, line)) {
        std::stringstream ss(line);
        std::string age_str, salary_str;
        
        std::getline(ss, p.name, ',');
        std::getline(ss, age_str, ',');
        std::getline(ss, salary_str);
        
        p.age = std::stoi(age_str);
        p.salary = std::stod(salary_str);
    }
    return is;
}

int main() {
    std::cout << "=== File and Stream Examples ===" << std::endl;

    // 1. Basic file output
    std::cout << "\n1. Basic file output:" << std::endl;
    std::ofstream outFile("test.txt");
    if (outFile.is_open()) {
        outFile << "Hello, File I/O!" << std::endl;
        outFile << 42 << std::endl;
        outFile << 3.14159 << std::endl;
        outFile.close();
        std::cout << "Data written to test.txt" << std::endl;
    }

    // 2. Basic file input
    std::cout << "\n2. Basic file input:" << std::endl;
    std::ifstream inFile("test.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << "Read: " << line << std::endl;
        }
        inFile.close();
    }

    // 3. String streams
    std::cout << "\n3. String streams:" << std::endl;
    std::stringstream ss;
    ss << "Hello" << " " << "World" << " " << 42;
    std::string word;
    while (ss >> word) {
        std::cout << "Word: " << word << std::endl;
    }

    // 4. Formatting output
    std::cout << "\n4. Formatting output:" << std::endl;
    double pi = 3.14159265359;
    std::cout << "Default: " << pi << std::endl;
    std::cout << "Fixed: " << std::fixed << pi << std::endl;
    std::cout << "Scientific: " << std::scientific << pi << std::endl;
    std::cout << "Precision 2: " << std::fixed << std::setprecision(2) << pi << std::endl;
    std::cout << "Width 10: " << std::setw(10) << std::right << pi << std::endl;

    // 5. Binary file operations
    std::cout << "\n5. Binary file operations:" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Writing binary file
    std::ofstream binOutFile("data.bin", std::ios::binary);
    if (binOutFile.is_open()) {
        binOutFile.write(reinterpret_cast<char*>(numbers.data()),
                        numbers.size() * sizeof(int));
        binOutFile.close();
        std::cout << "Binary data written" << std::endl;
    }
    
    // Reading binary file
    std::vector<int> readNumbers(5);
    std::ifstream binInFile("data.bin", std::ios::binary);
    if (binInFile.is_open()) {
        binInFile.read(reinterpret_cast<char*>(readNumbers.data()),
                      readNumbers.size() * sizeof(int));
        binInFile.close();
        std::cout << "Read numbers: ";
        for (int n : readNumbers) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }

    // 6. Custom object serialization
    std::cout << "\n6. Custom object serialization:" << std::endl;
    std::vector<Person> people = {
        Person("Alice", 30, 50000.0),
        Person("Bob", 25, 45000.0),
        Person("Charlie", 35, 60000.0)
    };
    
    // Writing objects to CSV file
    std::ofstream csvOutFile("people.csv");
    if (csvOutFile.is_open()) {
        for (const auto& person : people) {
            csvOutFile << person << std::endl;
        }
        csvOutFile.close();
        std::cout << "People data written to CSV" << std::endl;
    }
    
    // Reading objects from CSV file
    std::vector<Person> readPeople;
    std::ifstream csvInFile("people.csv");
    if (csvInFile.is_open()) {
        Person p;
        while (csvInFile >> p) {
            readPeople.push_back(p);
        }
        csvInFile.close();
        
        std::cout << "Read people data:" << std::endl;
        for (const auto& person : readPeople) {
            std::cout << person << std::endl;
        }
    }

    // 7. File position operations
    std::cout << "\n7. File position operations:" << std::endl;
    std::fstream file("position.txt", std::ios::out | std::ios::in | std::ios::trunc);
    if (file.is_open()) {
        file << "First line\nSecond line\nThird line" << std::endl;
        
        // Move to beginning
        file.seekg(0);
        std::string line;
        std::getline(file, line);
        std::cout << "First line: " << line << std::endl;
        
        // Get current position
        std::streampos pos = file.tellg();
        
        // Read next line
        std::getline(file, line);
        std::cout << "Second line: " << line << std::endl;
        
        // Go back to saved position
        file.seekg(pos);
        std::getline(file, line);
        std::cout << "Read again: " << line << std::endl;
        
        file.close();
    }

    return 0;
} 