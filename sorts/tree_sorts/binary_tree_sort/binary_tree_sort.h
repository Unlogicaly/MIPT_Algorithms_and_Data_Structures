//
// Created by tarog on 4/17/2020.
//

#ifndef UNTITLED_BIN_TREE_SORT_H
#define UNTITLED_BIN_TREE_SORT_H

#include "binarytree.h"

template<typename _Iter, class _Cmp>
void binary_tree_sort(_Iter begin, _Iter end, _Cmp) {

    BinaryTree<typeof(*begin), _Cmp> tree(begin, end);

    tree.in_order(begin);
}

template<typename _Iter>
void binary_tree_sort(_Iter begin, _Iter end) {

    BinaryTree<typeof(*begin)> tree(begin, end);

    tree.in_order(begin);
}

#endif //UNTITLED_BIN_TREE_SORT_H
