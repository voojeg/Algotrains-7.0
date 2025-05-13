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

    std::vector<int> knapsack(m + 1, -1);
    knapsack[0] = 0;
    int max_price = 0;
    for (size_t i = 0; i < n; ++i) {
        if (m >= weights[i]) {
            for (size_t j = m - weights[i]; j > 0; --j) {
                if (knapsack[j] != -1) {
                    knapsack[j + weights[i]] = std::max(knapsack[j] + prices[i], knapsack[j + weights[i]]);
                    max_price = std::max(max_price, knapsack[j + weights[i]]);
                }
            }
            if (knapsack[0] != -1) {
                knapsack[weights[i]] = std::max(knapsack[0] + prices[i], knapsack[weights[i]]);
                max_price = std::max(max_price, knapsack[weights[i]]);
            }
        }
    }

    std::cout << max_price << '\n';

    return 0;
}
