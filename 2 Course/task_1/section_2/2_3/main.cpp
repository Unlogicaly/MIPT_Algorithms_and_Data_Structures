#include <iostream>
#include <vector>

int_fast32_t count(const std::vector<int_fast32_t> &a, const std::vector<int_fast32_t> &b, int_fast32_t aim) {
    size_t i = 0, j = b.size() - 1;
    int_fast32_t res = 0;
    while (i < a.size() and j >= 0) {
        if (a[i] + b[j] == aim) {
            ++res;
            ++i;
            --j;
            continue;
        }

        if (a[i] + b[j] > aim) {
            --j;
            continue;
        }

        ++i;
    }

    while (i < a.size()) {
        if (a[i] + b[0] == aim) {
            ++res;
            break;
        }
        ++i;
    }

    while (j >= 0) {
        if (a.back() + b[j] == aim) {
            ++res;
            break;
        }
        --j;
    }

    return res;
}

int main() {

    std::ios::sync_with_stdio(false);

    int_fast32_t n, m;
    std::cin >> n;
    std::vector<int_fast32_t> a(n);

    for (auto i = 0; i < n; ++i){
        std::cin >> a[i];
    }

    std::cin >> m;
    std::vector<int_fast32_t> b(m);

    for (auto i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    int_fast32_t required;
    std::cin >> required;
    std::cout << count(a, b, required);

    return 0;
}