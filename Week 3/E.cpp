#include <iostream>

int main() {
    long long x1, y, x2, c;
    std::cin >> x1 >> y >> x2 >> c;
    std::cout << (x1 ^ y) << '\n';
    std::cout << (x2 ^ c) << '\n';
    return 0;
}
