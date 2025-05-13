#include <climits>
#include <iostream>
#include <vector>

struct Node {
    Node() = default;
    Node(int max, size_t max_index) : max(max), max_index(max_index) {}

    int max = INT_MIN;
    size_t max_index = INT_MAX;
};

class SegmentTree {
public:
    explicit SegmentTree(size_t n) {
        while (size_ < n) {
            size_ *= 2;
        }
        tree_.assign(2 * size_ - 1, {});
    }

    void Build(const std::vector<int>& nums) {
        Build(nums, 0, 0, size_);
    }

    Node Get(size_t l, size_t r) const  { // [l, r)
        return Get(l, r, 0, 0, size_);
    }

private:
    void Build(const std::vector<int>& nums, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            if (lx < nums.size()) {
                tree_[x] = {nums[lx], lx};
            }
        } else {
            const size_t mid = (lx + rx) / 2;
            const size_t left_child = LeftChild(x);
            const size_t right_child = RightChild(x);

            Build(nums, left_child, lx, mid);
            Build(nums, right_child, mid, rx);

            if (tree_[left_child].max > tree_[right_child].max) {
                tree_[x] = tree_[left_child];
            } else {
                tree_[x] = tree_[right_child];
            }
        }
    }

    Node Get(size_t l, size_t r, size_t x, size_t lx, size_t rx) const {
        if (lx >= r || rx <= l) {
            return {};
        }
        if (lx >= l && rx <= r) {
            return tree_[x];
        }
        const size_t mid = (lx + rx) / 2;
        const auto lhs = Get(l, r, LeftChild(x), lx, mid);
        const auto rhs = Get(l, r, RightChild(x), mid, rx);

        if (lhs.max > rhs.max) {
            return lhs;
        }
        return rhs;
    }

    size_t LeftChild(size_t i) const {
        return 2 * i + 1;
    }

    size_t RightChild(size_t i) const {
        return 2 * i + 2;
    }

    size_t size_ = 1;
    std::vector<Node> tree_;
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

    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        size_t l, r;
        std::cin >> l >> r;
        auto [max, max_ind] = tree.Get(l - 1, r);
        std::cout << max << " " << max_ind + 1 << '\n';
    }
    return 0;
}
