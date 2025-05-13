#include <iostream>

int CountOnes(unsigned long long n) {
    int ones = 0;
    while (n) {
        n &= (n - 1ull);
        ++ones;
    }
    return ones;
}

int main() {
    unsigned long long n;
    std::cin >> n;
    std::cout << std::popcount(n) << '\n';
    // std::cout << CountOnes(n) << '\n';
    return 0;
}
