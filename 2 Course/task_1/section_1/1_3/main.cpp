#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

int_fast32_t gcd(int_fast32_t a, int_fast32_t b) {
    return a % b ? gcd (b, a % b) : b;
}

int_fast32_t lcm(int_fast32_t a, int_fast32_t b) {
    return a * b / gcd(a, b);
}

std::pair<int_fast32_t, int_fast32_t> sum(int_fast32_t a, int_fast32_t b, int_fast32_t c, int_fast32_t d) {
    int_fast32_t n = b * d;
    int_fast32_t m = a * d + b * c;

    int_fast32_t tmp = gcd(m, n);

    return {m / tmp, n / tmp};
}

int main() {

    std::ios::sync_with_stdio(false);

    int_fast32_t a, b, c, d;

    std::cin >> a >> b >> c >> d;

    auto t = sum(a, b, c, d);

    std::cout << t.first << " " << t.second;

    return 0;
}