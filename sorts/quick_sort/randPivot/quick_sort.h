//
// Created by tarog on 3/19/2020.
//

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <functional>
#include <vector>
#include <random>

template <typename _Iter>
_Iter pivot(_Iter begin, _Iter end) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> uni(0, end - begin - 1);

    return begin + uni(rng);
}

template <typename _Iter, class _Cmp>
_Iter partition(_Iter begin, _Iter end, _Cmp cmp = {}) {

    auto p = pivot(begin, end);

    auto pivot = *p;

    std::swap(*p, *(end - 1));
    --end;

    auto i = begin, j = end - 1;

    while (i < j) {
        while (i != end and cmp(*i, pivot))
            ++i;
        while (j != begin and !cmp(*j, pivot))
            --j;

        if (i < j)
            std::swap(*i, *j);
    }

    std::swap(*end, *i);

    return i;
}

template <typename _Iter, class _Cmp>
void quick_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    while (end - begin > 2) {
        _Iter p_ind = partition<_Iter, _Cmp>(begin, end);
        if (p_ind - begin < end - p_ind + 1) {
            quick_sort(begin, p_ind, cmp);
            begin = p_ind + 1;
        }
        else {
            quick_sort(p_ind + 1, end, cmp);
            end = p_ind;
        }
    }
    if (end - begin == 2 and cmp(*(begin + 1), *begin))
        std::swap(*begin, *(begin + 1));
}

template <typename _Iter>
_Iter partition(_Iter begin, _Iter end) {

    auto p = pivot(begin, end);

    auto pivot = *p;

    std::swap(*p, *(end - 1));
    --end;

    auto i = begin, j = end - 1;

    while (i < j) {
        while (i != end and *i < pivot)
            ++i;
        while (j != begin and *j >= pivot)
            --j;

        if (i < j)
            std::swap(*i, *j);
    }

    std::swap(*end, *i);

    return i;
}

template <typename _Iter>
void quick_sort(_Iter begin, _Iter end) {

    while (end - begin > 2) {
        _Iter p_ind = partition(begin, end);
        if (p_ind - begin < end - p_ind + 1) {
            quick_sort(begin, p_ind);
            begin = p_ind + 1;
        }
        else {
            quick_sort(p_ind + 1, end);
            end = p_ind;
        }
    }
    if (end - begin == 2 and *(begin + 1) < *begin)
        std::swap(*begin, *(begin + 1));
}

#endif //QUICK_SORT_H
