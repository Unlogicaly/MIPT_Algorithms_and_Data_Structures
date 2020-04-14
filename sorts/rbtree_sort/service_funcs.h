//
// Created by tarog on 4/6/2020.
//

#ifndef UNTITLED8_SERVICE_FUNCS_H
#define UNTITLED8_SERVICE_FUNCS_H

#include "node.h"

template <typename T>
bool black(Node<T> *node) {

    return !node or node->black;
}

template <typename T>
Node<T> *father(Node<T> *node) {

    return node ? node->parent : node;
}

template <typename T>
Node<T> *brother(Node<T> *node) {

    return (father(node) ? father(node)->left == node ? father(node)->right : father(node)->left : nullptr);
}

template <typename T>
Node<T> *uncle(Node<T> *node) {

    return brother(father(node));
}

template <typename T>
Node<T> *gr_father(Node<T> *node) {

    return (father(node) ? father(father(node)) : nullptr);
}

#endif //UNTITLED8_SERVICE_FUNCS_H
