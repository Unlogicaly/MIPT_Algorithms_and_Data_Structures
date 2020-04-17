//
// Created by tarog on 3/19/2020.
//

#ifndef THINHEAP_SORT_H
#define THINHEAP_SORT_H

#include "thinheap.h"

template<typename _Iter, class _Cmp>
void thin_heap_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    ThinHeap<typeof(*begin), _Cmp> src(begin, end);

    for (; begin != end; ++begin) {
        *begin = src.top();
        src.pop();
    }
}

template<typename _Iter>
void thin_heap_sort(_Iter begin, _Iter end) {

    ThinHeap<typeof(*begin)> src(begin, end);

    for (; begin != end; ++begin) {
        *begin = src.top();
        src.pop();
    }
}

#endif //THINHEAP_SORT_H
