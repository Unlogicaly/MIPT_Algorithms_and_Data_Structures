#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, class Cmp = std::less<T>>
void _insert_sort(std::vector<T> &array, uint_fast64_t left, uint_fast64_t right, Cmp cmp = {}) noexcept {

    for (auto i = left; i < right; ++i) {
        auto pos = i - 1;

        while (pos >= left and array[pos] > array[i])
            --pos;

        for (register auto j = i; j > pos + 1; --j)
            std::swap(array[j], array[j - 1]);
    }
}

template <typename T, class Cmp = std::less<T>>
inline uint_fast64_t pivot(const std::vector<T> &array, uint_fast64_t left, uint_fast64_t right, Cmp cmp = {}) noexcept {

    auto mid = (left + right) >> 2;
    auto a = array[left], b = array[mid], c = array[right - 1];

    return a < b ? b < c ? mid : a < c ? right - 1 : left : a < c ? left : b < c ? right - 1 : mid;
}

template <typename T, class Cmp = std::less<T>>
uint_fast64_t partition(std::vector<T> &array, uint_fast64_t left, uint_fast64_t right, Cmp cmp = {}) noexcept {

    uint_fast64_t p_ind = pivot(array, left, right, cmp);

    uint_fast64_t pivot = array[p_ind];

    std::swap(array[p_ind], array[right - 1]);
    --right;

    auto i = left, j = right - 1;

    while (i < j) {
        while (i != right and array[i] < pivot)
            ++i;
        while (j != left and array[j] >= pivot)
            --j;

        if (i < j)
            std::swap(array[i], array[j]);
    }

    std::swap(array[right], array[i]);

    return i;
}

template <typename T, class Cmp = std::less<T>>
void _quick_sort(std::vector<T> &array, uint_fast64_t left, uint_fast64_t right, Cmp cmp = {}) noexcept {

    while (right > 16 + left) {
        auto p_ind = partition(array, left, right, cmp);
        if (p_ind - left < right - p_ind + 1) {
            _quick_sort(array, left, p_ind, cmp);
            left = p_ind + 1;
        }
        else {
            _quick_sort(array, p_ind + 1, right, cmp);
            right = p_ind;
        }
    }

    _insert_sort(array, left, right, cmp);
}

bool read(uint_fast32_t & out)
{
    int c = getchar();
    uint_fast32_t x = 0;

    for (; !('0'<=c and c<='9'); c = getchar())
    {
        if (c == EOF)
            return false;
    }

    if (c == EOF)
        return false;
    for (; '0' <= c and c <= '9' ; c = getchar())
    {
        x = x*10 + c - '0';
    }
    out = x;
    return true;
}

int main() {

    std::ios::sync_with_stdio(false);

    std::vector<uint_fast32_t> a;
    a.reserve(25000000);

    uint_fast32_t tmp;

    while(read(tmp)) {
        a.push_back(tmp);
    }

    uint_fast64_t n{a.size()};

    _quick_sort(a, 0, n);

    for (register uint_fast32_t i = 9; i < n; i += 10)
        std::cout << a[i] << ' ';

    return 0;
}