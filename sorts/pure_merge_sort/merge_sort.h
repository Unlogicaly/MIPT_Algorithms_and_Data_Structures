//
// Created by tarog on 3/19/2020.
//

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <iostream>
#include <vector>

template <typename T, class Cmp = std::less<T>>
void merge(const std::vector<T> &lhs, const std::vector<T> &rhs, std::vector<T> &result, size_t start, Cmp cmp = {}) {

    result.reserve(lhs.size() + rhs.size());

    size_t i = 0, j = 0;

    while (i < lhs.size() and j < rhs.size()) {
        result.at(start++) = (cmp(lhs.at(i), rhs.at(j)) ? lhs.at(i++) : rhs.at(j++));
    }

    while (i < lhs.size())
        result.at(start++) = (lhs.at(i++));

    while (j < rhs.size())
        result.at(start++) = (rhs.at(j++));
}

template <typename T, class Cmp = std::less<T>>
void _merge_sort(std::vector<T> &array, size_t left, size_t right, Cmp cmp = {}) {

    if (right - left <= 1)
        return;

    _merge_sort<T, Cmp>(array, left, (right + left) / 2, cmp);
    _merge_sort<T, Cmp>(array, (right + left) / 2, right, cmp);

    std::vector<T> a(array.begin() + left, array.begin() + (right + left) / 2);
    std::vector<T> b(array.begin() + (right + left) / 2, array.begin() + right);

    merge<T, Cmp>(a, b, array, left);
}

template <typename T, class Cmp = std::less<T>>
void merge_sort(std::vector<T> &array, Cmp cmp = {}) {

    if (array.size() <= 1)
        return;

    _merge_sort<T, Cmp>(array, 0, array.size(), cmp);
}

#endif //MERGE_SORT_H
