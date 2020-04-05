//
// Created by tarog on 4/3/2020.
//

#ifndef UNTITLED3_AVLTREE_H
#define UNTITLED3_AVLTREE_H

#include "node.h"
#include "deleter.h"
#include <functional>
#include <stack>
#include <memory>

template <typename T, class _Cmp = std::less<>>
class AVLTree {
  private:

    Node<T> *root{nullptr};

    _Cmp cmp{};

    T key{};

    void small_left_rotation(Node<T> *node, bool balance = true);

    void small_right_rotation(Node<T> *node, bool balance = true);

    void big_left_rotation(Node<T> *node);

    void big_right_rotation(Node<T> *node);

    Node<T> *_first(Node<T> *root);

    Node<T> *_find_node(std::stack<Node<T> *> &path, const T &elem, Node<T> *root);

    void replace(Node<T> *lhs, Node<T> *rhs);

    void del_node(std::stack<Node<T> *> &path, Node<T> *node, T &prev_val);

    void back_propagation_del(std::stack<Node<T> *> path, T &prev_val);

    void back_propagation_ins(std::stack<Node<T> *> path, T &prev_val);

  public:
    AVLTree() = default;

    explicit AVLTree(const T &elem) : root{std::make_unique<Node<T>>(elem).release()}, key{elem} {}

    template <class _Iter>
    AVLTree(_Iter begin, _Iter end);

    void insert(const T &elem);

    bool del(const T &elem);

    const T &first();

    void del_first();

    bool empty();

    ~AVLTree() {

        delete this->root;
    }
};

