#include <iostream>
#include <vector>

void intersection(const std::vector<int_fast32_t> &a, const std::vector<int_fast32_t> &b,
        std::vector<int_fast32_t> &result) {
    uint_fast64_t left = 0;
    uint_fast64_t right = 2;
    for (auto elem: b) {
        while (right < a.size()) {

            auto cur = std::lower_bound(a.begin() + left, a.begin() + right, elem) - a.begin();

            if (elem < a[cur])
                break;

            if (a[cur] == elem) {
                result.push_back(elem);
                break;
            }

            left = cur + 1;
            right = left * 2;
        }
        if (right >= a.size()) {
            auto cur = std::lower_bound(a.begin() + left, a.end() - 1, elem) - a.begin();

            left = cur;
            if (a[cur] == elem)
                result.push_back(elem);
        }
    }
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n, m;
    std::cin>> n >> m;

    std::vector<int_fast32_t> a(n);
    std::vector<int_fast32_t> b(m);

    for (auto i = 0; i < n; ++i)
        std::cin >> a[i];

    for (auto i = 0; i < m; ++i)
        std::cin >> b[i];

    std::vector<int_fast32_t> res;
    res.reserve(m + n);

    intersection(a, b, res);

    for (auto i: res)
        std::cout << i << " ";
}