#include <climits>
#include <iostream>
#include <vector>

class SegmentTree {
public:
    explicit SegmentTree(size_t n) {
        while (size_ < n) {
            size_ *= 2;
        }
        tree_.assign(2 * size_ - 1, INT_MIN);
    }

    void Build(const std::vector<int>& nums) {
        Build(nums, 0, 0, size_);
    }

    int Get(size_t l, size_t r) const  { // [l, r)
        return Get(l, r, 0, 0, size_);
    }

    void Set(size_t i, int val) {
        Set(i, val, 0, 0, size_);
    }
private:
    void Build(const std::vector<int>& nums, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            if (lx < nums.size()) {
                tree_[x] = nums[lx];
            }
        } else {
            const size_t mid = (lx + rx) / 2;
            const size_t left_child = LeftChild(x);
            const size_t right_child = RightChild(x);

            Build(nums, left_child, lx, mid);
            Build(nums, right_child, mid, rx);

            tree_[x] = std::max(tree_[left_child], tree_[right_child]);
        }
    }

    int Get(size_t l, size_t r, size_t x, size_t lx, size_t rx) const {
        if (lx >= r || rx <= l) {
            return INT_MIN;
        }
        if (lx >= l && rx <= r) {
            return tree_[x];
        }

        const size_t mid = (lx + rx) / 2;
        const auto lhs = Get(l, r, LeftChild(x), lx, mid);
        const auto rhs = Get(l, r, RightChild(x), mid, rx);

        return std::max(lhs, rhs);
    }

    void Set(size_t i, int num, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            tree_[x] = num;
            return;
        }

        const size_t mid = (lx + rx) / 2;
        if (i < mid) {
            Set(i, num, LeftChild(x), lx, mid);
        } else {
            Set(i, num, RightChild(x), mid, rx);
        }

        tree_[x] = std::max(tree_[LeftChild(x)], tree_[RightChild(x)]);
    }

    size_t LeftChild(size_t i) const {
        return 2 * i + 1;
    }

    size_t RightChild(size_t i) const {
        return 2 * i + 2;
    }

    size_t size_ = 1;
    std::vector<int> tree_;
};

int main() {
    size_t n;
    std::cin >> n;

    std::vector<int> nums(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    SegmentTree tree(n);
    tree.Build(nums);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        char query_type;
        std::cin >> query_type;
        if (query_type == 's') {
            size_t l, r;
            std::cin >> l >> r;
            std::cout << tree.Get(l - 1, r) << ' ';
        } else if (query_type == 'u') {
            size_t i;
            int num;
            std::cin >> i >> num;
            tree.Set(i - 1, num);
        }
    }
    return 0;
}
