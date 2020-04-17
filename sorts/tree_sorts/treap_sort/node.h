//
// Created by tarog on 4/1/2020.
//

#ifndef UNTITLED3_NODE_H
#define UNTITLED3_NODE_H

#include <utility>

template <typename K, typename P>
struct Node {

    K key{};

    P priority{};

    Node<K, P> *left{nullptr};

    Node<K, P> *right{nullptr};

    Node(const K &key, const P &priority) : key{key}, priority{priority} {}

    explicit Node(const std::pair<K, P> &elem) : key{elem.first}, priority{elem.second} {}

    ~Node() {

        delete left;
        delete right;
    }
};

#endif //UNTITLED3_NODE_H
