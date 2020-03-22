#include <iostream>

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast32_t n;
    std::cin >> n;

    auto a = new int_fast32_t[n];

    for (auto i = 0; i < n; ++i)
        std::cin >> a[i];

    for (auto i = 0; i < n / 2; ++i)
        std::swap(a[i], a[n - i - 1]);

    for (auto i = 0; i < n; ++i)
        std::cout << a[i] << " ";

    return 0;
}