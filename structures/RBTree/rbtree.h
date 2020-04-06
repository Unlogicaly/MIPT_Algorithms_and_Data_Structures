//
// Created by tarog on 4/6/2020.
//

#ifndef UNTITLED8_RBTREE_H
#define UNTITLED8_RBTREE_H

#include "service_funcs.h"
#include "deleter.h"
#include <memory>

template <typename T, class _Cmp = std::less<>>
class RBTree {

  private:
    Node<T> *root{nullptr};

    _Cmp cmp{};

    T key{};

    void left_rotation(Node<T> *node);

    void right_rotation(Node<T> *node);

    void big_left_rotation(Node<T> *node);

    void big_right_rotation(Node<T> *node);

    void back_propagation_del(Node<T> *node);

    void back_propagation_ins(Node<T> *node);

    Node<T> *find_first(Node<T> *root);

    void del_node(Node<T> *node);

  public:
    RBTree() = default;

    explicit RBTree(const T &elem) : root(std::make_unique<Node<T>>(elem).release()), key{elem} {}

    template <typename _Iter>
    RBTree(_Iter begin, _Iter end) {

        for (; begin != end; ++begin)
            this->insert(*begin);
    }

    void insert(const T &elem);

    void del(const T &elem);

    const T &first() {

        return this->key;
    }

    void del_first() {

        this->del(key);
    }

    bool empty() {

        return !this->root;
    }

    ~RBTree() {

        delete this->root;
    }
};

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::left_rotation(Node<T> *node) {

    auto b = node->right;
    std::swap(node->val, b->val);

    node->right = b->right;
    if (node->right)
        node->right->parent = node;

    b->right = b->left;

    if (node->left)
        node->left->parent = b;

    b->left = node->left;
    node->left = b;
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::right_rotation(Node<T> *node) {

    auto b = node->left;
    std::swap(node->val, b->val);

    node->left = b->left;
    if (node->left)
        node->left->parent = node;

    b->left = b->right;

    if (node->right)
        node->right->parent = b;

    b->right = node->right;
    node->right = b;
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::big_left_rotation(Node<T> *node) {

    right_rotation(node->right);
    left_rotation(node);
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::big_right_rotation(Node<T> *node) {

    left_rotation(node->left);
    right_rotation(node);
}

template <typename T>
void repaint(Node<T> *node) {

    father(node)->black = true;
    uncle(node)->black = true;
    gr_father(node)->black = false;
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::back_propagation_ins(Node<T> *node) {

    for (; !black(father(node)) and !black(node); node = gr_father(node)) {

        if (!black(uncle(node))) {
            repaint(node);
            continue;
        }

        if (father(node)->left == node) {
            if (gr_father(node)->left == father(node))
                right_rotation(gr_father(node));
            else
                big_left_rotation(gr_father(node));
        }
        else {
            if (gr_father(node)->right == father(node))
                left_rotation(gr_father(node));
            else
                big_right_rotation(gr_father(node));
        }
    }

    this->root->black = true;
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::insert(const T &elem) {

    if (!this->root) {
        this->root = std::make_unique<Node<T>>(elem).release();
        this->root->black = true;

        this->key = elem;

        return;
    }

    this->key = std::min(this->key, elem, this->cmp);

    auto cur = this->root;
    auto prev = cur;

    while (cur) {

        prev = cur;
        cur = (this->cmp(cur->val, elem) ? cur->right : cur->left);
    }

    cur = std::make_unique<Node<T>>(elem).release();
    cur->parent = prev;

    (this->cmp(prev->val, elem) ? prev->right : prev->left) = cur;

    back_propagation_ins(cur);
}

template <typename T, class _Cmp>
Node<T> *RBTree<T, _Cmp>::find_first(Node<T> *root) {

    for (; root->left; root = root->left);

    return root;
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::back_propagation_del(Node<T> *node) {

    while (node != this->root) {
        if (!black(brother(node))) {
            (node == father(node)->left) ? this->left_rotation(father(node)) : this->right_rotation(father(node));
            continue;
        }

        auto br = brother(node);

        if (black(br->left) and black(br->right)) {

            br->black = false;

            if (black(father(node))) {
                node = father(node);
                continue;
            }

            father(node)->black = true;
            break;
        }

        if (father(node)->left == node) {
            if (!black(br->left))
                this->right_rotation(br);
            else {
                this->left_rotation(father(node));
                gr_father(node)->right->black = true;
                break;
            }
        }

        else {
            if (!black(br->right))
                this->left_rotation(br);
            else {
                this->right_rotation(father(node));
                gr_father(node)->left->black = true;
                break;
            }
        }
    }

    this->root->black = true;
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::del_node(Node<T> *node) {

    if (!node->left and !node->right) {

        if (node == this->root) {
            deleter<Node<T>>{node};
            this->root = nullptr;
            return;
        }

        if (black(node))
            back_propagation_del(node);

        (father(node)->left == node ? father(node)->left : father(node)->right) = nullptr;

        deleter<Node<T>>{node};
    }

    else {

        auto tmp = (node->right ? node->right : node->left);
        node->val = tmp->val;
        node->left = nullptr;
        node->right = nullptr;
        deleter<Node<T>>{tmp};
    }
}

template <typename T, class _Cmp>
void RBTree<T, _Cmp>::del(const T &elem) {

    auto cur = this->root;

    while (cur->val != elem) {

        cur = (this->cmp(cur->val, elem) ? cur->right : cur->left);
    }

    if (cur->left and cur->right) {

        auto tmp = cur->right;

        while (tmp->left) {

            tmp = tmp->left;
        }

        cur->val = tmp->val;
        cur = tmp;
    }

    del_node(cur);

    if (this->root and this->key == elem)
        this->key = this->find_first(this->root)->val;
}


#endif //UNTITLED8_RBTREE_H
