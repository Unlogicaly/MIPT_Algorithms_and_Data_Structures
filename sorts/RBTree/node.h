//
// Created by tarog on 4/6/2020.
//

#ifndef UNTITLED8_NODE_H
#define UNTITLED8_NODE_H

template <typename T>
struct Node {

    T val{};

    bool black{false};

    Node<T> *parent{nullptr};

    Node<T> *left{nullptr};

    Node<T> *right{nullptr};

    Node() = delete;

    explicit Node(const T &elem) : val{elem} {}

    ~Node() {

        delete left;
        delete right;
    }
};


#endif //UNTITLED8_NODE_H
