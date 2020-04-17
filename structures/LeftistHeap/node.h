//
// Created by tarog on 3/28/2020.
//

#ifndef LEFTISTHEAP_NODE_H
#define LEFTISTHEAP_NODE_H

#include <cstdint>

namespace leftist {
    template <typename T>
    struct Node {

        T val;

        int_fast64_t rk{0};

        leftist::Node<T> *left{nullptr};

        leftist::Node<T> *right{nullptr};

        void update_rank() {

            if (this->left and this->right)
                this->rk = std::min(this->left->rk, this->right->rk) + 1;
        }

        explicit Node(const T &val) : val{val} {}

        explicit Node(T &&val) noexcept {

            std::swap(this->val, val);
        }

        Node(const leftist::Node<T> &other);

        T &value() {

            return val;
        }

        leftist::Node<T> &operator=(const leftist::Node<T> &other);

        void add_left(leftist::Node<T> *left) {

            this->left = left;

            update_rank();
        }

        void add_right(leftist::Node<T> *right) {

            this->right = right;

            update_rank();
        }

        ~Node() {

            delete left;
            delete right;
        }
    };

    template <typename T>
    Node<T>::Node(const leftist::Node<T> &other) {

        this->val = other.val;
        this->rk = other.rk;

        this->left = (other.left ? new leftist::Node<T>{*other.left} : nullptr);
        this->right = (other.right ? new leftist::Node<T>{*other.right} : nullptr);
    }

    template <typename T>
    leftist::Node<T> &Node<T>::operator=(const leftist::Node<T> &other) {

        this->val = other.val;
        this->rk = other.rk;

        this->left = (other.left ? new leftist::Node<T>{*other.left} : nullptr);
        this->right = (other.right ? new leftist::Node<T>{*other.right} : nullptr);

        return *this;
    }
}

#endif //LEFTISTHEAP_NODE_H
