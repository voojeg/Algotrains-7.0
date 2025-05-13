#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> groups(n);
    std::vector<std::pair<int, int>> rooms(m);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> groups[i].first;
        groups[i].second = i;
    }
    for (size_t i = 0; i < m; ++i) {
        std::cin >> rooms[i].first;
        rooms[i].second = i + 1;
    }

    std::ranges::sort(groups);
    std::ranges::sort(rooms);
    std::vector<int> assignments(n, 0);

    int ans = 0;
    for (size_t i = 0, j = 0; i < n && j < m; ++j) {
        if (groups[i].first < rooms[j].first) {
            assignments[groups[i].second] = rooms[j].second;
            ++i;
            ++ans;
        }
    }

    std::cout << ans << std::endl;
    for (const auto& assignment : assignments) {
        std::cout << assignment << " ";
    }
    return 0;
}
