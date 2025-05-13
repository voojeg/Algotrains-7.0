#include <algorithm>
#include <iostream>
#include <vector>

class DisjointSet {
public:
    DisjointSet() = delete;

    explicit DisjointSet(size_t n) {
        data_.resize(n);
        for (size_t i = 0; i != n; ++i) {
            data_[i] = {i, 0};
        }
    }

    size_t Find(size_t i) {
        if (i != data_[i].parent) {
            data_[i].parent = Find(data_[i].parent);
        }
        return data_[i].parent;
    }

    void Union(size_t i, size_t j) {
        i = Find(i);
        j = Find(j);
        if (i == j) {
            return;
        }
        if (data_[i].rank == data_[j].rank) {
            ++data_[i].rank;
        }
        if (data_[i].rank > data_[j].rank) {
            data_[j].parent = i;
        } else {
            data_[i].parent = j;
        }
    }
private:
    struct Node {
        size_t parent;
        int rank;
    };

    std::vector<Node> data_;
};

enum class query_type {
    ask,
    cut
};

struct Query {
    query_type type;
    size_t x, y;
};

int main() {
    size_t n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::pair<size_t, size_t>> edges(m);
    DisjointSet ds(n);

    for (size_t i = 0; i < m; ++i) {
        std::cin >> edges[i].first >> edges[i].second;
        --edges[i].first;
        --edges[i].second;
    }

    std::vector<Query> queries(k);
    for (size_t i = 0; i < k; ++i) {
        std::string cmd;
        size_t x, y;
        std::cin >> cmd >> x >> y;
        if (cmd == "ask") {
            queries[i] = {query_type::ask, x - 1, y - 1};
        } else {
            queries[i] = {query_type::cut, x - 1, y - 1};
        }
    }

    std::ranges::reverse(queries);

    std::vector<std::string> responses;
    for (const auto& query : queries) {
        if (query.type == query_type::ask) {
            responses.emplace_back(ds.Find(query.x) == ds.Find(query.y) ? "YES" : "NO");
        } else if (query.type == query_type::cut) {
            ds.Union(query.x, query.y);
        }
    }

    std::ranges::reverse(responses);
    for (const auto& response : responses) {
        std::cout << response << '\n';
    }

    return 0;
}
