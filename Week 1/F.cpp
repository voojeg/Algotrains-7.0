#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    size_t n, m;
    std::cin >> n >> m;
    std::vector<int> weights(n), prices(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    for (size_t i = 0; i < n; ++i) {
        std::cin >> prices[i];
    }

    std::vector<std::vector<int>> knapsack(n + 1, std::vector<int>(m + 1, 0)); // stores max value
    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t w = 1; w < m + 1; ++w) {
            knapsack[i][w] = knapsack[i - 1][w];
            if (weights[i - 1] <= w) {
                knapsack[i][w] = std::max(knapsack[i][w], knapsack[i - 1][w - weights[i - 1]] + prices[i - 1]);
            }
        }
    }

    size_t i = n;
    size_t j = m;
    std::vector<size_t> used;
    while (i > 0) {
        if (knapsack[i][j] != knapsack[i - 1][j]) {
            j -= weights[i - 1];
            used.push_back(i);
        }
        --i;
    }

    std::ranges::reverse(used);
    for (auto u : used) {
        std::cout << u << '\n';
    }

    return 0;
}
