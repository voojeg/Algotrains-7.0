#include <iostream>
#include <vector>

int main() {
    long long m;
    std::cin >> m;

    std::vector<int> powers(31);
    powers[0] = 1;
    for (size_t i = 1; i < 31; ++i) {
        powers[i] = powers[i - 1] * 2;
    }

    std::vector<long long> seconds(31);
    for (size_t i = 0; i < 31; ++i) {
        std::cin >> seconds[i];
        if (i > 0 && seconds[i - 1] * 2 > seconds[i]) {
            seconds[i] = seconds[i - 1] * 2;
        }
    }

    long long total_price = 0;
    for (size_t i = 30; i < 31; --i) {
        if (m >= seconds[i]) {
            m -= seconds[i];
            total_price += powers[i];
        }
    }

    if (m > 0) {
        ++total_price;
    }

    std::cout << total_price << '\n';

    return 0;
}
