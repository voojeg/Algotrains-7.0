#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>

struct Order {
    int volume;
    int cost;
    int pressure;
    size_t index;
};

int main() {
    size_t n;
    int s;
    std::cin >> n >> s;
    int total_volume = 0;
    std::vector<Order> orders(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> orders[i].volume >> orders[i].cost >> orders[i].pressure;
        orders[i].index = i;
        total_volume += orders[i].volume;
    }

    std::ranges::sort(orders, [](const auto& lhs, const auto& rhs) {
        const double lhs_d = static_cast<double>(lhs.cost) / lhs.volume;
        const double rhs_d = static_cast<double>(rhs.cost) / rhs.volume;
        if (std::abs(lhs_d - rhs_d) < 1e-9) {
            return lhs.pressure > rhs.pressure;
        }
        return lhs_d > rhs_d;
    });

    std::vector<long long> knapsack(total_volume + 1, -1);
    knapsack[0] = 0;
    std::vector<int> prev_vol(total_volume + 1, -1), prev_order(total_volume + 1, -1), min_pressure(total_volume + 1, INT_MAX);

    for (size_t j = 0; j < n; ++j) {
        int v = orders[j].volume;
        int c = orders[j].cost;
        int p = orders[j].pressure;
        for (int i = total_volume; i >= v; --i) {
            if (knapsack[i - v] == -1) continue;

            long long new_cost = knapsack[i - v] + c;
            long long new_pressure = std::min(p, min_pressure[i - v]);
            long long pressure = std::max(0ll, static_cast<long long>(i) - s);

            if (pressure <= new_pressure && new_cost > knapsack[i]) {
                knapsack[i] = new_cost;
                min_pressure[i] = new_pressure;
                prev_vol[i] = i - v;
                prev_order[i] = j;
            }
        }
    }

    long long best_cost = -1;
    long long best_volume = -1;
    for (int v = 0; v <= total_volume; ++v) {
        if (knapsack[v] != -1) {
            long long pressure = std::max(0LL, static_cast<long long>(v) - s);
            if (pressure <= min_pressure[v] && knapsack[v] > best_cost) {
                best_cost = knapsack[v];
                best_volume = v;
            }
        }
    }

    std::vector<int> ans;
    long long i = best_volume;
    while (i > 0 && prev_order[i] != -1) {
        auto idx = prev_order[i];
        ans.push_back(orders[idx].index);
        i = prev_vol[i];
    }

    std::cout << ans.size() << ' ';
    if (ans.empty()) {
        std::cout << 0 << '\n';
    } else {
        std::cout << best_cost << '\n';
        for (int idx : ans) {
            std::cout << idx + 1 << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
