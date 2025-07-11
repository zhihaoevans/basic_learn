#include <iostream>
#include <type_traits>

// Traditional enum (unscoped)
enum Color {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};

// Scoped enum (enum class)
enum class TrafficLight {
    RED,
    YELLOW,
    GREEN
};

// Enum class with specified underlying type
enum class Flags : uint8_t {
    NONE = 0,
    READ = 1,
    WRITE = 2,
    EXECUTE = 4
};

// Enum class for permissions with operator overloading
enum class Permission : unsigned int {
    NONE = 0,
    READ = 1 << 0,
    WRITE = 1 << 1,
    EXECUTE = 1 << 2
};

// Operator overloading for Permission
Permission operator|(Permission a, Permission b) {
    return static_cast<Permission>(
        static_cast<unsigned int>(a) | static_cast<unsigned int>(b)
    );
}

Permission operator&(Permission a, Permission b) {
    return static_cast<Permission>(
        static_cast<unsigned int>(a) & static_cast<unsigned int>(b)
    );
}

// Function to demonstrate type safety
void handleTrafficLight(TrafficLight light) {
    switch (light) {
        case TrafficLight::RED:
            std::cout << "Stop!" << std::endl;
            break;
        case TrafficLight::YELLOW:
            std::cout << "Caution!" << std::endl;
            break;
        case TrafficLight::GREEN:
            std::cout << "Go!" << std::endl;
            break;
    }
}

int main() {
    std::cout << "=== Enum Class Examples ===" << std::endl;

    // 1. Traditional enum vs enum class
    std::cout << "\n1. Traditional enum vs enum class:" << std::endl;
    Color color = RED;  // Traditional enum can be used without scope
    TrafficLight light = TrafficLight::RED;  // Enum class requires scope

    std::cout << "Color (traditional): " << color << std::endl;
    // std::cout << light << std::endl;  // Won't compile - no implicit conversion

    // 2. Type safety
    std::cout << "\n2. Type safety demonstration:" << std::endl;
    // color = light;  // Won't compile - no implicit conversion
    // if (TrafficLight::RED == Color::RED) {}  // Won't compile - different types

    // 3. Underlying type
    std::cout << "\n3. Underlying type information:" << std::endl;
    std::cout << "Size of Flags: " << sizeof(Flags) << " bytes" << std::endl;
    std::cout << "Is Flags unsigned: " << std::is_unsigned<std::underlying_type<Flags>::type>::value << std::endl;

    // 4. Using enum class values
    std::cout << "\n4. Using enum class values:" << std::endl;
    handleTrafficLight(TrafficLight::RED);
    handleTrafficLight(TrafficLight::YELLOW);
    handleTrafficLight(TrafficLight::GREEN);

    // 5. Bitwise operations with enum class
    std::cout << "\n5. Bitwise operations:" << std::endl;
    Permission perm = Permission::READ | Permission::WRITE;
    
    if ((perm & Permission::READ) == Permission::READ) {
        std::cout << "Has read permission" << std::endl;
    }
    
    if ((perm & Permission::EXECUTE) == Permission::NONE) {
        std::cout << "No execute permission" << std::endl;
    }

    // 6. Explicit conversion
    std::cout << "\n6. Explicit conversion:" << std::endl;
    int lightValue = static_cast<int>(TrafficLight::GREEN);
    std::cout << "Value of TrafficLight::GREEN: " << lightValue << std::endl;

    return 0;
} 