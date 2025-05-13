#include <iostream>
#include <list>

int main() {
    int n;
    std::cin >> n;
    std::list<long long> businesses;
    long long ans = 0;

    for (int i = 0; i < n; ++i) {
        long long len;
        std::cin >> len;
        businesses.push_back(len);
        ans += len * len;
    }

    int k;
    std::cin >> k;
    int prev_updated = 0;
    auto cur = businesses.begin();
    std::cout << ans << '\n';
    for (int i = 0; i < k; ++i) {
        int e, v;
        std::cin >> e >> v;
        --v;
        int steps = v - prev_updated;
        cur = std::next(cur, steps);
        if (e == 1) {
            if (cur == businesses.begin()) {
                auto next = std::next(cur);
                ans -= (*cur) * (*cur) + (*next) * (*next);
                (*next) += (*cur);
                ans += (*next) * (*next);
            } else if (std::next(cur) == businesses.end()) {
                auto prev = std::prev(cur);
                ans -= (*cur) * (*cur) + (*prev) * (*prev);
                (*prev) += (*cur);
                ans += (*prev) * (*prev);
            } else {
                auto prev = std::prev(cur);
                auto next = std::next(cur);
                ans -= (*prev) * (*prev) + (*cur) * (*cur) + (*next) * (*next);
                (*prev) += (*cur) / 2;
                (*next) += (*cur) / 2 + (*cur) % 2;
                ans += (*prev) * (*prev) + (*next) * (*next);
            }
            cur = businesses.erase(cur);
        } else if (e == 2) {
            ans -= (*cur) * (*cur);
            cur = businesses.insert(cur, *cur);
            auto next = std::next(cur);
            (*cur) /= 2;
            (*next) = (*next) / 2 + (*next) % 2;
            ans += (*cur) * (*cur) + (*next) * (*next);
        }
        prev_updated = v;
        std::cout << ans << '\n';
    }

    return 0;
}
