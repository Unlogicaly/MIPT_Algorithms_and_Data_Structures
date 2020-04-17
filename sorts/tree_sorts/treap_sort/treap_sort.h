//
// Created by tarog on 4/17/2020.
//

#ifndef UNTITLED_TREAP_SORT_H
#define UNTITLED_TREAP_SORT_H

#include "treap.h"
#include <random>
#include <algorithm>

template <typename _Iter, class _Cmp>
void treap_sort(_Iter begin, _Iter end, _Cmp) {

    std::random_device d;

    std::vector<uint_fast64_t> y(end - begin);
    for (uint_fast64_t i = 0; i < end - begin; ++i)
        y[i] = i;

    std::shuffle(y.begin(), y.end(), d);

    Treap<typeof(*begin), uint_fast64_t, _Cmp> treap{};

    auto cur = begin;

    for (uint_fast64_t i{0}; cur != end; ++i, ++cur) {

        treap.insert({*cur, y[i]});
    }

    treap.in_order(begin);
}

template <typename _Iter>
void treap_sort(_Iter begin, _Iter end) {

    std::random_device d;

    std::vector<uint_fast64_t> y(end - begin);
    for (uint_fast64_t i = 0; i < end - begin; ++i)
        y[i] = i;

    std::shuffle(y.begin(), y.end(), d);

    Treap<typeof(*begin), uint_fast64_t > treap{};

    auto cur = begin;

    for (uint_fast64_t i{0}; cur != end; ++i, ++cur) {

        treap.insert({*cur, y[i]});
    }

    for (;begin != end; ++begin) {

        *begin = treap.first();
        treap.del_first();
    }
}

#endif //UNTITLED_TREAP_SORT_H
