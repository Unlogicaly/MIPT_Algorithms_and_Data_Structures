//
// Created by tarog on 3/19/2020.
//

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "heap.h"

template<typename _Iter, class _Cmp>
void heap_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    Heap<typeof(*begin), _Cmp> src(begin, end);

    while (!src.empty()) {
        *(begin++) = src.top();
        src.pop();
    }
}

template<typename _Iter>
void heap_sort(_Iter begin, _Iter end) {

    Heap<typeof(*begin)> src(begin, end);

    while (!src.empty()) {
        *(begin++) = src.top();
        src.pop();
    }
}

#endif //HEAP_SORT_H
