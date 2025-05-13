#include <iostream>
#include <queue>

class CustomQueue {
public:
    void Push(int n) {
        q.push(n);
    }

    std::pair<bool, int> Pop() {
        if (q.empty()) {
            return {false, 0};
        }
        const auto ret = q.front();
        q.pop();
        return {true, ret};
    }

    std::pair<bool, int> Front() const {
        if (q.empty()) {
            return {false, 0};
        }
        return {true, q.front()};
    }

    size_t Size() const {
        return q.size();
    }

    void Clear() {
        while (!q.empty()) {
            q.pop();
        }
    }
private:
    std::queue<int> q;
};

int main() {
    std::string cmd;
    CustomQueue q;

    while (std::cin >> cmd && cmd != "exit") {
        if (cmd == "push") {
            int n;
            std::cin >> n;
            q.Push(n);
            std::cout << "ok\n";
        } else if (cmd == "pop") {
            const auto res = q.Pop();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        } else if (cmd == "front") {
            const auto res = q.Front();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        } else if (cmd == "size") {
            std::cout << q.Size() << '\n';
        } else if (cmd == "clear") {
            q.Clear();
            std::cout << "ok\n";
        }
    }
    std::cout << "bye\n";
    return 0;
}
