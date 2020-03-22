#include <iostream>
#include <vector>

std::pair<size_t, size_t> find_indexes(const std::vector<int_fast32_t> &a, const std::vector<int_fast32_t> &b) {

    int_fast32_t loc_max = a[0];
    int_fast32_t loc_max_ind = 0;

    int_fast32_t max_sum = a[0] + b[0];

    std::pair<size_t, size_t> res{0, 0};

    for (auto i = 0; i < a.size(); ++i) {

        if (a[i] > loc_max) {
            loc_max = a[i];
            loc_max_ind = i;
        }

        if (b[i] + loc_max > max_sum) {
            max_sum = b[i] + loc_max;
            res = {loc_max_ind, i};
        }
    }

    return res;
}

int main() {

    size_t n;
    std::cin >> n;

    std::vector<int_fast32_t> a(n);
    std::vector<int_fast32_t> b(n);

    for (auto i = 0; i < n; ++i)
        std::cin >> a[i];

    for (auto i = 0; i < n; ++i)
        std::cin >> b[i];

    auto res = find_indexes(a, b);

    std::cout << res.first << " " << res.second;

    return 0;
}