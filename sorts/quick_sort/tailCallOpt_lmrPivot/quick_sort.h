//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_QUICK_SORT_H
#define UNTITLED_QUICK_SORT_H

#include <functional>
#include <vector>
#include <random>

template <typename T, class Cmp = std::less<T>>
size_t pivot(const std::vector<T> &array, size_t left, size_t right, Cmp cmp = {}) {

    auto mid = (left + right) / 2;
    auto a = array[left], b = array[mid], c = array[right - 1];

    if (a < b) {
        if (b < c)
            return mid;
        if (a < c)
            return right - 1;
        return left;
    }
    if (a < c)
        return left;
    if (b < c)
        return right - 1;
    return mid;
}

template <typename T, class Cmp = std::less<T>>
size_t partition(std::vector<T> &array, size_t left, size_t right, Cmp cmp = {}) {

    auto p_ind = pivot(array, left, right, cmp);

    auto pivot = array[p_ind];

    std::swap(array[p_ind], array[right - 1]);
    --right;

    auto i = left, j = right - 1;

    while (i < j) {
        while (array[i] < pivot)
            ++i;
        while (array[j] >= pivot)
            --j;

        if (i < j)
            std::swap(array[i], array[j]);
    }

    std::swap(array[right], array[i]);

    return i;
}

template <typename T, class Cmp = std::less<T>>
void _quick_sort(std::vector<T> &array, size_t left, size_t right, Cmp cmp = {}) {

    while (right - left > 1) {
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
}

template <typename T, class Cmp = std::less<T>>
void quick_sort(std::vector<T> &array, Cmp cmp = {}) {

    if (array.size() <= 1)
        return;
    _quick_sort(array, 0, array.size(), cmp);
}

#endif //UNTITLED_QUICK_SORT_H
