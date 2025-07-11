#include <iostream>

//UML表示：<> 依赖箭头
class SecretKeeper {
private:
    int secretCode = 42;
    
    friend class TrustedFriend; // 友元声明
};

class TrustedFriend {
public:
    static void revealSecret(const SecretKeeper& keeper) {
        std::cout << "The secret code is: " << keeper.secretCode << std::endl;
    }
};

int main() {
    SecretKeeper sk;
    TrustedFriend::revealSecret(sk); // 输出: The secret code is: 42
    return 0;
}