//
// Created by tarog on 3/19/2020.
//

#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include <algorithm>

template <typename _Iter, class _Cmp>
void insert_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    for (auto iter = begin; iter != end; ++iter) {
        auto pos = std::lower_bound(begin, iter, *iter, cmp);
        for (auto i = iter; i != pos; --i) {
            std::swap(*i, *(i - 1));
        }
    }
}

template <typename _Iter>
void insert_sort(_Iter begin, _Iter end) {

    for (auto iter = begin; iter != end; ++iter) {
        auto pos = std::lower_bound(begin, iter, *iter);
        for (auto i = iter; i != pos; --i) {
            std::swap(*i, *(i - 1));
        }
    }
}

#endif //INSERT_SORT_H
