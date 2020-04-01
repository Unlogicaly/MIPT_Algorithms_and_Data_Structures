//
// Created by tarog on 4/1/2020.
//

#ifndef UNTITLED3_BINARYLTREE_H
#define UNTITLED3_BINARYLTREE_H

#include "node.h"
#include "deleter.h"
#include <memory>
#include <cassert>

template <typename T, class _Cmp = std::less<>>
class BinaryTree {

  private:

    T key{};

    Node<T> *root{nullptr};

    _Cmp cmp{};

    Node<T> *_first(Node<T> *root);

  public:

    BinaryTree() = default;

    explicit BinaryTree(const T &elem) : root(std::make_unique<Node<T>>(elem).release()), key{elem} {}

    template <class _Iter>
    BinaryTree(_Iter begin, _Iter end);

    void insert(const T &elem);

    bool del(const T &elem);

    const T &first();

    bool empty() {
        return !(this->root);
    }

    void del_first();

    ~BinaryTree() {

        delete root;
    }
};

template <typename T, class _Cmp>
void BinaryTree<T, _Cmp>::insert(const T &elem) {

    auto cur = this->root;

    if (!cur) {

        this->key = elem;

        this->root = std::make_unique<Node<T>>(elem).release();
        return;
    }

    this->key = std::min(key, elem);

    auto prev = cur;

    while (cur) {

        prev = cur;

        cur = (cmp(cur->val, elem) ? cur->right : cur->left);
    }

    cur = std::make_unique<Node<T>>(elem).release();
    cur->parent = prev;
    (cmp(prev->val, elem) ? prev->right : prev->left) = cur;
}

template <typename T, class _Cmp>
template <class _Iter>
BinaryTree<T, _Cmp>::BinaryTree(_Iter begin, _Iter end) {

    for (; begin != end; ++begin) {
        this->insert(*begin);
    }
}

template <typename T, class _Cmp>
Node<T> *BinaryTree<T, _Cmp>::_first(Node<T> *root) {

    if (!root)
        return root;

    while (root->left) {
        root = root->left;
    }

    return root;
}

template <typename T, class _Cmp>
const T &BinaryTree<T, _Cmp>::first() {

    return key;
}

template <typename T, class _Cmp>
bool BinaryTree<T, _Cmp>::del(const T &elem) {

    if (!this->root)
        return false;

    auto cur = this->root;

    while (cur->val != elem) {

        cur = (cmp(cur->val, elem) ? cur->right : cur->left);

        if (!cur)
            return false;
    }

    if (!cur->right and !cur->left) {

        (cur->parent ? cmp(cur->parent->val, cur->val) ? cur->parent->right : cur->parent->left : this->root) = nullptr;

        deleter<Node<T>>{cur};
    }

    else if (cur->left and cur->right) {
        auto tmp = this->_first(cur->right);

        cur->val = tmp->val;

        (tmp->parent == cur ? tmp->parent->right : tmp->parent->left) = tmp->right;

        if (tmp->right)
            tmp->right->parent = tmp->parent;

        tmp->right = nullptr;

        deleter<Node<T>>{tmp};
    }
    else {

        auto tmp = (cur->left ? cur->left : cur->right);

        cur->val = tmp->val;

        cur->left = tmp->left;

        if (tmp->left)
            tmp->left->parent = cur;

        cur->right = tmp->right;

        if (tmp->right)
            tmp->right->parent = cur;

        tmp->left = nullptr;
        tmp->right = nullptr;

        deleter<Node<T>>{tmp};
    }

    if (elem == key and this->root)
        key = this->_first(this->root)->val;

    return true;
}

template <typename T, class _Cmp>
void BinaryTree<T, _Cmp>::del_first() {

    this->del(key);
}


#endif //UNTITLED3_BINARYLTREE_H
