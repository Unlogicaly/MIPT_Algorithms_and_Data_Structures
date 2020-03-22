#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

bool operator <(std::pair<int_fast32_t, int_fast32_t> lhs, std::pair<int_fast32_t, int_fast32_t> rhs) {
    return lhs.first < rhs.first;
}

double s(std::pair<int_fast32_t, int_fast32_t> a, std::pair<int_fast32_t, int_fast32_t> b, std::pair<int_fast32_t, int_fast32_t> c) {
    return 0.5 * std::abs((a.first - c.first) * (b.second - c.second) - (b.first - c.first) * (a.second - c.second));
}

int main() {

    std::ios::sync_with_stdio(false);

    double res = 0;

    int_fast32_t n;
    std::cin >> n;

    std::vector<std::pair<int_fast32_t, int_fast32_t>> point_fast32_ts(n);

    for (auto i = 0; i < n; ++i) {
        std::cin >> point_fast32_ts[i].first >> point_fast32_ts[i].second;
    }

    std::sort(point_fast32_ts.data(), point_fast32_ts.data() + point_fast32_ts.size());

    for (auto i = 0; i < point_fast32_ts.size() - 2; ++i) {
        res += s(point_fast32_ts[i], point_fast32_ts[i+1], point_fast32_ts[i + 2]);
    }

    std::cout << res;

    return 0;
}