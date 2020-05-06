//
// Created by tarog on 04.05.2020.
//

#ifndef SPLAYTREE_SPLAYTREE_H
#define SPLAYTREE_SPLAYTREE_H


#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

template <typename T>
class SplayTree {

  private:

    struct Node {

        T val{};

        Node *parent{nullptr};
        Node *left{nullptr};
        Node *right{nullptr};

        Node() = default;

        explicit Node(const T &elem, Node *parent = nullptr) : val{elem}, parent{parent} {}

        ~Node() {

            delete left;
            delete right;
        }
    };

    Node *merge(Node *lhs, Node *rhs);

    std::pair<Node *, Node *> split(const T &key);

    Node *left_zig(Node *node);
    Node *right_zig(Node *node);

    Node *left_zig_zig(Node *node);
    Node *right_zig_zig(Node *node);

    Node *left_zig_zag(Node *node);
    Node *right_zig_zag(Node *node);

    Node *zig(Node *node);

    void splay(Node *node);

    Node *last(Node *sub_root) {
        while (sub_root->right)
            sub_root = sub_root->right;

        return sub_root;
    }

    template<typename Iter>
    void _in_order(Iter iter, Node *cur);

    Node *root{nullptr};

  public:

    SplayTree() = default;

    explicit SplayTree(const T &elem);

    template <typename Iter>
    SplayTree(Iter begin, Iter end);

    const T &first();

    bool del(const T &elem);

    void del_first() {

        del(first());
    }

    void insert(const T &elem);

    bool empty() {
        return !this->root;
    }

    template <typename Iter>
    void in_order(Iter begin);

    ~SplayTree() {

        delete root;
    }
};

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::left_zig(SplayTree::Node *node) {

    auto a = node->parent;

    std::swap(a->val, node->val);

    a->right = node->right;
    if (a->right)
        a->right->parent = a;

    node->right = node->left;

    if (a->left)
        a->left->parent = node;

    node->left = a->left;
    a->left = node;

    return a;
}

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::right_zig(SplayTree::Node *node) {

    auto a = node->parent;

    std::swap(a->val, node->val);

    a->left = node->left;
    if (a->left)
        a->left->parent = a;

    node->left = node->right;

    if (a->right)
        a->right->parent = node;

    node->right = a->right;
    a->right = node;

    return a;
}

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::left_zig_zig(SplayTree::Node *node) {

    left_zig(node->parent);
    left_zig(node);

    return node->parent;
}

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::right_zig_zig(SplayTree::Node *node) {

    right_zig(node->parent);
    right_zig(node);

    return node->parent;
}

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::left_zig_zag(SplayTree::Node *node) {

    right_zig(node);
    left_zig(node->parent);

    return node->parent;
}

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::right_zig_zag(SplayTree::Node *node) {

    left_zig(node);
    right_zig(node->parent);

    return node->parent;
}

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::zig(SplayTree::Node *node) {

    if (!node->parent)
        return nullptr;

    return node->parent->left == node ? !node->parent->parent ? right_zig(node) :
                                        node->parent->parent->left == node->parent ? right_zig_zig(node) :
                                        left_zig_zag(node) : !node->parent->parent ? left_zig(node) :
                                                             node->parent->parent->left == node->parent ? right_zig_zag(node): left_zig_zig(node);
}

template <typename T>
void SplayTree<T>::splay(SplayTree::Node *node) {

    while (node) {
        node = zig(node);
    }
}

template <typename T>
typename SplayTree<T>::Node *SplayTree<T>::merge(SplayTree::Node *lhs, SplayTree::Node *rhs) {

    if (!rhs) {

        if (lhs)
            lhs->parent = nullptr;

        return lhs;
    }
    if (!lhs) {

        rhs->parent = nullptr;
        return rhs;
    }

    auto res = last(lhs);

    this->root = lhs;

    splay(res);

    this->root->right = rhs;

    this->root->parent = nullptr;

    return this->root;
}

template <typename T>
std::pair<typename SplayTree<T>::Node *, typename SplayTree<T>::Node *> SplayTree<T>::split(const T &key) {

    auto cur = this->root, prev = this->root;

    while (cur and cur->val != key) {

        prev = cur;

        cur = (cur->val < key ? cur->right : cur->left);
    }

    if (!cur)
        cur = prev;

    splay(cur);

    auto l = root->left, r = root->right;

    if (root->val < key) {

        if (root->right)
            root->right->parent = nullptr;

        root->right = nullptr;
        l = root;
    }
    else {

        if (root->left)
            root->left->parent = nullptr;

        root->left = nullptr;
        r = root;
    }

    return {l, r};
}

template <typename T>
SplayTree<T>::SplayTree(const T &elem) : root{std::make_unique<typename SplayTree<T>::Node>(elem).release()} {
}

template <typename T>
const T &SplayTree<T>::first() {

    assert(this->root);

    auto cur = this->root;

    while(cur->left)
        cur = cur->left;

    return cur->val;
}

template <typename T>
bool SplayTree<T>::del(const T &elem) {

    assert(this->root);

    auto cur = this->root;

    while (cur->val != elem) {

        cur = (cur->val < elem ? cur->right : cur->left);

        if (!cur)
            return false;
    }

    splay(cur);

    auto res = merge(cur->left, cur->right);

    cur->left = nullptr;
    cur->right = nullptr;

    delete cur;

    this->root = res;

    return true;
}

template <typename T>
void SplayTree<T>::insert(const T &elem) {

    if (!this->root) {

        this->root = std::make_unique<typename SplayTree<T>::Node>(elem).release();
        return;
    }

    auto [l, r] = this->split(elem);

    auto res = std::make_unique<typename SplayTree<T>::Node>(elem).release();

    res->left = l;
    if (l)
        l->parent = res;

    res->right = r;
    if (r)
        r->parent = res;

    this->root = res;
}

template <typename T>
template <typename Iter>
SplayTree<T>::SplayTree(Iter begin, Iter end) {

    for (; begin != end; ++begin)
        this->insert(*begin);
}

template <typename T>
template <typename Iter>
void SplayTree<T>::in_order(Iter begin) {

    if (!this->root)
        return;

    _in_order(&begin, this->root);
}

template <typename T>
template <typename Iter>
void SplayTree<T>::_in_order(Iter iter, typename SplayTree<T>::Node *cur) {

    if (cur->left)
        _in_order(iter, cur->left);

    **iter = cur->val;
    ++(*iter);

    if (cur->right)
        _in_order(iter, cur->right);
}


#endif //SPLAYTREE_SPLAYTREE_H
