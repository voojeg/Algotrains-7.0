#include <iostream>
#include <vector>

int main() {
    size_t n;
    int k;
    std::cin >> n >> k;
    std::vector<std::pair<int, int>> items(n);
    int max_length = 0;

    for (size_t i = 0; i < n; ++i) {
        int l, c;
        std::cin >> l >> c;
        items[i] = std::make_pair(l, c);
        if (c == 1) {
            max_length += l;
        }
    }

    std::vector<std::vector<int>> knapsack(k + 1, std::vector<int>(max_length + 1, -1));
    for (size_t i = 0; i < k + 1; ++i) {
        knapsack[i][0] = 0;
    }

    for (int i = 0; i < n; ++i) {
        const auto item_length = items[i].first;
        const auto color = items[i].second;
        for (size_t length = max_length - item_length; length < max_length - item_length + 1; --length) {
            if (knapsack[color][item_length + length] == -1 && knapsack[color][length] != -1) {
                knapsack[color][item_length + length] = i + 1;
            }
        }
    }

    std::vector<size_t> ans;
    for (size_t length = 1; length < max_length; ++length) {
        bool flag = true;
        for (size_t color = 1; color < k + 1; ++color) {
            if (knapsack[color][length] == -1) {
                flag = false;
            }
        }
        if (flag) {
            std::cout << "YES\n";
            for (size_t color = 1; color < k + 1; ++color) {
                auto cur_length = length;
                while (cur_length != 0) {
                    ans.push_back(knapsack[color][cur_length]);
                    cur_length -= items[knapsack[color][cur_length] - 1].first;
                }
            }
            for (auto i : ans) {
                std::cout << i << ' ';
            }
            return 0;
        }
    }

    std::cout << "NO\n";
    return 0;
}
