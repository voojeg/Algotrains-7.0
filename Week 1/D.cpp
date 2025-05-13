#include <iostream>
#include <vector>

int main() {
    size_t n, m;

    std::cin >> n >> m;
    std::vector<int> weights(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }

    std::vector<bool> knapsack(m + 1, false);
    knapsack[0] = true;
    int max_weight = 0;
    for (int weight : weights) {
        for (size_t i = m - weight; i < weight - m; --i) {
            if (knapsack[i]) {
                knapsack[i + weight] = true;
                max_weight = std::max(max_weight, static_cast<int>(i) + weight);
            }
        }
    }

    std::cout << max_weight << '\n';

    return 0;
}
