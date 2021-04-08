#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

void decomposition(uint_fast32_t num, std::vector<uint_fast32_t > &result) {

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

    uint_fast32_t n;
    std::cin >> n;

    std::vector<uint_fast32_t > result;
    decomposition(n, result);

    std::sort(result.data(), result.data() + result.size());

    for (auto i: result)
        std::cout << i << " ";

    return 0;
}