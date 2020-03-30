//
// Created by tarog on 3/29/2020.
//

#ifndef THINHEAP_NODE_H
#define THINHEAP_NODE_H

#include <cinttypes>
#include <memory>

template <typename T>
struct Node {

    T val{};
    uint_fast64_t rk{0};

    Node<T> *child{nullptr};
    Node<T> *left{nullptr};
    Node<T> *right{nullptr};

    bool rec{true};

    Node() = default;

    explicit Node(const T &elem) : val{elem} {}

    ~Node() {

        if (rec) {
            delete child;
            delete right;
        }
    }
};


#endif //THINHEAP_NODE_H
