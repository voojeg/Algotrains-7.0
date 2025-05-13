#include <iostream>
#include <vector>

class SegmentTree {
public:
    explicit SegmentTree(size_t n) {
        while (size_ < n) {
            size_ *= 2;
        }
        tree_.assign(2 * size_ - 1, 0);
    }

    long long Get(size_t l, size_t r) const  { // [l, r)
        return Get(l, r, 0, 0, size_);
    }

    void Set(size_t i, long long val) {
        Set(i, val, 0, 0, size_);
    }

private:
    long long Get(size_t l, size_t r, size_t x, size_t lx, size_t rx) const {
        if (lx >= r || rx <= l) {
            return 0;
        }
        if (lx >= l && rx <= r) {
            return tree_[x];
        }

        const size_t mid = (lx + rx) / 2;
        const auto lhs = Get(l, r, LeftChild(x), lx, mid);
        const auto rhs = Get(l, r, RightChild(x), mid, rx);

        return lhs + rhs;
    }

    void Set(size_t i, long long num, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            tree_[x] = num;
            return;
        }

        const size_t mid = (lx + rx) / 2;
        const size_t left_child = LeftChild(x);
        const size_t right_child = RightChild(x);

        if (i < mid) {
            Set(i, num, left_child, lx, mid);
        } else {
            Set(i, num, right_child, mid, rx);
        }

        tree_[x] = tree_[left_child] + tree_[right_child];
    }

    size_t LeftChild(size_t i) const {
        return 2 * i + 1;
    }

    size_t RightChild(size_t i) const {
        return 2 * i + 2;
    }

    size_t size_ = 1;
    std::vector<long long> tree_;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    int k;
    std::cin >> n >> k;
    SegmentTree tree(n);

    for (int i = 0; i < k; ++i) {
        char query_type;
        std::cin >> query_type;
        if (query_type == 'Q') {
            size_t l, r;
            std::cin >> l >> r;
            std::cout << tree.Get(l - 1, r) << '\n';
        } else if (query_type == 'A') {
            size_t pos;
            long long num;
            std::cin >> pos >> num;
            tree.Set(pos - 1, num);
        }
    }

    return 0;
}
