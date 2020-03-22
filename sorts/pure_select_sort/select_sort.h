//
// Created by tarog on 3/19/2020.
//

#ifndef SELECT_SORT_H
#define SELECT_SORT_H

#include <vector>
#include <functional>

template <typename T, class Cmp = std::less<T>>
void _select_sort(std::vector<T> &array, size_t left, size_t right, Cmp cmp={}) {
    for (auto i = left; i < right - 1; ++i) {
        size_t ind = i;
        for (auto j = i + 1; j < right; ++j) {
            if (cmp(array[j], array[ind]))
                 ind = j;
        }
        std::swap(array[i], array[ind]);
    }
}

template<typename T, class Cmp = std::less<T>>
void select_sort(std::vector<T> &array, Cmp cmp={}){
    if (array.size() <= 1)
        return;
    _select_sort(array, 0, array.size(), cmp);
}

#endif //SELECT_SORT_H
