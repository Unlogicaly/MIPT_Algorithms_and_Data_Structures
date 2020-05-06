//
// Created by tarog on 04.05.2020.
//

#ifndef SPLAYTREE_SPLAY_TREE_SORT_H
#define SPLAYTREE_SPLAY_TREE_SORT_H

#include "splayTree.h"

template <typename Iter>
void splay_tree_sort(Iter begin, Iter end) {

    SplayTree<typeof(*begin)> tree(begin, end);

    tree.in_order(begin);
}

#endif //SPLAYTREE_SPLAY_TREE_SORT_H
