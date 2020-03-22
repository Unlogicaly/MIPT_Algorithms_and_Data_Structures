//
// Created by tarog on 3/19/2020.
//

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "heap.h"

template<typename T, class Cmp = std::less<T>>
void _heap_sort(std::vector<T> &array, size_t left, size_t right, Cmp cmp={}){
    Heap<T, Cmp> tmp;

    for (auto i = left; i < right; ++i) {
        tmp.add(array[i]);
    }

    for (auto i = left; i < right; ++i) {
        array[i] = tmp.top();
        tmp.pop();
    }
}

template<typename T, class Cmp = std::less<T>>
void heap_sort(std::vector<T> &array, Cmp cmp={}) {
    if (array.size() <= 1)
        return;
    _heap_sort(array, 0, array.size(), cmp);
}

#endif //HEAP_SORT_H
