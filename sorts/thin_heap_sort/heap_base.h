//
// Created by tarog on 3/29/2020.
//

#ifndef THINHEAP_HEAP_BASE_H
#define THINHEAP_HEAP_BASE_H

#include <memory>
#include "node.h"

template <typename T>
struct heap_base {

    Node<T> *first{nullptr};

    Node<T> *last{nullptr};

    heap_base() : first{nullptr}, last{nullptr} {};

    ~heap_base() {

        delete first;
    }
};


#endif //THINHEAP_HEAP_BASE_H
