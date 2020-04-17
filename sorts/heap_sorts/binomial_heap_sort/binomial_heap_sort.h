//
// Created by tarog on 4/17/2020.
//

#ifndef BINOMIAL_HEAP_SORT_H
#define BINOMIAL_HEAP_SORT_H

#include "binomialHeap.h"

template <typename _Iter, class _Cmp>
void binomial_heap_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    BinomialHeap<typeof(*begin), _Cmp> tree(begin, end);

    for (; begin != end; ++begin) {
        *begin = tree.top();
        tree.pop();
    }
}

template <typename _Iter>
void leftist_heap_sort(_Iter begin, _Iter end) {

    BinomialHeap<typeof(*begin)> tree(begin, end);

    for (; begin != end; ++begin) {
        *begin = tree.top();
        tree.pop();
    }
}

#endif //UNTITLED_BINOMIAL_HEAP_SORT_H
