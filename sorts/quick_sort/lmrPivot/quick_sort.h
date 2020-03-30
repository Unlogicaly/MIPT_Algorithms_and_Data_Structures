//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_QUICK_SORT_H
#define UNTITLED_QUICK_SORT_H

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

    if (end - begin > 2) {
        _Iter p_ind = partition<_Iter, _Cmp>(begin, end);
        quick_sort(begin, p_ind, cmp);
        quick_sort(p_ind + 1, end, cmp);
    }
    else if (end - begin == 2 and cmp(*(begin + 1), *begin))
        std::swap(*begin, *(begin + 1));
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

    if (end - begin > 2) {
        _Iter p_ind = partition(begin, end);
        quick_sort(begin, p_ind);
        quick_sort(p_ind + 1, end);
    }
    else if (end - begin == 2 and *(begin + 1) < *begin)
        std::swap(*begin, *(begin + 1));
}

#endif //UNTITLED_QUICK_SORT_H

