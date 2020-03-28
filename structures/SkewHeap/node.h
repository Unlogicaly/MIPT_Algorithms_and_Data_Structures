//
// Created by tarog on 3/28/2020.
//

#ifndef SKEWHEAP_H
#define SKEWHEAP_H

#include <cstdint>

template <typename T>
class Node {

  private:
    T val;

    int_fast64_t rk{0};

    Node<T> *left{nullptr};

    Node<T> *right{nullptr};

    void update_rank() {
        if (this->left and this->right)
            this->rk = std::min(this->left->rk, this->right->rk) + 1;

    }

    template <typename, class>
    friend class LeftistHeap;

  public:

    explicit Node(const T &val) : val{val} {}

    explicit Node(T &&val) noexcept {
        std::swap(this->val, val);
    }

    Node (const Node<T> &other);

    T &value() {
        return val;
    }

    Node<T> &operator = (const Node<T> &other);

    void add_left(Node<T> *left) {

        this->left = left;

        update_rank();
    }

    void add_right(Node<T> *right) {

        this->right= right;

        update_rank();
    }

    ~Node() {

        delete left;
        delete right;
    }
};

template <typename T>
Node<T>::Node(const Node<T> &other) {

    this->val = other.val;
    this->rk = other.rk;

    this->left = (other.left ? new Node<T>{*other.left} : nullptr);
    this->right = (other.right ? new Node<T>{*other.right} : nullptr);
}

template <typename T>
Node<T> &Node<T>::operator=(const Node<T> &other) {

    this->val = other.val;
    this->rk = other.rk;

    this->left = (other.left ? new Node<T>{*other.left} : nullptr);
    this->right = (other.right ? new Node<T>{*other.right} : nullptr);

    return *this;
}

#endif //SKEWHEAP_H
