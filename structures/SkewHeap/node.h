//
// Created by tarog on 3/28/2020.
//

#ifndef SKEWHEAP_NODE_H
#define SKEWHEAP_NODE_H

#include <cstdint>

namespace skew {

    template <typename T>
    struct Node {

        T val;

        int_fast64_t rk{0};

        skew::Node<T> *left{nullptr};

        skew::Node<T> *right{nullptr};

        void update_rank() {

            if (this->left and this->right)
                this->rk = std::min(this->left->rk, this->right->rk) + 1;
        }


        explicit Node(const T &val) : val{val} {}

        explicit Node(T &&val) noexcept {

            std::swap(this->val, val);
        }

        Node(const skew::Node<T> &other);

        T &value() {

            return val;
        }

        skew::Node<T> &operator=(const skew::Node<T> &other);

        void add_left(skew::Node<T> *left) {

            this->left = left;

            update_rank();
        }

        void add_right(skew::Node<T> *right) {

            this->right = right;

            update_rank();
        }

        ~Node() {

            delete left;
            delete right;
        }
    };

    template <typename T>
    Node<T>::Node(const skew::Node<T> &other) {

        this->val = other.val;
        this->rk = other.rk;

        this->left = (other.left ? new skew::Node<T>{*other.left} : nullptr);
        this->right = (other.right ? new skew::Node<T>{*other.right} : nullptr);
    }

    template <typename T>
    skew::Node<T> &Node<T>::operator=(const skew::Node<T> &other) {

        this->val = other.val;
        this->rk = other.rk;

        this->left = (other.left ? new skew::Node<T>{*other.left} : nullptr);
        this->right = (other.right ? new skew::Node<T>{*other.right} : nullptr);

        return *this;
    }
}

#endif //SKEWHEAP_NODE_H
