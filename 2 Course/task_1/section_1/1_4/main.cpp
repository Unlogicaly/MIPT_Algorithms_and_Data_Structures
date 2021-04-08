#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

void decomposition(int_fast32_t num, std::vector<int_fast32_t> &result) {

    for (auto i = 2; i <= std::sqrt(num); ++i) {
        while (!(num % i)) {
            result.push_back(i);
            num /= i;
        }
    }

    if (num != 1)
        result.push_back(num);
}

int main() {

    std::ios::sync_with_stdio(false);

    int_fast32_t n;
    std::cin >> n;

    std::vector<int_fast32_t> result;
    decomposition(n, result);

    std::sort(result.data(), result.data() + result.size());

    int_fast32_t first = 1;

    for (auto i = result.size() - 1; i >= 1; --i) {
        first *= result[i];
    }

    std::cout << first << " " << (result[0] - 1) * first;

    return 0;
}