#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <cstring>

struct Elem {
    size_t index;
    int decrease;

    explicit Elem(size_t index) : index{index}, decrease{0} {}

    size_t operator()(const std::string &s) {
        return index < s.size() ? size_t(s[index] - decrease) : 0;
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
void _radix_sort(std::vector<T> &array, size_t max, size_t max_len, size_t left, size_t right, size_t n) {

    std::vector<size_t> counts;

    _count_sort(array, left, right, max, Elem{n}, true, &counts);

    for (size_t i = 0; i < counts.size() - 1; ++i) {

        if (counts[i + 1] - counts[i] <= 1)
            continue;

        if (Elem{n}(array[counts[i]]) == 0)
            continue;

        _radix_sort(array, max, max_len, counts[i], counts[i + 1], n + 1);
    }
}

template<typename T>
void radix_sort(std::vector<T> &array, size_t max, size_t max_len) {

    _radix_sort(array, max, max_len, 0, array.size(), 0);
}


int main() {

    std::ios::sync_with_stdio(false);

    std::vector<std::string> a;
    a.reserve(100000);

    size_t max{256};
    size_t max_len{0};

    std::string s;

    while(std::cin >> s) {

        a.push_back(s);

        max_len = std::max(max_len, s.size());
    }

    radix_sort(a, max, max_len);

    for (auto &i: a)
        std::cout << i << "\n";

    return 0;
}