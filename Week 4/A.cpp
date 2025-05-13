#include <iostream>
#include <stack>

class CustomStack {
public:
    void Push(int n) {
        s.push(n);
    }

    std::pair<bool, int> Pop() {
        if (s.empty()) {
            return {false, 0};
        }
        const auto ret = s.top();
        s.pop();
        return {true, ret};
    }

    std::pair<bool, int> Back() const {
        if (s.empty()) {
            return {false, 0};
        }
        return {true, s.top()};
    }

    size_t Size() const {
        return s.size();
    }

    void Clear() {
        while (!s.empty()) {
            s.pop();
        }
    }
private:
    std::stack<int> s;
};

int main() {
    std::string cmd;
    CustomStack s;

    while (std::cin >> cmd && cmd != "exit") {
        if (cmd == "push") {
            int n;
            std::cin >> n;
            s.Push(n);
            std::cout << "ok\n";
        } else if (cmd == "pop") {
            const auto res = s.Pop();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        } else if (cmd == "back") {
            const auto res = s.Back();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        } else if (cmd == "size") {
            std::cout << s.Size() << '\n';
        } else if (cmd == "clear") {
            s.Clear();
            std::cout << "ok\n";
        }
    }
    std::cout << "bye\n";
    return 0;
}
