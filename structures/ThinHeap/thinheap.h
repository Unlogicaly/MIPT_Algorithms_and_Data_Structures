//
// Created by tarog on 3/29/2020.
//

#ifndef THINHEAP_THINHEAP_H
#define THINHEAP_THINHEAP_H

#include "heap_base.h"
#include <cmath>
#include <vector>

const double f{(1 + std::sqrt(5)) / 2};

template<typename T, class _Cmp = std::less<T>>
class ThinHeap : private heap_base<T> {

  private:

    _Cmp cmp{};

    uint_fast64_t n{0};

    void insert(Node<T> *node) {

        if (!this->first) {
            this->first = node;
            this->last = node;
        }
        else if (node->val < this->first->val) {
            node->right = this->first;
            this->first = node;
        }
        else {
            this->last->right = node;
            this->last = node;
        }
    }

    void copy_node(Node<T> *node) {

        if (!node)
            return;

        this->push(node->val);
        copy_node(node->child);
        copy_node(node->right);
    }

    bool is_thin(Node<T> *node) {

        return (node->rk ? node->rk == 1 ? !node->child : node->child->rk + 1 != node->rk : false);
    }

  public:

    explicit ThinHeap(const T &elem, _Cmp cmp = {}) : cmp{cmp} {

        this->push(elem);
    }

    explicit ThinHeap(_Cmp cmp = {}) : cmp{cmp} {}

    template <class _Iter>
    ThinHeap(_Iter begin, _Iter end);

    ThinHeap(const ThinHeap<T, _Cmp> &other);

    ThinHeap(ThinHeap<T, _Cmp> &&other) noexcept;

    void push(const T &elem);

    const T &top();

    void pop();

    bool empty() {
        return !this->n;
    }
};

template <typename T, class _Cmp>
void ThinHeap<T, _Cmp>::push(const T &elem) {

    auto tmp_ptr = std::make_unique<Node<T>>(elem);

    this->insert(tmp_ptr.release());
    ++n;
}

template <typename T, class _Cmp>
const T &ThinHeap<T, _Cmp>::top() {

    return this->first->val;
}

template <typename T, class _Cmp>
void ThinHeap<T, _Cmp>::pop() {

    std::unique_ptr<Node<T>> tmp{this->first};

    tmp->rec = false;

    this->first = this->first->right;

    if (!this->first)
        this->last = nullptr;

    auto x = tmp->child;

    Node<T> *next{nullptr};

    while (x) {
        if (is_thin(x))
            --x->rk;

        x->left = nullptr;
        next = x->right;
        x->right = nullptr;
        insert(x);
        x = next;
    }

    x = this->first;
    std::vector<Node<T> *> aux(uint_fast64_t(std::log(n)/std::log(f)) + 1, nullptr);

    while(x) {

        next = x->right;

        while(aux[x->rk]) {

//            if (x->right == aux[x->rk])
//                next = x->right->right;

            if (aux[x->rk]->val < x->val) {
                std::swap(aux[x->rk], x);
            }
            aux[x->rk]->right = x->child;
            if (x->child) {
                x->child->left = aux[x->rk];
            }
            aux[x->rk]->left = x;
            x->child = aux[x->rk];
            aux[x->rk] = nullptr;
            ++x->rk;
        }

        x->left = nullptr;
        x->right = nullptr;
        aux[x->rk] = x;
        x = next;
    }

    ThinHeap<T, _Cmp> new_heap{};
    for (auto i = 0; i < aux.size(); ++i) {
        if (aux[i]) {
            new_heap.insert(aux[i]);
        }
    }

    this->first = new_heap.first;
    new_heap.first = nullptr;

    this->last = new_heap.last;
    new_heap.last = nullptr;

    --n;
}

template <typename T, class _Cmp>
template <class _Iter>
ThinHeap<T, _Cmp>::ThinHeap(_Iter begin, _Iter end) {

    for (auto iter = begin; iter != end; ++iter) {

        this->push(*iter);
    }
}

template <typename T, class _Cmp>
ThinHeap<T, _Cmp>::ThinHeap(const ThinHeap<T, _Cmp> &other) : cmp{other.cmp} {

    copy_node(other.first);
}

template <typename T, class _Cmp>
ThinHeap<T, _Cmp>::ThinHeap(ThinHeap<T, _Cmp> &&other) noexcept {

    std::swap(this->first, other.first);
    std::swap(this->last, other.last);
    std::swap(this->n, other.n);
    std::swap(this->cmp, other.cmp);
}

#endif //THINHEAP_THINHEAP_H
