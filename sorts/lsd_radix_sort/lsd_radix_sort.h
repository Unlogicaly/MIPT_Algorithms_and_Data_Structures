//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_LSD_RADIX_SORT_H
#define UNTITLED_LSD_RADIX_SORT_H

#include "count_sort.h"
#include <cmath>

template <typename T, class Cmp = std::less<T>>
struct ByteCmp {
    int byte;
    Cmp cmp{};

    explicit ByteCmp(int byte) : byte{byte} {}

    bool operator()(const T &lhs, const T &rhs) {
        return cmp(lhs / size_t(std::pow(10, byte)) % 10, rhs / size_t(std::pow(10, byte)) % 10);
    }
};

template<typename T, class Cmp = std::less<T>>
void radix_sort(std::vector<T> &array, int max_byte, Cmp cmp={}) {
    for (auto i = 0; i <= max_byte; ++i)
        count_sort(array, ByteCmp<T, Cmp>(i));
}

#endif //UNTITLED_LSD_RADIX_SORT_H
