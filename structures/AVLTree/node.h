//
// Created by tarog on 4/3/2020.
//

#ifndef UNTITLED3_NODE_H
#define UNTITLED3_NODE_H

template <typename T>
struct Node {

    T val{};

    short diff{0};

    Node<T> *left{nullptr};
    Node<T> *right{nullptr};

    explicit Node(const T &elem) : val{elem} {}

    ~Node() {
        delete left;
        delete right;
    }
};

#endif //UNTITLED3_NODE_H
