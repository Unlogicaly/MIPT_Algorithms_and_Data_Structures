#include <iostream>
#include <vector>
#include <stack>

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    std::stack<std::pair<int_fast32_t, int_fast32_t>> a;
    int_fast32_t w, h;
    std::cin >> w >> h;

    a.emplace(w, h);

    int_fast32_t max_s = 0;

    for (auto i = 0; i < n - 1; ++i) {
        std::cin >> w >> h;
        if (h >= a.top().second) {
            a.emplace(w + a.top().first, h);
            continue;
        }

        auto cur_x = a.top().first;

        while (a.size() > 1 and h < a.top().second) {
            auto cur = a.top();
            a.pop();
            max_s = std::max(max_s, cur.second * (cur_x - a.top().first));
        }

        if (a.size() == 1) {
            max_s = std::max(max_s, a.top().second * cur_x);
            if (h < a.top().second)
                a.pop();
        }

        a.emplace(w + cur_x, h);
    }

    h = 0;

    auto cur_x = a.top().first;

    while (a.size() > 1 and h < a.top().second) {
        auto cur = a.top();
        a.pop();
        max_s = std::max(max_s, cur.second * (cur_x - a.top().first));
    }

    if (a.size() == 1) {
        max_s = std::max(max_s, a.top().second * cur_x);
    }

    std::cout << max_s;

    return 0;
}