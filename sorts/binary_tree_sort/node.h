//
// Created by tarog on 4/1/2020.
//

#ifndef UNTITLED3_NODE_H
#define UNTITLED3_NODE_H

template <typename T>
struct Node {

    T val{};

    Node<T> *parent{nullptr};

    Node<T> *left{nullptr};

    Node<T> *right{nullptr};

    explicit Node(const T &elem) : val{elem} {}

    ~Node() {

        delete left;
        delete right;
    }
};

#endif //UNTITLED3_NODE_H
