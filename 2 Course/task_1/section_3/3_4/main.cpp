#include <iostream>
#include <vector>

uint_fast64_t find_closest(const std::vector<int_fast32_t> &a, int_fast32_t val) {
    uint_fast64_t step = 2;
    uint_fast64_t start = 0;

    if (a[0] >= val)
        return 0;

    if (a.back() <= val)
        return a.size() - 1;

    while (start + step < a.size()) {
        if (a[start] <= val and a[start + step] >= val)
            break;

        start += step;
        step *= 2;
    }

    auto left = start;
    auto right = std::min(start + step, a.size());
    auto middle = (left + right) / 2;

    while (right - left > 1) {

        if (a[middle - 1] <= val and a[middle] >= val)
            break;

        if (a[middle - 1] < val and a[middle] < val) {
            left = middle;
            middle = (left + right) / 2;
            continue;
        }

        right = middle;
        middle = (left + right) / 2;
    }

    if (right - left == 1)
        middle = right;

    if (a[middle] - val < val - a[middle - 1])
        return middle;

    return middle - 1;
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    std::vector<int_fast32_t> a(n);

    for (auto i = 0; i < n; ++i)
        std::cin >> a[i];


    uint_fast64_t m;
    std::cin >> m;
    std::vector<int_fast32_t> b(m);

    for (auto i = 0; i < m; ++i)
        std::cin >> b[i];

    for (auto i: b) {
        std::cout << find_closest(a, i) << " ";
    }

    return 0;
}