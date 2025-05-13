#include <iostream>
#include <vector>

struct Node {
    Node() :
        pref(0),
        suf(0),
        max(0),
        len(0) {}

    explicit Node (long long num) :
        pref(num == 0), suf(num == 0), max(num == 0), len(1) {}

    Node(long long pref, long long suf, long long max, long long len) :
        pref(pref),
        suf(suf),
        max(max),
        len(len) {}

    long long pref, suf, max, len;
};

class SegmentTree {
public:
    explicit SegmentTree(size_t n) {
        while (size_ < n) {
            size_ *= 2;
        }
        tree_.resize(2 * size_ - 1);
    }

    void Build(const std::vector<int>& nums) {
        Build(nums, 0, 0, size_);
    }

    Node Get(size_t l, size_t r) const  {
        return Get(l, r, 0, 0, size_);
    }

    void Set(size_t i, long long val) {
        Set(i, val, 0, 0, size_);
    }
private:
    void Build(const std::vector<int>& nums, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            if (lx < nums.size()) {
                tree_[x] = Node(nums[lx]);
            }
        } else {
            const size_t mid = (lx + rx) / 2;
            const size_t left_child = LeftChild(x);
            const size_t right_child = RightChild(x);

            Build(nums, left_child, lx, mid);
            Build(nums, right_child, mid, rx);

            tree_[x] = Combine(tree_[left_child], tree_[right_child]);
        }
    }

    Node Get(size_t l, size_t r, size_t x, size_t lx, size_t rx) const {
        if (lx >= r || rx <= l) {
            return {-1, 0, 0, 0};
        }
        if (lx >= l && rx <= r) {
            return tree_[x];
        }

        const size_t mid = (lx + rx) / 2;
        const size_t left_child = LeftChild(x);
        const size_t right_child = RightChild(x);

        const auto lhs = Get(l, r, left_child, lx, mid);
        const auto rhs = Get(l, r, right_child, mid, rx);

        return Combine(lhs, rhs);
    }

    void Set(size_t i, long long num, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            tree_[x] = Node(num);
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

        tree_[x] = Combine(tree_[left_child], tree_[right_child]);
    }

    size_t LeftChild(size_t i) const {
        return 2 * i + 1;
    }

    size_t RightChild(size_t i) const {
        return 2 * i + 2;
    }

    Node Combine(const Node& lhs, const Node& rhs) const {
        if (lhs.pref == -1) {
            return rhs;
        }
        if (rhs.pref == -1) {
            return lhs;
        }
        Node res = {
            std::max(lhs.pref, (lhs.pref + rhs.pref) * (lhs.pref == lhs.len)),
            std::max(rhs.suf, (lhs.suf + rhs.suf) * (rhs.suf == rhs.len)),
            0,
            lhs.len + rhs.len
        };
        res.max = std::max(std::max(res.pref, res.suf), std::max(std::max(lhs.suf + rhs.pref, lhs.max), rhs.max));
        return res;
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

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "UPDATE") {
            size_t i;
            long long x;
            std::cin >> i >> x;
            tree.Set(i - 1, x);
        } else if (cmd == "QUERY") {
            size_t l, r;
            std::cin >> l >> r;
            std::cout << tree.Get(l - 1, r).max << '\n';
        }
    }
    return 0;
}
