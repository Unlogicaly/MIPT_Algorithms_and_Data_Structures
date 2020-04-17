//
// Created by tarog on 3/28/2020.
//

#ifndef LEFTISTHEAP_LEFTISTHEAP_H
#define LEFTISTHEAP_LEFTISTHEAP_H

#include "node.h"
#include <list>
#include <functional>

namespace leftist {
    template <typename T>
    struct heap_base {

        leftist::Node<T> *root{nullptr};

        heap_base() = default;

        explicit heap_base(const T &elem) : root{new leftist::Node<T>{elem}} {
        }

        explicit heap_base(leftist::Node<T> *other) : root{other ? new leftist::Node<T>{*other} : nullptr} {
        }

        heap_base(const leftist::heap_base<T> &other) : root{other.root ? new leftist::Node<T>{*other.root} : nullptr} {
        }

        leftist::heap_base<T> &operator=(const leftist::heap_base<T> &other) {

            this->root = new leftist::Node<T>{*other.root};

            return *this;
        }

        ~heap_base() {

            delete root;
        }
    };
}

template <typename T, class _Cmp = std::less<T>>
class LeftistHeap : leftist::heap_base<T> {

  private:

    _Cmp cmp{};

    leftist::heap_base<T> merge(leftist::heap_base<T> lhs, leftist::heap_base<T> rhs);

  public:
    LeftistHeap() = default;

    explicit LeftistHeap(const T &elem) : leftist::heap_base<T>(elem) {
    }

    LeftistHeap(const LeftistHeap<T, _Cmp> &other) : leftist::heap_base<T>(other.root), cmp{other.cmp} {
    }

    LeftistHeap(LeftistHeap<T, _Cmp> &&other) noexcept {

        std::swap(this->root, other.root);
        std::swap(this->cmp, other.cmp);
    }

    template <class _Iter>
    LeftistHeap(_Iter begin, _Iter end);

    void push(const T &elem);

    void pop();

    const T &top();

    void merge(const LeftistHeap<T, _Cmp> &other);

    bool empty() {

        return this->root == nullptr;
    }
};

template <typename T, class _Cmp>
void LeftistHeap<T, _Cmp>::merge(const LeftistHeap<T, _Cmp> &other) {

    auto tmp{merge(leftist::heap_base<T>{this->root}, leftist::heap_base<T>{other.root})};
    std::swap(this->root, tmp.root);
}

template <typename T, class _Cmp>
leftist::heap_base<T> LeftistHeap<T, _Cmp>::merge(leftist::heap_base<T> lhs, leftist::heap_base<T> rhs) {

    if (!lhs.root)
        return rhs;

    if (!rhs.root)
        return lhs;

    if (!cmp(lhs.root->val, rhs.root->val))
        std::swap(lhs.root, rhs.root);

    auto tmp{merge(leftist::heap_base<T>{lhs.root->right}, leftist::heap_base<T>{rhs.root})};

    std::swap(lhs.root->right, tmp.root);

    if (!lhs.root->left or lhs.root->right->rk > lhs.root->left->rk)
        std::swap(lhs.root->left, lhs.root->right);

    lhs.root->update_rank();

    return lhs;
}

template <typename T, class _Cmp>
void LeftistHeap<T, _Cmp>::push(const T &elem) {

    merge(LeftistHeap<T, _Cmp>{elem});
}

template <typename T, class _Cmp>
void LeftistHeap<T, _Cmp>::pop() {

    auto tmp{merge(leftist::heap_base<T>{this->root->left}, leftist::heap_base<T>{this->root->right})};
    std::swap(this->root, tmp.root);
}

template <typename T, class _Cmp>
const T &LeftistHeap<T, _Cmp>::top() {

    return this->root->val;
}

template <typename T, class _Cmp>
template <class _Iter>
LeftistHeap<T, _Cmp>::LeftistHeap(_Iter begin, _Iter end) {

    if (begin == end)
        return;

    std::list<leftist::heap_base<T>> tmp;

    for (auto iter = begin; iter != end; ++iter)
        tmp.push_back(leftist::heap_base<T>{*iter});

    auto second = tmp.begin();
    ++second;

    while (tmp.size() != 1) {

        *tmp.begin() = merge(*tmp.begin(), *second);
        tmp.push_back(tmp.front());

        tmp.pop_front();
        tmp.pop_front();
        second = tmp.begin();
        ++second;
    }

    std::swap(this->root, tmp.front().root);
}

#endif //LEFTISTHEAP_LEFTISTHEAP_H
