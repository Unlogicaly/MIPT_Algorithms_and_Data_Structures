//
// Created by tarog on 4/17/2020.
//

#ifndef UNTITLED_SKEW_HEAP_SORT_H
#define UNTITLED_SKEW_HEAP_SORT_H

#include "skewHeap.h"

template <typename _Iter, class _Cmp>
void skew_heap_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    SkewHeap<typeof(*begin), _Cmp> tree(begin, end);

    for (; begin != end; ++begin) {
        *begin = tree.top();
        tree.pop();
    }
}

template <typename _Iter>
void skew_heap_sort(_Iter begin, _Iter end) {

    SkewHeap<typeof(*begin)> tree(begin, end);

    for (; begin != end; ++begin) {
        *begin = tree.top();
        tree.pop();
    }
}

#endif //UNTITLED_SKEW_HEAP_SORT_H
