#include <iostream>
#include <vector>

struct Node {
    Node() = default;
    Node(long long sum, long long add) : sum(sum), add(add) {}

    long long sum = 0;
    long long add = 0;
};

class SegmentTree {
public:
    explicit SegmentTree(size_t n) {
        while (size_ < n) {
            size_ *= 2;
        }
        tree_.assign(2 * size_ - 1, {});
    }

    void Build(const std::vector<long long>& nums) {
        Build(nums, 0, 0, size_);
    }

    long long GetSum(size_t l, size_t r) const  {
        return GetSum(l, r, 0, 0, size_);
    }

    void Add(size_t l, size_t r, long long val) {
        Add(l, r, val, 0, 0, size_);
    }
private:
    void Build(const std::vector<long long>& nums, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            if (lx < nums.size()) {
                tree_[x].sum = nums[lx];
            }
        } else {
            const size_t mid = (lx + rx) / 2;
            const size_t left_child = LeftChild(x);
            const size_t right_child = RightChild(x);

            Build(nums, left_child, lx, mid);
            Build(nums, right_child, mid, rx);

            tree_[x].sum = tree_[left_child].sum + tree_[right_child].sum;
        }
    }

    long long GetSum(size_t l, size_t r, size_t x, size_t lx, size_t rx) const {
        if (lx >= r || rx <= l) {
            return 0;
        }
        if (lx >= l && rx <= r) {
            return tree_[x].sum;
        }

        const size_t mid = (lx + rx) / 2;
        const auto lhs = GetSum(l, r, LeftChild(x), lx, mid);
        const auto rhs = GetSum(l, r, RightChild(x), mid, rx);
        auto res = lhs + rhs;

        return res + tree_[x].add;
    }

    void Add(size_t l, size_t r, long long val, size_t x, size_t lx, size_t rx) {
        if (lx >= r || rx <= l) {
            return;
        }

        if (lx >= l && rx <= r) {
            tree_[x].add += val;
            tree_[x].sum += val;
            return;
        }
        const size_t mid = (lx + rx) / 2;
        Add(l, r, val, LeftChild(x), lx, mid);
        Add(l, r, val, RightChild(x), mid, rx);
        tree_[x].sum = tree_[LeftChild(x)].sum + tree_[RightChild(x)].sum + tree_[x].add;
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

    std::vector<long long> nums(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    SegmentTree tree(n);
    tree.Build(nums);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        char query_type;
        size_t l, r;
        std::cin >> query_type >> l;
        r = l;
        if (query_type == 'g') {
            std::cout << tree.GetSum(l - 1, r) << '\n';
        } else if (query_type == 'a') {
            long long val;
            std::cin >> r >> val;
            tree.Add(l - 1, r, val);
        }
    }
    return 0;
}
