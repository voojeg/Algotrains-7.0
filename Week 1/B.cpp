#include <iostream>
#include <vector>

std::vector<int> Split(const std::vector<int>& nums) {
    std::vector<int> ans;
    const size_t n = nums.size();
    size_t max_len = n;
    int len = 0;
    for (size_t i = 0; i < n; ++i) {
        max_len = std::min(max_len, static_cast<size_t>(nums[i]));
        ++len;
        if (len > max_len) {
            ans.push_back(len - 1);
            len = 1;
        }
        if (len == max_len) {
            ans.push_back(len);
            len = 0;
            max_len = n;
        }
    }
    if (len != 0) {
        ans.push_back(len);
    }
    return ans;
}

int main() {
    int t;
    std::cin >> t;
    while (t > 0) {
        size_t n;
        std::cin >> n;
        std::vector<int> nums(n);
        for (size_t i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }

        const auto segments = Split(nums);
        std::cout << segments.size() << std::endl;
        for (auto i : segments) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        --t;
    }
    return 0;
}