template <typename T, class _Cmp>
Node<T> *AVLTree<T, _Cmp>::_find_node(std::stack<Node<T> *> &path, const T &elem, Node<T> *_root) {

    auto cur = _root;

    while (cur and cur->val != elem) {

        path.push(cur);

        cur = (cmp(cur->val, elem) ? cur->right : cur->left);
    }

    return cur;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::replace(Node<T> *lhs, Node<T> *rhs) {

    lhs->val = rhs->val;
    lhs->diff = rhs->diff;
    lhs->left = rhs->left;
    rhs->left = nullptr;
    lhs->right = rhs->right;
    rhs->right = nullptr;

    deleter<Node<T>>{rhs};
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::del_node(std::stack<Node<T> *> &path, Node<T> *node, T &prev_val) {

    if (!node->right and !node->left) {

        (!path.empty() ? cmp(path.top()->val, node->val) ? path.top()->right : path.top()->left : this->root) = nullptr;

        deleter<Node<T>>{node};
    }

    else if (node->left and node->right) {

        path.push(node);

        auto tmp = node->right;
        while (tmp->left) {

            path.push(tmp);
            tmp = tmp->left;
        }

        prev_val = tmp->val;

        if (!tmp->right) {
            (cmp(path.top()->val, tmp->val) ? path.top()->right : path.top()->left) = nullptr;

            deleter<Node<T>>{tmp};
        }
        else {
            node->val = tmp->val;

            replace(node, node->right);
        }
    }
    else {

        auto tmp = (node->left ? node->left : node->right);

        replace(node, tmp);
    }
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::small_left_rotation(Node<T> *node, bool balance) {

    auto b = node->right;
    std::swap(node->val, b->val);
    node->right = b->right;
    b->right = b->left;
    auto t_node = node->left;
    node->left = b;
    b->left = t_node;

    if (balance) {
        node->diff = static_cast<short>(-(b->diff + 1));
        b->diff = static_cast<short>(std::abs(node->diff));
    }
    std::swap(node->diff, b->diff);
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::small_right_rotation(Node<T> *node, bool balance) {

    auto b = node->left;
    std::swap(node->val, b->val);
    node->left = b->left;
    b->left = b->right;
    auto t_node = node->right;
    node->right = b;
    b->right = t_node;

    if (balance) {
        node->diff = static_cast<short>(std::abs(b->diff - 1));
        b->diff = static_cast<short>(b->diff - 1);
    }
    std::swap(node->diff, b->diff);
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::big_left_rotation(Node<T> *node) {

    auto b = node->right;

    small_right_rotation(b, false);
    small_left_rotation(node, false);

    switch (node->diff) {
        case 0:
            node->right->diff = 0;
            b->diff = 0;
            break;
        case 1:
            node->right->diff = -1;
            b->diff = 0;
            break;
        case -1:
            node->right->diff = 0;
            b->diff = 1;
    }
    node->diff = 0;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::big_right_rotation(Node<T> *node) {

    auto b = node->left;

    small_left_rotation(b, false);
    small_right_rotation(node, false);

    switch (node->diff) {
        case 0:
            node->left->diff = 0;
            b->diff = 0;
            break;
        case 1:
            node->left->diff = 0;
            b->diff = -1;
            break;
        case -1:
            node->left->diff = 1;
            b->diff = 0;
            break;
    }
    node->diff = 0;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::back_propagation_del(std::stack<Node<T> *> path, T &prev_val) {

    while (!path.empty()) {

        auto root = path.top();
        path.pop();
        cmp(root->val, prev_val) ? ++root->diff : --root->diff;
        prev_val = root->val;

        if (!root->diff)
            continue;

        if (root->diff == 1 or root->diff == -1)
            break;

        if (root->diff == -2) {
            if (root->right->diff == 1)
                big_left_rotation(root);
            else
                small_left_rotation(root);
        }
        else {
            if (root->left->diff == -1)
                big_right_rotation(root);
            else
                small_right_rotation(root);
        }

        if (root->diff == 1 or root->diff == -1)
            break;
    }
}

template <typename T, class _Cmp>
bool AVLTree<T, _Cmp>::del(const T &elem) {

    if (!this->root)
        return false;

    std::stack<Node<T> *> path{};

    auto cur = _find_node(path, elem, this->root);

    if (!cur)
        return false;

    T prev_val{elem};

    del_node(path, cur, prev_val);

    back_propagation_del(path, prev_val);

    if (this->root and this->key == elem) {
        this->key = this->_first(this->root)->val;
    }

    return true;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::back_propagation_ins(std::stack<Node<T> *> path, T &prev_val) {

    while (!path.empty()) {

        auto root = path.top();
        path.pop();
        cmp(root->val, prev_val) ? --root->diff : ++root->diff;
        prev_val = root->val;

        if (!root->diff)
            break;

        if (root->diff == 1 or root->diff == -1)
            continue;

        if (root->diff == -2) {
            if (root->right->diff == 1)
                big_left_rotation(root);
            else
                small_left_rotation(root);
        }
        else {
            if (root->left->diff == -1)
                big_right_rotation(root);
            else
                small_right_rotation(root);
        }

        if (!root->diff)
            break;
    }
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::insert(const T &elem) {

    auto cur = this->root;

    if (!cur) {

        this->key = elem;

        this->root = std::make_unique<Node<T>>(elem).release();
        return;
    }

    this->key = std::min(key, elem, cmp);

    std::stack<Node<T> *> path{};

    _find_node(path, elem, this->root);

    cur = std::make_unique<Node<T>>(elem).release();

    (cmp(path.top()->val, elem) ? path.top()->right : path.top()->left) = cur;

    T prev_val{cur->val};

    back_propagation_ins(path, prev_val);
}

template <typename T, class _Cmp>
const T &AVLTree<T, _Cmp>::first() {

    return this->key;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::del_first() {

    this->del(this->key);
}

template <typename T, class _Cmp>
bool AVLTree<T, _Cmp>::empty() {

    return !this->root;
}

template <typename T, class _Cmp>
template <class _Iter>
AVLTree<T, _Cmp>::AVLTree(_Iter begin, _Iter end) {

    for (; begin != end; ++begin)
        this->insert(*begin);
}

template <typename T, class _Cmp>
Node<T> *AVLTree<T, _Cmp>::_first(Node<T> *root) {

    while (root->left)
        root = root->left;

    return root;
}


#endif //UNTITLED3_AVLTREE_H
