#include <iostream>
#include <vector>
#include <algorithm>

long long CountMaxOrders(const std::vector<std::string>& input) {
    std::vector<std::pair<long long, long long>> odds;
    long long even_extra1 = 0;
    long long even_extra2 = 0;

    for (const auto& str : input) {
        long long even = 0;
        long long odd = 0;
        for (size_t i = 0; i < str.size(); ++i) {
            if (i % 2 == 0 && str[i] == 'S') ++even;
            else if (i % 2 == 1 && str[i] == 'S') ++odd;
        }
        if (str.size() % 2 == 0) {
            even_extra1 += even;
            even_extra2 += std::max(even, odd);
        } else {
            odds.emplace_back(even, odd);
        }
    }

    long long ans = 0;
    if (!odds.empty()) {
        ans = even_extra2;
    } else {
        ans = even_extra1;
    }

    std::ranges::sort(odds, [](const auto& lhs, const auto& rhs) {
        return lhs.first - lhs.second > rhs.first - rhs.second;
    });

    if (!odds.empty()) {
        const size_t n = odds.size();
        for (size_t i = 0; i <= (n - 1) / 2; ++i) {
            ans += odds[i].first;
        }
        for (size_t i = (n - 1) / 2 + 1; i < n; ++i) {
            ans += odds[i].second;
        }
    }

    return ans;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::string> input(n);

    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> input[i];
    }

    const auto ans = CountMaxOrders(input);
    std::cout << ans << '\n';

    return 0;
}
