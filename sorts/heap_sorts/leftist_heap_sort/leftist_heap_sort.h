//
// Created by tarog on 4/17/2020.
//

#ifndef UNTITLED_LEFTIST_HEAP_SORT_H
#define UNTITLED_LEFTIST_HEAP_SORT_H

#include "leftistHeap.h"

template <typename _Iter, class _Cmp>
void leftist_heap_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    LeftistHeap<typeof(*begin), _Cmp> tree(begin, end);

    for (; begin != end; ++begin) {
        *begin = tree.top();
        tree.pop();
    }
}

template <typename _Iter>
void leftist_heap_sort(_Iter begin, _Iter end) {

    LeftistHeap<typeof(*begin)> tree(begin, end);

    for (; begin != end; ++begin) {
        *begin = tree.top();
        tree.pop();
    }
}

#endif //UNTITLED_LEFTIST_HEAP_SORT_H
