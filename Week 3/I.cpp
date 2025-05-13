#include <iostream>
#include <vector>

size_t GetCodingBits(size_t n) {
    size_t res = 0;
    while ((1 << res) < n + res + 1) {
        ++res;
    }
    return res;
}

bool IsPowerOfTwo(size_t n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

std::vector<int> Encode(const std::vector<int>& input) {
    const auto coding_bits = GetCodingBits(input.size());
    const auto len = input.size() + coding_bits;
    std::vector<int> encoded(len, 0);
    size_t r = 0;

    for (size_t l = 0; l < len; ++l) {
        if (!IsPowerOfTwo(l + 1)) {
            encoded[l] = input[r];
            ++r;
        }
    }

    for (size_t i = 0; i < coding_bits; ++i) {
        int parity = 0;
        for (size_t j = ((1 << i) - 1); j < len; ++j) {
            if (((j + 1) & (1 << i)) != 0) {
                parity ^= encoded[j];
            }
        }
        encoded[(1 << i) - 1] = parity;
    }

    return encoded;
}

std::vector<int> Decode(std::vector<int> input) {
    const auto coding_bits = GetCodingBits(input.size());
    const auto len = input.size();
    size_t error_pos = 0;

    for (size_t i = 0; i < coding_bits; ++i) {
        int parity = 0;
        for (size_t j = 0; j < len; ++j) {
            if (((j + 1) & (1 << i)) != 0) {
                parity ^= input[j];
            }
        }
        if (parity) {
            error_pos += (1 << i);
        }
    }

    if (error_pos) {
        input[error_pos - 1] ^= 1;
    }
    std::vector<int> str;
    for (size_t i = 0; i < len; ++i) {
        if (!IsPowerOfTwo(i + 1)) {
            str.push_back(input[i]);
        }
    }

    return str;
}

std::vector<int> ConvertString(const std::string& s) {
    std::vector<int> res;
    for (auto c : s) {
        res.push_back(c - '0');
    }
    return res;
}

int main() {
    int code;
    std::cin >> code;
    if (code == 1) {
        std::string str;
        std::cin >> str;
        std::vector<int> input = ConvertString(str);

        const auto encoded = Encode(input);
        for (auto c : encoded) {
            std::cout << c;
        }

    } else if (code == 2) {
        std::string str;
        std::cin >> str;
        std::vector<int> input = ConvertString(str);

        const auto decoded = Decode(input);
        for (auto c : decoded) {
            std::cout << c;
        }
    }
    return 0;
}
