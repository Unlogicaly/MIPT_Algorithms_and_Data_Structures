//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_COUNT_SORT_H
#define UNTITLED_COUNT_SORT_H

#include <functional>
#include <vector>

template<typename T, class Cmp = std::less<T>>
void _count_sort(std::vector<T> &array, size_t left, size_t right, int max, Cmp cmp={}){
    std::vector<int> src(max, 0);

    for (auto i = left; i < right; ++i)
        src[array[i]]++;

    int sum = 0;

    for (auto i = 0; i < max; ++i) {
        auto tmp = src[i];
        src[i] = sum;
        sum += tmp;
    }

    std::vector<T> tmp(right - left, 0);

    for (auto i = left; i < right; ++i) {
        tmp[src[array[i]]++] = array[i];
    }

    memcpy(array.data() + left, tmp.data(), (right - left) * sizeof(T));
}

template<typename T, class Cmp = std::less<T>>
void count_sort(std::vector<T> &array, Cmp cmp={}) {
    if (array.size() <= 1)
        return;

    T max = array[0];
    for (auto i = 1; i < array.size(); ++i)
        max = std::max(max, array[i]);

    _count_sort(array, 0, array.size(), max + 1, cmp);
}

#endif //UNTITLED_COUNT_SORT_H
