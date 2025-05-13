#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    std::string name;
    int cost;
};

int main() {
    size_t n;
    int d;
    std::cin >> n >> d;
    std::vector<Item> items(n);
    int max_cost = 0;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> items[i].name >> items[i].cost;
        max_cost = std::max(max_cost, items[i].cost);
    }

    std::ranges::sort(items, [](const auto& lhs, const auto& rhs) {
        return lhs.cost < rhs.cost;
    });
    std::vector<int> knapsack(max_cost + 1, -1);
    knapsack[0] = 0;
    std::vector<std::string> refused_items;
    int days = 0;

    for (size_t i = 0; i < n; ++i) {
        int cost = -1;
        for (size_t j = std::max(0, items[i].cost - d); j < items[i].cost; ++j) {
            if (knapsack[j] != -1) {
                if (cost != -1) {
                    cost = std::min(cost, knapsack[j]);
                } else {
                    cost = knapsack[j];
                }
            }
        }
        if (cost == -1) {
            continue;
        }
        ++cost;
        days += cost;
        refused_items.push_back(items[i].name);
        for (size_t j = max_cost - items[i].cost; j >= 1; --j) {
            if (knapsack[j] != -1) {
                if (knapsack[j + items[i].cost] != -1) {
                    knapsack[j + items[i].cost] = std::min(knapsack[j + items[i].cost], knapsack[j] + cost);
                } else {
                    knapsack[j + items[i].cost] = knapsack[j] + cost;
                }
            }
        }
        if (knapsack[0] != -1) {
            if (knapsack[items[i].cost] != -1) {
                knapsack[items[i].cost] = std::min(knapsack[items[i].cost], knapsack[0] + cost);
            } else {
                knapsack[items[i].cost] = knapsack[0] + cost;
            }
        }
    }

    std::ranges::sort(refused_items);
    std::cout << refused_items.size() << ' ' << days << '\n';
    for (const auto& name : refused_items) {
        std::cout << name << '\n';
    }

    return 0;
}
