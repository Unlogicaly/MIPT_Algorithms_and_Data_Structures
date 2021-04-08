#include <iostream>
#include <vector>

uint_fast64_t search(const std::vector<int_fast32_t> &a, uint_fast64_t left, uint_fast64_t right) {

    auto middle = (left + right) / 2;

    while (!(a[middle - 1] < a[middle] and a[middle] > a[middle + 1])) {

        if (right - left <= 1)
            break;

        if (a[middle - 1] < a[middle] and a[middle] < a[middle + 1]) {
            left = middle;
            middle = (left + right) / 2;
            continue;
        }

        right = middle;

        middle = (left + right) / 2;
    }

    return middle;
}

uint_fast64_t find_trans(const std::vector<int_fast32_t> &a) {
    uint_fast64_t range = 2;
    uint_fast64_t start = 0;
    auto cur = search(a, start, start + range);

    while(range + start <= a.size() and cur == -1) {
        start += range;
        range *= 2;
        cur = search(a, start, start + range);
    }

    cur = search(a, start, a.size());

    return cur;
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    std::vector<int_fast32_t> a(n);

    for (auto i = 0; i < n; ++i)
        std::cin >> a[i];

    auto t = find_trans(a);

    std::cout << (t == -1 ? 0 : t);

    return 0;
}