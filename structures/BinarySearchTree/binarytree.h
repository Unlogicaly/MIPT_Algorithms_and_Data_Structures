//
// Created by tarog on 4/1/2020.
//

#ifndef UNTITLED3_BINARYLTREE_H
#define UNTITLED3_BINARYLTREE_H

#include "node.h"
#include "deleter.h"
#include <memory>
#include <cassert>
#include <queue>

template <typename T, class _Cmp = std::less<>>
class BinomialTree {

  private:

    T key{};

    Node<T> *root{nullptr};

    _Cmp cmp{};

    Node<T> *_first(Node<T> *root);

  public:

    BinomialTree() = default;

    explicit BinomialTree(const T &elem) : root(std::make_unique<Node<T>>(elem).release()), key{elem} {}

    template <class _Iter>
    BinomialTree(_Iter begin, _Iter end);

    void insert(const T &elem);

    bool del(const T &elem);

    const T &first();

    bool empty() {
        return !(this->root);
    }

    void del_first();

    void in_order(std::ostream &os);

    void post_order(std::ostream &os);

    void pre_order(std::ostream &os);

    void level_order(std::ostream &os);

    ~BinomialTree() {

        delete root;
    }
};

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::insert(const T &elem) {

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
BinomialTree<T, _Cmp>::BinomialTree(_Iter begin, _Iter end) {

    for (; begin != end; ++begin) {
        this->insert(*begin);
    }
}

template <typename T, class _Cmp>
Node<T> *BinomialTree<T, _Cmp>::_first(Node<T> *root) {

    if (!root)
        return root;

    while (root->left) {
        root = root->left;
    }

    return root;
}

template <typename T, class _Cmp>
const T &BinomialTree<T, _Cmp>::first() {

    return key;
}

template <typename T, class _Cmp>
bool BinomialTree<T, _Cmp>::del(const T &elem) {

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
void BinomialTree<T, _Cmp>::del_first() {

    this->del(key);
}

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::in_order(std::ostream &os) {

    if (!root)
        return;

    auto cur = root;

    while (cur) {

        if (cur->left and !cur->left->visited)
            cur = cur->left;

        else if (!cur->right) {
            os << cur->val << ' ';
            cur->visited = true;

            if (cur->left)
                cur->left->visited = false;

            cur = cur->parent;
        }

        else if (cur->right->visited) {
            cur->right->visited = false;

            if (cur->left)
                cur->left->visited = false;

            cur = cur->parent;
        }

        else {
            cur->visited = true;
            os << cur->val << ' ';
            cur = cur->right;
        }
    }

    this->root->visited = false;
}

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::post_order(std::ostream &os) {

    if (!root)
        return;

    auto cur = root;

    while (cur) {

        if (cur->left and !cur->left->visited)
            cur = cur->left;

        else if (!cur->right) {
            os << cur->val << ' ';
            cur->visited = true;

            if (cur->left)
                cur->left->visited = false;

            cur = cur->parent;
        }

        else if (cur->right->visited) {
            cur->right->visited = false;
            cur->visited = true;
            if (cur->left)
                cur->left->visited = false;

            os << cur->val << ' ';

            cur = cur->parent;
        }

        else {
            cur = cur->right;
        }
    }

    this->root->visited = false;
}

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::pre_order(std::ostream &os) {

    if (!root)
        return;

    auto cur = root;

    while (cur) {

        if (cur->left and !cur->left->visited) {
            os << cur->val << ' ';
            cur = cur->left;
        }

        else if (!cur->right) {
            if (!cur->left)
                os << cur->val << ' ';
            cur->visited = true;

            if (cur->left)
                cur->left->visited = false;

            cur = cur->parent;
        }

        else if (cur->right->visited) {
            cur->right->visited = false;

            if (cur->left)
                cur->left->visited = false;

            cur = cur->parent;
        }

        else {
            if (!cur->left)
                os << cur->val << ' ';
            cur->visited = true;
            cur = cur->right;
        }
    }

    this->root->visited = false;
}

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::level_order(std::ostream &os) {

    std::queue<Node<T> *> buffer{};

    buffer.push(this->root);

    while (!buffer.empty()) {

        if (buffer.front()->left)
            buffer.push(buffer.front()->left);
        if (buffer.front()->right)
            buffer.push(buffer.front()->right);

        os << buffer.front()->val << ' ';

        buffer.pop();
    }
}


#endif //UNTITLED3_BINARYLTREE_H
