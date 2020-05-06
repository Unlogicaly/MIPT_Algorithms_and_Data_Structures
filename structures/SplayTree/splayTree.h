//
// Created by tarog on 04.05.2020.
//

#ifndef SPLAYTREE_SPLAYTREE_H
#define SPLAYTREE_SPLAYTREE_H

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

template <typename T, class Cmp = std::less<>>
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

    // Для сортировки
    template<typename Iter>
    void _in_order(Iter iter, Node *cur);

    Node *root{nullptr};

    Cmp cmp{};

  public:

    SplayTree() = default;

    explicit SplayTree(const Cmp &cmp) : SplayTree() {
        this->cmp = cmp;
    }

    explicit SplayTree(const T &elem, const Cmp &cmp = {});

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

    bool contain(const T &elem);

    const T &top() {

        assert(this->root);

        return this->root->val;
    }

    // Для сортировки
    template <typename Iter>
    void in_order(Iter begin);

    ~SplayTree() {

        delete root;
    }
};

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::left_zig(SplayTree::Node *node) {

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

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::right_zig(SplayTree::Node *node) {

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

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::left_zig_zig(SplayTree::Node *node) {

    left_zig(node->parent);
    left_zig(node);

    return node->parent;
}

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::right_zig_zig(SplayTree::Node *node) {

    right_zig(node->parent);
    right_zig(node);

    return node->parent;
}

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::left_zig_zag(SplayTree::Node *node) {

    right_zig(node);
    left_zig(node->parent);

    return node->parent;
}

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::right_zig_zag(SplayTree::Node *node) {

    left_zig(node);
    right_zig(node->parent);

    return node->parent;
}

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::zig(SplayTree::Node *node) {

    if (!node->parent)
        return nullptr;

    return node->parent->left == node ? !node->parent->parent ? right_zig(node) :
                                        node->parent->parent->left == node->parent ? right_zig_zig(node) :
                                        left_zig_zag(node) : !node->parent->parent ? left_zig(node) :
                                                             node->parent->parent->left == node->parent ? right_zig_zag(node): left_zig_zig(node);
}

template <typename T, class Cmp>
void SplayTree<T, Cmp>::splay(SplayTree::Node *node) {

    while (node) {
        node = zig(node);
    }
}

template <typename T, class Cmp>
typename SplayTree<T, Cmp>::Node *SplayTree<T, Cmp>::merge(SplayTree::Node *lhs, SplayTree::Node *rhs) {

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

template <typename T, class Cmp>
std::pair<typename SplayTree<T, Cmp>::Node *, typename SplayTree<T, Cmp>::Node *> SplayTree<T, Cmp>::split(const T &key) {

    auto cur = this->root, prev = this->root;

    while (cur and cur->val != key) {

        prev = cur;

        cur = (cmp(cur->val, key) ? cur->right : cur->left);
    }

    if (!cur)
        cur = prev;

    splay(cur);

    auto l = root->left, r = root->right;

    if (cmp(root->val, key)) {

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

template <typename T, class Cmp>
SplayTree<T, Cmp>::SplayTree(const T &elem, const Cmp &cmp) : root{std::make_unique<typename SplayTree<T, Cmp>::Node>(elem).release()}, cmp{cmp} {
}

template <typename T, class Cmp>
const T &SplayTree<T, Cmp>::first() {

    assert(this->root);

    auto cur = this->root;

    while(cur->left)
        cur = cur->left;

    splay(cur);

    return root->val;
}

template <typename T, class Cmp>
bool SplayTree<T, Cmp>::del(const T &elem) {

    assert(this->root);

    auto cur = this->root;

    while (cur->val != elem) {

        cur = (cmp(cur->val, elem) ? cur->right : cur->left);

        if (!cur)
            return false;
    }

    splay(cur);

    auto res = merge(root->left, root->right);

    root->left = nullptr;
    root->right = nullptr;

    delete root;

    this->root = res;

    return true;
}

template <typename T, class Cmp>
void SplayTree<T, Cmp>::insert(const T &elem) {

    if (!this->root) {

        this->root = std::make_unique<typename SplayTree<T, Cmp>::Node>(elem).release();
        return;
    }

    auto [l, r] = this->split(elem);

    auto res = std::make_unique<typename SplayTree<T, Cmp>::Node>(elem).release();

    res->left = l;
    if (l)
        l->parent = res;

    res->right = r;
    if (r)
        r->parent = res;

    this->root = res;
}

template <typename T, class Cmp>
template <typename Iter>
SplayTree<T, Cmp>::SplayTree(Iter begin, Iter end) {

    for (; begin != end; ++begin)
        this->insert(*begin);
}

template <typename T, class Cmp>
template <typename Iter>
void SplayTree<T, Cmp>::in_order(Iter begin) {

    if (!this->root)
        return;

    _in_order(&begin, this->root);
}

template <typename T, class Cmp>
template <typename Iter>
void SplayTree<T, Cmp>::_in_order(Iter iter, typename SplayTree<T, Cmp>::Node *cur) {

    if (cur->left)
        _in_order(iter, cur->left);

    **iter = cur->val;
    ++(*iter);

    if (cur->right)
        _in_order(iter, cur->right);
}

template <typename T, class Cmp>
bool SplayTree<T, Cmp>::contain(const T &elem) {

    auto cur = this->root;

    while (cur and cur->val != elem) {

        cur = (cmp(cur->val, elem) ? cur->right : cur->left);
    }

    if (cur) {

        splay(cur);
        return true;
    }

    return false;
}


#endif //SPLAYTREE_SPLAYTREE_H
