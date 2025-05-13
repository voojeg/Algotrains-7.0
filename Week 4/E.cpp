#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n), left(n), right(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
        left[i] = (i - 1 + n) % n;
        right[i] = (i + 1) % n;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (nums[i] < nums[left[i]] && nums[i] < nums[right[i]]) {
            q.push(i);
        }
    }

    std::vector<bool> out(n, false);
    std::vector<int> ans(n, 0);
    int step = 1;
    int contestants = n;

    while (!q.empty() && contestants > 2) {
        std::vector<int> tmp;
        int size = q.size();

        for (int i = 0; i < size; ++i) {
            int cur = q.front();
            q.pop();
            if (out[cur]) continue;
            out[cur] = true;
            ans[cur] = step;
            --contestants;

            int l = left[cur];
            int r = right[cur];
            if (!out[l]) {
                right[l] = r;
            }
            if (!out[r]) {
                left[r] = l;
            }

            if (!out[l] && ans[l] == 0) {
                if (nums[l] < nums[left[l]] && nums[l] < nums[right[l]]) {
                    tmp.push_back(l);
                }
            }

            if (!out[r] && ans[r] == 0) {
                if (nums[r] < nums[left[r]] && nums[r] < nums[right[r]]) {
                    tmp.push_back(r);
                }
            }
        }

        if (tmp.empty()) break;

        for (int i : tmp) {
            q.push(i);
        }
        ++step;
    }

    for (int i : ans) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}
