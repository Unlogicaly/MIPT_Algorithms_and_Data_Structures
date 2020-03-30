//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_QUICK_SORT_H
#define UNTITLED_QUICK_SORT_H

#include "insert_sort.h"

template <typename _Iter, class _Cmp>
auto pivot(_Iter begin, _Iter end, _Cmp cmp = {}) {

    auto mid = begin + (end - begin) / 2;

    if (cmp(*begin, *mid)) {
        if (cmp(*mid, *(end - 1)))
            return mid;
        if (cmp(*begin, *(end - 1)))
            return end - 1;
        return begin;
    }

    if (cmp(*begin, *(end - 1)))
        return begin;
    if (cmp(*mid , *(end - 1)))
        return end - 1;
    return mid;
}

template <typename _Iter, class _Cmp>
_Iter partition(_Iter begin, _Iter end, _Cmp cmp = {}) {

    auto p = pivot(begin, end, cmp);

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

    while (end - begin > 40) {
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
    insert_sort(begin, end, cmp);
}

template <typename _Iter>
auto pivot(_Iter begin, _Iter end) {

    auto mid = begin + (end - begin) / 2;

    if (*begin < *mid) {
        if (*mid < *(end - 1))
            return mid;
        if (*begin < *(end - 1))
            return end - 1;
        return begin;
    }

    if (*begin < *(end - 1))
        return begin;
    if (*mid < *(end - 1))
        return end - 1;
    return mid;
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

    while (end - begin > 40) {
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

    insert_sort(begin, end);
}

#endif //UNTITLED_QUICK_SORT_H
