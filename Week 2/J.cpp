#include <climits>
#include <iostream>
#include <vector>

class SegmentTree {
private:
    static const long long NO_OPERATION = LLONG_MIN;
    static const long long NEUTRAL_ELEMENT = 0;

    struct Node {
        Node() : hash(0), len(0) {}
        Node(long long hash, long long len) : hash(hash), len(len) {}

        long long hash = NEUTRAL_ELEMENT;
        long long len = 1;
    };

public:
    explicit SegmentTree(size_t n) {
        while (size_ < n) {
            size_ *= 2;
        }
        tree_.resize(2 * size_ - 1);
        // Build(nums, 0, 0, size_);
        x_pows_.resize(n + 1);
        x_pows_[0] = 1;
        for (size_t i = 1; i <= n; ++i) {
            x_pows_[i] = ((x_pows_[i - 1] % mod) * (x % mod)) % mod;
        }
    }

    void Build(const std::vector<long long>& nums) {
        Build(nums, 0, 0, size_);
    }

    Node GetHash(size_t l, size_t r)  {
        return GetHash(l, r, 0, 0, size_);
    }

    void Set(size_t i, long long val) {
        Set(i, val, 0, 0, size_);
    }

    void Print() const {
        std::cerr << tree_.size() << std::endl;
        for (const auto& i : tree_) {
            std::cerr << i.hash << " " << i.len << std::endl;
        }
    }
private:
    void Build(const std::vector<long long>& nums, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            if (lx < nums.size()) {
                tree_[x].hash = nums[lx] % mod;
            }
            return;
        }
        const size_t mid = (lx + rx) / 2;
        const size_t left_child = LeftChild(x);
        const size_t right_child = RightChild(x);

        Build(nums, left_child, lx, mid);
        Build(nums, right_child, mid, rx);

        tree_[x] = CombineNodes(tree_[left_child], tree_[right_child]);
    }

    Node GetHash(size_t l, size_t r, size_t x, size_t lx, size_t rx) {
        if (lx >= r || rx <= l) {
            return {};
        }
        if (lx >= l && rx <= r) {
            return tree_[x];
        }

        const size_t mid = (lx + rx) / 2;
        const size_t left_child = LeftChild(x);
        const size_t right_child = RightChild(x);

        const auto lhs = GetHash(l, r, left_child, lx, mid);
        const auto rhs = GetHash(l, r, right_child, mid, rx);

        return CombineNodes(lhs, rhs);
    }

    void Set(size_t i, long long val, size_t x, size_t lx, size_t rx) {
        if (rx == lx + 1) {
            tree_[x].hash = val % mod;
            return;
        }
        const size_t mid = (lx + rx) / 2;
        const size_t left_child = LeftChild(x);
        const size_t right_child = RightChild(x);

        if (i < mid) {
            Set(i, val, left_child, lx, mid);
        } else {
            Set(i, val, right_child, mid, rx);
        }

        tree_[x] = CombineNodes(tree_[left_child], tree_[right_child]);

    }

    Node CombineNodes(const Node& lhs, const Node& rhs) {
        return {((lhs.hash % mod) * (x_pows_[rhs.len] % mod) + rhs.hash) % mod, lhs.len + rhs.len};
    }

    size_t LeftChild(size_t i) const {
        return 2 * i + 1;
    }

    size_t RightChild(size_t i) const {
        return 2 * i + 2;
    }

    size_t size_ = 1;
    std::vector<Node> tree_;

    const long long x = 100'747;
    const long long mod = 1e9 + 7;

    std::vector<long long> x_pows_;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<long long> nums(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    SegmentTree tree(n);
    tree.Build(nums);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int query_type;
        size_t l, r;
        long long k;

        std::cin >> query_type >> l >> r >> k;
        if (query_type == 0) {
            while (l <= r) {
                tree.Set(l - 1, k);
                nums[l - 1] = k;
                ++l;
            }

        } else if (query_type == 1) {
            char res = '+';
            if (l > r) {
                res = '-';
            } else {
                const auto lhs = tree.GetHash(l - 1, l + k - 1);
                const auto rhs = tree.GetHash(r - 1, r + k - 1);
                if ((lhs.hash) != (rhs.hash)) {
                    res = '-';
                }
            }
            std::cout << res;
        }
    }
    return 0;
}
