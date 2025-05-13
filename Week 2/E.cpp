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

    void Build(const std::vector<int>& nums) {
        Build(nums, 0, 0, size_);
    }

    int Sum(size_t l, size_t r) const {
        return Sum(l, r, 0, 0, size_);
    }

    int Get(size_t l, size_t r, int k) const  {
        return Get(l, r, k, 0, 0, size_);
    }

    void Set(size_t i, int val) {
        Set(i, val, 0, 0, size_);
    }

    void Print() const {
        std::cerr << tree_.size() << std::endl;
        for (const auto& i : tree_) {
            std::cerr << i << std::endl;
        }
        std::cerr << std::endl;
    }
private:
    void Build(const std::vector<int>& nums, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            if (lx < nums.size()) {
                tree_[x] = nums[lx] == 0;
            }
        } else {
            const size_t mid = (lx + rx) / 2;
            const size_t left_child = LeftChild(x);
            const size_t right_child = RightChild(x);

            Build(nums, left_child, lx, mid);
            Build(nums, right_child, mid, rx);

            tree_[x] = tree_[left_child] + tree_[right_child];
        }
    }

    int Sum(size_t l, size_t r, size_t x, size_t lx, size_t rx) const {
        if (lx >= r || rx <= l) {
            return 0;
        }
        if (lx >= l && rx <= r) {
            return tree_[x];
        }

        const size_t mid = (lx + rx) / 2;
        const auto lhs = Sum(l, r, LeftChild(x), lx, mid);
        const auto rhs = Sum(l, r, RightChild(x), mid, rx);

        return lhs + rhs;
    }

    int Get(size_t l, size_t r, int k, size_t x, size_t lx, size_t rx) const {
        if (rx == lx + 1) {
            if (k != tree_[x]) {
                return -2;
            }
            return lx;
        }

        const size_t mid = (lx + rx) / 2;
        if (k <= tree_[LeftChild(x)]) {
            return Get(l, r, k, LeftChild(x), lx, mid);
        }
        return Get(l, r, k - tree_[LeftChild(x)], RightChild(x), mid, rx);
    }

    void Set(size_t i, int num, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            tree_[x] = num == 0;
            return;
        }

        const size_t mid = (lx + rx) / 2;
        if (i < mid) {
            Set(i, num, LeftChild(x), lx, mid);
        } else {
            Set(i, num, RightChild(x), mid, rx);
        }

        tree_[x] = tree_[LeftChild(x)] + tree_[RightChild(x)];
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
            int k;
            std::cin >> l >> r >> k;
            auto prev_zeros = tree.Sum(0, l - 1);
            auto ans = tree.Get(0, n, prev_zeros + k) + 1;
            if (ans > r) {
                ans = -1;
            }
            std::cout << ans << ' ';
        } else if (query_type == 'u') {
            size_t pos;
            int num;
            std::cin >> pos >> num;
            tree.Set(pos - 1, num);
        }
    }
    return 0;
}
