#include <iostream>

int GetLen(int n) {
    int len = 0;
    while (n) {
        ++len;
        n >>= 1;
    }
    return len;
}

int GetMaxWithShifts(int n) {
    int max_num = n;
    const int n_len = GetLen(n);
    for (int i = 0; i < n_len; ++i) {
        bool extra_bit = n & 1;
        n >>= 1;
        if (extra_bit) {
            n |= (1 << (n_len - 1));
        }
        max_num = std::max(max_num, n);
    }
    return max_num;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << GetMaxWithShifts(n) << '\n';
    return 0;
}
