#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <algorithm>

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n, k;

    std::cin >> n;

    std::vector<int_fast32_t> a(n);

    for (auto i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::cin >> k;

    if (k == 1) {
        for (auto i: a) {
            std::cout << i << " ";
        }
        return 0;
    }

    --k;

    std::vector<int_fast32_t> b(n);
    std::vector<int_fast32_t> c(n);

    b.front() = a.front();
    c.back() = a.back();

    for (uint_fast64_t i = 1, j = n - 2; i < n; ++i, --j) {
        b[i] = (i % k ? std::max(a[i], b[i - 1]) : a[i]);
        c[j] = ((j + 1) % k ? std::max(a[j], c[j + 1]) : a[j]);
    }

    for (auto i = 0; i < n - k; ++i) {
        std::cout << std::max(c[i], b[i + k]) << " ";
    }

    return 0;
}