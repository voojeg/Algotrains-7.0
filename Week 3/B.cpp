#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int num;
            std::cin >> num;
            nums[i] |= num;
        }
    }
    for (auto num : nums) {
        std::cout << num << " ";
    }
    return 0;
}
