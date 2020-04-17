//
// Created by tarog on 3/28/2020.
//

#ifndef SKEWHEAP_H
#define SKEWHEAP_H

#include "node.h"
#include <list>
#include <functional>

namespace skew {

    template <typename T>
    int_fast32_t rank(skew::Node<T> *src) {

        return (src ? std::min(rank(src->left), rank(src->right)) + 1 : -1);
    }

    template <typename T>
    struct heap_base {

        skew::Node<T> *root{nullptr};

        heap_base() = default;

        explicit heap_base(const T &elem) : root{new skew::Node<T>{elem}} {
        }

        explicit heap_base(skew::Node<T> *other) : root{other ? new skew::Node<T>{*other} : nullptr} {
        }

        heap_base(const skew::heap_base<T> &other) : root{other.root ? new skew::Node<T>{*other.root} : nullptr} {
        }

        skew::heap_base<T> &operator=(const skew::heap_base<T> &other) {

            this->root = new skew::Node<T>{*other.root};

            return *this;
        }

        ~heap_base() {

            delete root;
        }
    };
}
template <typename T, class _Cmp = std::less<T>>
class SkewHeap : skew::heap_base<T> {

  private:

    _Cmp cmp{};

    skew::heap_base<T> merge(skew::heap_base<T> lhs, skew::heap_base<T> rhs);

  public:
    SkewHeap() = default;

    explicit SkewHeap(const T &elem) : skew::heap_base<T>(elem) {
    }

    SkewHeap(const SkewHeap<T, _Cmp> &other) : skew::heap_base<T>(other.root), cmp{other.cmp} {
    }

    SkewHeap(SkewHeap<T, _Cmp> &&other) noexcept {

        std::swap(this->root, other.root);
        std::swap(this->cmp, other.cmp);
    }

    template <class _Iter>
    SkewHeap(_Iter begin, _Iter end);

    void push(const T &elem);

    void pop();

    const T &top();

    void merge(const SkewHeap<T, _Cmp> &other);

    bool empty() {

        return this->root == nullptr;
    }
};

template <typename T, class _Cmp>
void SkewHeap<T, _Cmp>::merge(const SkewHeap<T, _Cmp> &other) {

    auto tmp{merge(skew::heap_base<T>{this->root}, skew::heap_base<T>{other.root})};
    std::swap(this->root, tmp.root);
}

template <typename T, class _Cmp>
skew::heap_base<T> SkewHeap<T, _Cmp>::merge(skew::heap_base<T> lhs, skew::heap_base<T> rhs) {

    if (!lhs.root)
        return rhs;

    if (!rhs.root)
        return lhs;

    if (!cmp(lhs.root->val, rhs.root->val))
        std::swap(lhs.root, rhs.root);

    auto tmp{merge(skew::heap_base<T>{lhs.root->right}, skew::heap_base<T>{rhs.root})};

    std::swap(lhs.root->right, tmp.root);

    std::swap(lhs.root->left, lhs.root->right);

    lhs.root->update_rank();

    return lhs;
}

template <typename T, class _Cmp>
void SkewHeap<T, _Cmp>::push(const T &elem) {

    merge(SkewHeap<T, _Cmp>{elem});
}

template <typename T, class _Cmp>
void SkewHeap<T, _Cmp>::pop() {

    auto tmp{merge(skew::heap_base<T>{this->root->left}, skew::heap_base<T>{this->root->right})};
    std::swap(this->root, tmp.root);
}

template <typename T, class _Cmp>
const T &SkewHeap<T, _Cmp>::top() {

    return this->root->val;
}

template <typename T, class _Cmp>
template <class _Iter>
SkewHeap<T, _Cmp>::SkewHeap(_Iter begin, _Iter end) {

    if (begin == end)
        return;

    std::list<skew::heap_base<T>> tmp;

    for (auto iter = begin; iter != end; ++iter)
        tmp.push_back(skew::heap_base<T>{*iter});

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

#endif //SKEWHEAP_H
