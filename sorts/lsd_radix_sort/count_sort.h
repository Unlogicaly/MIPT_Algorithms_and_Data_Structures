//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_COUNT_SORT_H
#define UNTITLED_COUNT_SORT_H

#include <functional>
#include <vector>
#include <cassert>

template<typename T>
struct Self {

    size_t operator ()(const T &elem) {
        return size_t(elem);
    }
};

template<typename T, class Feature = Self<T>>
void _count_sort(std::vector<T> &array, size_t left, size_t right, T max, Feature feature={}, bool return_counts = false,
                 std::vector<size_t> *counts = nullptr){

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
void count_sort(std::vector<T> &array, T max, Feature feature={}, bool return_counts = false,
                std::vector<size_t> *counts = nullptr) {

    assert((return_counts and counts) or !(return_counts or counts));

    _count_sort(array, 0, array.size(), max, feature, return_counts, counts);
}

#endif //UNTITLED_COUNT_SORT_H
