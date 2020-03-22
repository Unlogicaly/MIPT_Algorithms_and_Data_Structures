#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int_fast64_t find_min(const std::vector<int_fast32_t> &a, int_fast32_t val) {
    int_fast32_t range = 2;
    int_fast32_t start = 0;
    while (range + start <= a.size()) {
        auto t = std::lower_bound(a.begin() + start, a.begin() + start + range, val);

        if (t - a.begin() < start + range)
            return t - a.begin();

        start += range;
        range *= 2;
    }

    return std::lower_bound(a.begin() + start, a.end(), val) - a.begin();
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n, m;
    std::cin >> n >> m;

    std::vector<int_fast32_t> a(n);
    std::vector<int_fast32_t> b(m);

    for(auto i = 0; i < n; ++i)
        std::cin >> a[i];

    for(auto i = 0; i < m; ++i)
        std::cin >> b[i];

    for (auto i = 0; i < m; ++i) {
        std::cout << find_min(a, b[i]) << " ";
    }

    return 0;
}