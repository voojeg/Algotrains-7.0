#include <iostream>
#include <vector>

class FenwickTree {
public:
    FenwickTree() = delete;

    explicit FenwickTree(size_t n) : size_(n) {
        tree_.assign(size_, std::vector<std::vector<long long>>(size_, std::vector<long long>(size_, 0)));
    }

    void Update(size_t x, size_t y, size_t z, long long val) {
        for (size_t i = x; i < size_; i |= (i + 1)) {
            for (size_t j = y; j < size_; j |= (j + 1)) {
                for (size_t k = z; k < size_; k |= (k + 1)) {
                    tree_[i][j][k] += val;
                }
            }
        }
    }

    long long Sum(size_t x, size_t y, size_t z) const {
        long long result = 0;
        for (size_t i = x; i < x + 1; i = (i & (i + 1)) - 1) {
            for (size_t j = y; j < y + 1; j = (j & (j + 1)) - 1) {
                for (size_t k = z; k < z + 1; k = (k & (k + 1)) - 1) {
                    result += tree_[i][j][k];
                }
            }
        }
        return result;
    }

    long long Sum(size_t x1, size_t y1, size_t z1, size_t x2, size_t y2, size_t z2) const {
        return
            Sum(x2, y2, z2) -
            Sum(x1 - 1, y2, z2) -
            Sum(x2, y1 - 1, z2) -
            Sum(x2, y2, z1 - 1) +
            Sum(x2, y1 - 1, z1 - 1) +
            Sum(x1 - 1, y2, z1 - 1) +
            Sum(x1 - 1, y1 - 1, z2) -
            Sum(x1 - 1, y1 - 1, z1 - 1);
    }
private:
    size_t size_;
    std::vector<std::vector<std::vector<long long>>> tree_;
};

int main() {
    size_t n;
    std::cin >> n;
    FenwickTree tree(n);

    int query_type;
    while (std::cin >> query_type && query_type != 3) {
        if (query_type == 1) {
            size_t x, y, z;
            int k;
            std::cin >> x >> y >> z >> k;
            tree.Update(x, y, z, k);
        } else if (query_type == 2) {
            size_t x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            std::cout << tree.Sum(x1, y1, z1, x2, y2, z2) << '\n';
        }
    }

    return 0;
}
