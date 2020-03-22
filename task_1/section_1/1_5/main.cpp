#include <iostream>

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast32_t n;
    std::cin >> n;

    uint_fast32_t i = 1;
    uint_fast32_t c = 3;

    for (auto j = 0; j < n; ++j) {
        std::cout << i << " ";
        i += c;
        c += 2;
    }

    return 0;
}