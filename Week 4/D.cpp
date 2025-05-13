#include <algorithm>
#include <iostream>
#include <list>

int main() {
    int n;
    std::cin >> n;
    std::list<std::string> windows;
    auto pos = windows.end();
    size_t curr_window = 0;

    for (int i = 0; i < n; ++i) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Run") {
            std::string app_name;
            std::getline(std::cin, app_name, '\n');
            if (!app_name.empty()) {
                app_name = app_name.substr(1);
            }
            pos = windows.insert(pos, app_name);
            std::cout << app_name << std::endl;
        } else {
            const auto k = std::ranges::count(cmd, '+');
            curr_window = k % windows.size();
            pos = std::next(windows.begin(), curr_window);
            windows.push_front(*pos);
            windows.erase(pos);
            pos = windows.begin();
            std::cout << windows.front() << std::endl;
        }
    }

    return 0;
}
