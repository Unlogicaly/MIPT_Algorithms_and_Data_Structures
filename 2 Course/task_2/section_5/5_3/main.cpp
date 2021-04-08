#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <cstring>

template<typename T>
struct Self {

    size_t operator ()(const T &elem) {
        return size_t(elem);
    }
};

struct Bit {

    size_t bit;

    explicit Bit(size_t bit) : bit{bit} {}

    size_t operator ()(const size_t &elem) {
        return (elem >> ((sizeof(size_t) << 3) - bit - 1)) & uint8_t(1);
    }
};

template<typename T, class Feature = Self<T>>
void _count_sort(std::vector<T> &array, size_t left, size_t right, size_t max, Feature feature={}, bool return_counts = false,
                 std::vector<size_t> *counts = new std::vector<size_t>{}){

    auto *src = new std::vector<size_t>(max);

    for (auto i = left; i < right; ++i)
        src->at(feature(array[i]))++;

    size_t sum = 0;

    for (auto i = 0; i < max; ++i) {
        auto tmp = src->at(i);
        src->at(i) = sum;
        sum += tmp;
    }

    auto *tmp = new std::vector<T>(right - left);

    for (auto i = left; i < right; ++i) {
        tmp->at(src->at(feature(array[i]))++) = array[i];
    }

    if (return_counts) {
        for (size_t &i : *src)
            i += left;
        std::swap(*counts, *src);
    }

    else {
        delete counts;
    }

    delete src;

    for (auto i = 0; i < tmp->size(); ++i) {
        array[i + left] = tmp->at(i);
    }

    delete tmp;
}

template<typename T>
void _radix_sort(std::vector<T> &array, size_t max, size_t left, size_t right, size_t n) {

    if (right - left <= 1)
        return;

    std::vector<size_t> counts;

    _count_sort(array, left, right, max, Bit{n}, true, &counts);

    _radix_sort(array, max, left, counts[0], n + 1);
    _radix_sort(array, max, counts[0], right, n + 1);
}

template<typename T>
void radix_sort(std::vector<T> &array, size_t max) {

    _radix_sort(array, max, 0, array.size(), 0);
}

int main() {

    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<size_t> a(n);

    size_t max{2};

    for (auto i = 0; i < n; ++i) {

        std::cin >> a[i];
    }

    radix_sort(a, max);

    for (auto &i: a)
        std::cout << i << " ";

    return 0;
}