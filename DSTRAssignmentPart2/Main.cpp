#include <iostream>
#include "Array.hpp"

int main() {
    // Test Array with int
    Array<int> intArr;

    std::cout << "=== Testing push() ===\n";
    for (int i = 1; i <= 5; ++i) {
        intArr.push(i * 10);
        std::cout << "Pushed: " << i * 10 << "\n";
    }

    std::cout << "\n=== Testing get() ===\n";
    for (int i = 0; i < intArr.size(); ++i) {
        std::cout << "Index " << i << ": " << intArr.get(i) << "\n";
    }

    std::cout << "\n=== Testing set() ===\n";
    intArr.set(2, 999);
    std::cout << "Updated index 2 to 999\n";

    std::cout << "\n=== After set() ===\n";
    for (int i = 0; i < intArr.size(); ++i) {
        std::cout << "Index " << i << ": " << intArr.get(i) << "\n";
    }

    std::cout << "\n=== Testing pop() ===\n";
    int popped = intArr.pop();
    std::cout << "Popped: " << popped << "\n";

    std::cout << "\n=== Testing shift() ===\n";
    int shifted = intArr.shift();
    std::cout << "Shifted: " << shifted << "\n";

    std::cout << "\n=== Final Array State ===\n";
    for (int i = 0; i < intArr.size(); ++i) {
        std::cout << "Index " << i << ": " << intArr.get(i) << "\n";
    }

    return 0;
}
