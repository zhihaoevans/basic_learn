#include <iostream>
#include <memory>
#include <vector>

class Resource {
    std::string name;
public:
    Resource(const std::string& n) : name(n) {
        std::cout << "Resource " << name << " constructed" << std::endl;
    }
    ~Resource() {
        std::cout << "Resource " << name << " destroyed" << std::endl;
    }
    void use() {
        std::cout << "Using resource " << name << std::endl;
    }
};

// Function demonstrating unique_ptr parameter passing
void process_unique(std::unique_ptr<Resource> ptr) {
    ptr->use();
    // ptr will be automatically deleted when function ends
}

// Function demonstrating shared_ptr parameter passing
void process_shared(std::shared_ptr<Resource> ptr) {
    std::cout << "Shared count: " << ptr.use_count() << std::endl;
    ptr->use();
}

int main() {
    std::cout << "=== Smart Pointer Examples ===" << std::endl;

    // unique_ptr example
    std::cout << "\n1. unique_ptr examples:" << std::endl;
    {
        std::unique_ptr<Resource> uniq1(new Resource("Unique1"));
        uniq1->use();

        // Transfer ownership
        std::unique_ptr<Resource> uniq2 = std::move(uniq1);
        if (!uniq1) {
            std::cout << "uniq1 is now empty" << std::endl;
        }
        
        // Pass to function (transfers ownership)
        process_unique(std::move(uniq2));
        // uniq2 is now empty
    } // Resource is automatically deleted here

    // shared_ptr example
    std::cout << "\n2. shared_ptr examples:" << std::endl;
    {
        auto shared1 = std::make_shared<Resource>("Shared1");
        std::cout << "Reference count: " << shared1.use_count() << std::endl;
        
        {
            auto shared2 = shared1; // Reference count increases
            std::cout << "Reference count after sharing: " << shared1.use_count() << std::endl;
            process_shared(shared2);
        } // shared2 goes out of scope, count decrements
        
        std::cout << "Reference count after inner scope: " << shared1.use_count() << std::endl;
    } // Last reference gone, Resource is deleted

    // weak_ptr example
    std::cout << "\n3. weak_ptr examples:" << std::endl;
    {
        std::weak_ptr<Resource> weak1;
        {
            auto shared = std::make_shared<Resource>("WeakResource");
            weak1 = shared;
            
            if (auto temp = weak1.lock()) {
                std::cout << "Resource still alive, using it" << std::endl;
                temp->use();
            }
        } // shared_ptr destroyed here
        
        // Try to access after shared_ptr is destroyed
        if (auto temp = weak1.lock()) {
            std::cout << "Resource still alive" << std::endl;
        } else {
            std::cout << "Resource no longer available" << std::endl;
        }
    }

    return 0;
} 