//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_LSD_RADIX_SORT_H
#define UNTITLED_LSD_RADIX_SORT_H

#include "count_sort.h"
#include <cmath>

template <typename T>
struct Byte {
    size_t byte;

    explicit Byte(size_t byte) : byte{byte} {}

    int operator()(T elem) {
        return (elem >> 8 * byte) & uint8_t(255);
    }
};

template<typename T>
void radix_sort(std::vector<T> &array, T max) {

    for (size_t i = 0; i < sizeof(T); ++i)
        count_sort(array, max, Byte<T>{i});
}

#endif //UNTITLED_LSD_RADIX_SORT_H
