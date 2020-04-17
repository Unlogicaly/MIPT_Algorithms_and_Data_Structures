//
// Created by tarog on 4/17/2020.
//

#ifndef UNTITLED_RBTREE_SORT_H
#define UNTITLED_RBTREE_SORT_H

#include "rbtree.h"

template<typename _Iter, class _Cmp>
void rbtree_sort(_Iter begin, _Iter end, _Cmp = {}) {

    RBTree<typeof(*begin), _Cmp> tree(begin, end);

    tree.in_order(begin);
}

template<typename _Iter>
void rbtree_sort(_Iter begin, _Iter end) {

    RBTree<typeof(*begin)> tree(begin, end);

    tree.in_order(begin);
}

#endif //UNTITLED_RBTREE_SORT_H
