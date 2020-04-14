//
// Created by tarog on 4/6/2020.
//

#ifndef UNTITLED8_RBTREE_SORT_H
#define UNTITLED8_RBTREE_SORT_H

#include "rbtree.h"

template<typename _Iter, class _Cmp>
void rbtree_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    RBTree<typeof(*begin), _Cmp> rbTree(begin, end);

    for (; !rbTree.empty(); ++begin) {
        *begin = rbTree.first();
        rbTree.del_first();
    }
}

template<typename _Iter>
void rbtree_sort(_Iter begin, _Iter end) {

    RBTree<typeof(*begin)> rbTree(begin, end);

    for (; !rbTree.empty(); ++begin) {
        *begin = rbTree.first();
        rbTree.del_first();
    }
}

#endif //UNTITLED8_RBTREE_SORT_H
