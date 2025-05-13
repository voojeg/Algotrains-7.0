#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::bitset<64>> nums(n);
    std::vector<unsigned long long> nums_init(n);

    unsigned long long max = 0ull;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> nums_init[i];
        max = std::max(max, nums_init[i]);
        nums[i] = std::bitset<64>(nums_init[i]);
    }

    std::bitset<64> xor_all = std::accumulate(
        nums.begin(),
        nums.end(),
        std::bitset<64>(0),
        std::bit_xor<>()
    );

    for (size_t j = 63; j < 64; --j) {
        if (xor_all.test(j)) {
            bool flag = true;
            for (int i = 0; i < n && flag; ++i) {
                for (size_t k = j; k < j + 1 && flag; --k) {
                    if (nums[i][j] ^ nums[i][k]) {
                        nums[i][j].flip();
                        nums[i][k].flip();
                        flag = false;
                    }
                }
            }
            xor_all = std::accumulate(
                nums.begin(),
                nums.end(),
                std::bitset<64>(0),
                std::bit_xor<>()
            );
        }
    }

    xor_all = std::accumulate(
        nums.begin(),
        nums.end(),
        std::bitset<64>(0),
        std::bit_xor<>()
    );

    if (xor_all.count()) {
        std::cout << "impossible\n";
    } else {
        for (size_t i = 0; i < n; ++i) {
            std::cout << nums[i].to_ullong() << ' ';
        }
    }

    return 0;
}
