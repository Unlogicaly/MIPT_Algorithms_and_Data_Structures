//
// Created by tarog on 3/19/2020.
//

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

template <typename T, typename _Iter>
void merge(const std::vector<T> &lhs, const std::vector<T> &rhs, _Iter begin) {

    size_t i = 0, j = 0;

    while (i < lhs.size() and j < rhs.size()) {
        *(begin++) = (lhs.at(i) < rhs.at(j) ? lhs.at(i++) : rhs.at(j++));
    }

    while (i < lhs.size())
        *(begin++) = (lhs.at(i++));

    while (j < rhs.size())
        *(begin++) = (rhs.at(j++));
}

template <typename _Iter>
void merge_sort(_Iter begin, _Iter end) {

    if (end - begin <= 1)
        return;

    merge_sort(begin, begin + (end - begin) / 2);
    merge_sort(begin + (end - begin) / 2, end);

    std::vector<typeof(*begin)> a(begin, begin + (end - begin) / 2);
    std::vector<typeof(*begin)> b(begin + (end - begin) / 2, end);

    merge<typeof(*begin)>(a, b, begin);
}

template <typename T, typename _Iter, class _Cmp>
void merge(const std::vector<T> &lhs, const std::vector<T> &rhs, _Iter begin, _Cmp cmp = {}) {

    size_t i = 0, j = 0;

    while (i < lhs.size() and j < rhs.size()) {
        *(begin++) = (cmp(lhs.at(i), rhs.at(j)) ? lhs.at(i++) : rhs.at(j++));
    }

    while (i < lhs.size())
        *(begin++) = (lhs.at(i++));

    while (j < rhs.size())
        *(begin++) = (rhs.at(j++));
}

template <typename _Iter, class _Cmp>
void merge_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    if (end - begin <= 1)
        return;

    merge_sort(begin, begin + (end - begin) / 2, cmp);
    merge_sort(begin + (end - begin) / 2, end, cmp);

    std::vector<typeof(*begin)> a(begin, begin + (end - begin) / 2);
    std::vector<typeof(*begin)> b(begin + (end - begin) / 2, end);

    merge<typeof(*begin), _Iter, _Cmp>(a, b, begin);
}

//template <typename T, class Cmp = std::less<T>>
//void merge_sort(std::vector<T> &array, Cmp cmp = {}) {
//
//    if (array.size() <= 1)
//        return;
//
//    _merge_sort<T, Cmp>(array, 0, array.size(), cmp);
//}

#endif //MERGE_SORT_H
