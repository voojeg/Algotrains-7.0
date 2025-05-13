#include <iostream>
#include <deque>

class CustomDeque {
public:
    void PushFront(int n) {
        d.push_front(n);
    }

    void PushBack(int n) {
        d.push_back(n);
    }

    std::pair<bool, int> PopFront() {
        if (d.empty()) {
            return {false, 0};
        }
        const auto ret = d.front();
        d.pop_front();
        return {true, ret};
    }

    std::pair<bool, int> PopBack() {
        if (d.empty()) {
            return {false, 0};
        }
        const auto ret = d.back();
        d.pop_back();
        return {true, ret};
    }

    std::pair<bool, int> Front() const {
        if (d.empty()) {
            return {false, 0};
        }
        return {true, d.front()};
    }

    std::pair<bool, int> Back() const {
        if (d.empty()) {
            return {false, 0};
        }
        return {true, d.back()};
    }

    size_t Size() const {
        return d.size();
    }

    void Clear() {
        d.clear();
    }
private:
    std::deque<int> d;
};

int main() {
    std::string cmd;
    CustomDeque d;

    while (std::cin >> cmd && cmd != "exit") {
        if (cmd == "push_front") {
            int n;
            std::cin >> n;
            d.PushFront(n);
            std::cout << "ok\n";
        } else if (cmd == "push_back") {
            int n;
            std::cin >> n;
            d.PushBack(n);
            std::cout << "ok\n";
        } else if (cmd == "pop_front") {
            const auto res = d.PopFront();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        }  else if (cmd == "pop_back") {
            const auto res = d.PopBack();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        } else if (cmd == "front") {
            const auto res = d.Front();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        }  else if (cmd == "back") {
            const auto res = d.Back();
            if (res.first) {
                std::cout << res.second << '\n';
            } else {
                std::cout << "error\n";
            }
        } else if (cmd == "size") {
            std::cout << d.Size() << '\n';
        } else if (cmd == "clear") {
            d.Clear();
            std::cout << "ok\n";
        }
    }
    std::cout << "bye\n";
    return 0;
}
