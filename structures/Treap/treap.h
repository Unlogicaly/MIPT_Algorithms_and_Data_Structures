//
// Created by tarog on 4/1/2020.
//

#ifndef UNTITLED3_TREAP_H
#define UNTITLED3_TREAP_H

#include "node.h"
#include "deleter.h"
#include <memory>
#include <cassert>

template <typename K, typename P, class _k_cmp = std::less<K>, class _p_cmp = std::less<P>>
class Treap {

  private:

    K fst{};

    Node<K, P> *root{nullptr};

    _k_cmp k_cmp{};

    _p_cmp p_cmp{};

    std::pair<Node<K, P> *, Node<K, P> *> _split(Node<K, P> *root, K key);

    Node<K, P> *_merge(Node<K, P> *lhs, Node<K, P> *rhs);

    Node<K, P> *_first(Node<K, P> *root);

    uint_fast64_t _depth(Node<K, P> *root) {

        return (root ? std::max(_depth(root->left), _depth(root->right)) + 1 : 0);
    }

  public:

    Treap() = default;

    explicit Treap(const std::pair<K, P> elem) : root{std::make_unique<Node<K, P>>(elem).release()}, fst{elem.first} {}

    template <typename _Iter>
    Treap(_Iter begin, _Iter end);

    void insert(const std::pair<K, P> &elem);

    void del(const K &key);

    const K &first() {

        return fst;
    }

    void del_first();

    uint_fast64_t depth();

    ~Treap() {

        delete this->root;
    }
};

template <typename K, typename P, class _k_cmp, class _p_cmp>
std::pair<Node<K, P> *, Node<K, P> *> Treap<K, P, _k_cmp, _p_cmp>::_split(Node<K, P> *root, K key) {

    if (!root)
        return {nullptr, nullptr};

    if (k_cmp(root->key, key)) {
        auto[node1, node2] = _split(root->right, key);
        root->right = node1;
        return {root, node2};
    }

    auto[node1, node2] = _split(root->left, key);
    root->left = node2;
    return {node1, root};
}

template <typename K, typename P, class _k_cmp, class _p_cmp>
Node<K, P> *Treap<K, P, _k_cmp, _p_cmp>::_merge(Node<K, P> *lhs, Node<K, P> *rhs) {

    if (!lhs)
        return rhs;

    if (!rhs)
        return lhs;

    if (p_cmp(rhs->priority, lhs->priority)) {
        rhs->left = this->_merge(lhs, rhs->left);
        return rhs;
    }

    lhs->right = this->_merge(lhs->right, rhs);
    return lhs;
}

template <typename K, typename P, class _k_cmp, class _p_cmp>
void Treap<K, P, _k_cmp, _p_cmp>::insert(const std::pair<K, P> &elem) {

    if (!this->root) {
        this->fst = elem.first;
        this->root = std::make_unique<Node<K, P>>(elem).release();
        return;
    }

    auto cur = this->root;
    auto prev = cur;

    this->fst = std::min(fst, elem.first, k_cmp);

    while (cur and !p_cmp(cur->priority, elem.second)) {

        prev = cur;
        cur = (k_cmp(elem.first, cur->key) ? cur->left : cur->right);
    }

    auto new_node = std::make_unique<Node<K, P>>(elem).release();

    auto [left, right] = this->_split(cur, elem.first);

    new_node->left = left;
    new_node->right = right;

    (prev == cur ? this->root : k_cmp(elem.first, prev->key) ? prev->left : prev->right) = new_node;
}

template <typename K, typename P, class _k_cmp, class _p_cmp>
void Treap<K, P, _k_cmp, _p_cmp>::del(const K &key) {

    assert(this->root);

    auto cur = this->root;
    auto prev = cur;

    while (cur and cur->key != key) {

        prev = cur;
        cur = (k_cmp(key, cur->key) ? cur->left : cur->right);
    }

    if (!cur)
        return;

    auto new_node = this->_merge(cur->left, cur->right);

    (prev->left == cur ? prev->left : prev == cur ? this->root : prev->right) = new_node;

    cur->left = nullptr;
    cur->right = nullptr;

    deleter<Node<K, P>>{cur};

    if (this->fst == key and this->root)
        this->fst = this->_first(this->root)->key;
}

template <typename K, typename P, class _k_cmp, class _p_cmp>
template <typename _Iter>
Treap<K, P, _k_cmp, _p_cmp>::Treap(_Iter begin, _Iter end) {

    for (; begin != end; ++begin)
        this->insert(*begin);
}

template <typename K, typename P, class _k_cmp, class _p_cmp>
Node<K, P> *Treap<K, P, _k_cmp, _p_cmp>::_first(Node<K, P> *root) {

    assert(root);

    while (root->left)
        root = root->left;

    return root;
}

template <typename K, typename P, class _k_cmp, class _p_cmp>
void Treap<K, P, _k_cmp, _p_cmp>::del_first() {

    this->del(this->fst);
}

template <typename K, typename P, class _k_cmp, class _p_cmp>
uint_fast64_t Treap<K, P, _k_cmp, _p_cmp>::depth() {

    return this->_depth(this->root);
}

#endif //UNTITLED3_TREAP_H
