#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <cstring>

template <typename T>
struct Byte {
    size_t byte;

    explicit Byte(size_t byte) : byte{byte} {}

    int operator()(T elem) {
        return (elem >> 8 * byte) & uint8_t(255);
    }
};

template<typename T>
struct Self {

    size_t operator ()(const T &elem) {
        return size_t(elem);
    }
};

template<typename T, class Feature = Self<T>>
void _count_sort(std::vector<T> &array, size_t left, size_t right, size_t max, Feature feature={}, bool return_counts = false,
                 std::vector<size_t> *counts = new std::vector<size_t>{}){

    auto *src = new std::vector<size_t>(max, 0);

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

template<typename T, class Feature = Self<T>>
void count_sort(std::vector<T> &array, size_t max, Feature feature={}, bool return_counts = false,
                std::vector<size_t> *counts = new std::vector<size_t>{}) {

    _count_sort(array, 0, array.size(), max, feature, return_counts, counts);
}

template<typename T, class Feature = Byte<T>>
void radix_sort(std::vector<T> &array, size_t max) {

    for (size_t i = 0; i < sizeof(T); ++i)
        count_sort(array, max, Feature{i});
}

int main() {

    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<size_t> a(n);

    size_t max{256};

    for (auto i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    radix_sort(a, max);

    for (auto i: a)
        std::cout << i << " ";

    return 0;
}