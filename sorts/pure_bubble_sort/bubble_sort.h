//
// Created by tarog on 3/19/2020.
//

#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>
#include <functional>

template <typename T, class Cmp = std::less<T>>
void _bubble_sort(std::vector<T> &array, size_t left, size_t right, Cmp cmp={}) {
    for (auto i = left; i < right - 1; ++i) {
        bool sorted = true;
        for (auto j = left; j < right - i - 1; ++j) {
            if (!cmp(array[j], array[j + 1])) {
                sorted = false;
                std::swap(array[j], array[j + 1]);
            }
        }
        if (sorted)
            break;
    }
}

template <typename T, class Cmp = std::less<T>>
void bubble_sort(std::vector<T> &array, Cmp cmp = {}) {
    if (array.size() <= 1)
        return;
    _bubble_sort(array, 0, array.size(), cmp);
}

#endif //BUBBLE_SORT_H
