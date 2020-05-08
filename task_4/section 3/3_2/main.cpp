#include <iostream>
#include <vector>

uint_fast64_t high_pyramid(uint_fast64_t amount) {

    std::vector<std::vector<uint_fast64_t>> table(amount + 1, std::vector<uint_fast64_t>(amount + 1, 0));

    for (auto i = 1 ; i < amount + 1; ++i) {

        table[0][i] = 1;
        table[1][i] = 1;
    }

    for (uint_fast64_t i = 2; i < amount + 1; ++i) {

        for (uint_fast64_t j = 2; j <= i; ++j) {

            table[i][j] = table[i - j][j - 1] + table[i][j - 1];
        }
        for (uint_fast64_t j = i + 1; j < amount + 1; ++j)

            table[i][j] = table[i][j - 1];
    }

    return table[amount][amount];
}

int main() {

    uint_fast64_t n;
    std::cin >> n;

    std::cout << high_pyramid(n);

    return 0;
}
