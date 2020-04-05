//
// Created by tarog on 4/5/2020.
//

#ifndef UNTITLED6_AVL_SORT_H
#define UNTITLED6_AVL_SORT_H

#include "avltree.h"

template<typename _Iter, class _Cmp = std::less<>>
void avl_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    AVLTree<typeof(*begin), _Cmp> avl(begin, end);

    for (; begin != end; ++begin) {

        *begin = avl.first();
        avl.del_first();
    }
}

template<typename _Iter>
void avl_sort(_Iter begin, _Iter end) {

    AVLTree<typeof(*begin)> avl(begin, end);

    for (; begin != end; ++begin) {

        *begin = avl.first();
        avl.del_first();
    }
}

#endif //UNTITLED6_AVL_SORT_H
