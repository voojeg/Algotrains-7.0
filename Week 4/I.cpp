#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::pair<long long, int>> snowmen(n + 1, {0, 0});
    long long ans = 0;

    for (size_t i = 1; i <= n; ++i) {
        int t, m;
        std::cin >> t >> m;
        if (m == 0) {
            snowmen[i] = snowmen[snowmen[t].second];
        } else {
            snowmen[i] = {snowmen[t].first + static_cast<long long>(m), t};
        }
        ans += snowmen[i].first;
    }

    std::cout << ans << '\n';
    return 0;
}
