//
// Created by tarog on 3/23/2020.
//

#ifndef BINOMIALTREE_H
#define BINOMIALTREE_H

#include <memory>
#include <cmath>

template <typename T, class A>
struct tree_base {

    A alloc;

    T *base;

    uint_fast64_t deg;

    tree_base(A a, uint_fast64_t degree) : alloc{a}, base{a.allocate(1 << degree)}, deg{degree} {}

    ~tree_base() {

        alloc.deallocate(base, 1 << deg);
    };
};

template <typename T, class _Cmp = std::less<T>, class A = std::allocator<T>>
class BinomialTree : private tree_base<T, A> {

  private:
    _Cmp cmp{};

    template <typename, class>
    friend
    class BinomialHeap;

  public:

    BinomialTree() : tree_base<T, A>({}, 0) {}

    explicit BinomialTree(const T &elem);

    BinomialTree(std::initializer_list<T> lst);

    template <typename _iter>
    BinomialTree(_iter begin, _iter end);

    BinomialTree(const BinomialTree<T, _Cmp, A> &other);

    BinomialTree(BinomialTree<T, _Cmp, A> &&other) noexcept;

    BinomialTree(const BinomialTree<T, _Cmp, A> &a, const BinomialTree<T, _Cmp, A> &b);

    const T &top() const;

    uint_fast64_t degree() const;

    void merge(const BinomialTree &other);

    BinomialTree<T, _Cmp, A> &operator=(const BinomialTree<T, _Cmp, A> &a);

    BinomialTree<T, _Cmp, A> &operator=(BinomialTree<T, _Cmp, A> &&a) noexcept;

    ~BinomialTree();
};

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A>::BinomialTree(const T &elem) : tree_base<T, A>({}, 0) {


    this->alloc.construct(this->base, elem);
}

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A>::BinomialTree(std::initializer_list<T> lst) :
        tree_base<T, A>({}, std::max(uint_fast64_t((std::log((lst.size()))) / std::log(2)), uint_fast64_t(1)) - 1) {


    auto n = lst.size();

    if (n & (n - 1))
        throw std::runtime_error("Can't build binomial tree on array with size " + n);

    if (n == 2) {

        this->alloc.construct(this->base, *lst.begin());

        BinomialTree<T, _Cmp, A> a(*(lst.begin() + 1));

        this->merge(a);
    }

    else {

        BinomialTree<T, _Cmp, A> a(lst.begin(), lst.begin() + (lst.end() - lst.begin()) / 2);
        BinomialTree<T, _Cmp, A> b(lst.begin() + (lst.end() - lst.begin()) / 2, lst.end());

        for (auto i = 0; i < n / 2; ++i)
            this->alloc.construct(this->base + i, *(a.base + i));

        this->deg = a.deg;

        this->merge(b);
    }
}

template <typename T, class _Cmp, class A>
template <typename _iter>
BinomialTree<T, _Cmp, A>::BinomialTree(_iter begin, _iter end) :
        tree_base<T, A>({}, std::max(uint_fast64_t((std::log((end - begin))) / std::log(2)), uint_fast64_t(1)) - 1) {


    auto n = end - begin;

    if (n & (n - 1))
        throw std::runtime_error("Can't build binomial tree on array with size " + n);

    if (n == 1)
        this->alloc.construct(this->base, *begin);

    else if (n == 2) {

        this->alloc.construct(this->base, *begin);

        BinomialTree<T, _Cmp, A> a(*(begin + 1));

        this->merge(a);
    }

    else {

        BinomialTree<T, _Cmp, A> a(begin, begin + n / 2);
        BinomialTree<T, _Cmp, A> b(begin + n / 2, end);

        for (auto i = 0; i < n / 2; ++i)
            this->alloc.construct(this->base + i, *(a.base + i));

        this->deg = a.deg;

        this->merge(b);
    }
}

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A>::BinomialTree(const BinomialTree<T, _Cmp, A> &other) :
        tree_base<T, A>(other.alloc, other.deg) {


    for (uint_fast64_t i = 0; i < (1 << this->deg); ++i)
        this->alloc.construct(this->base + i, *(other.base + i));
}

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A>::BinomialTree(BinomialTree<T, _Cmp, A> &&other) noexcept :
        tree_base<T, A>(other.alloc, other.deg) {


    this->base = other.base;

    other.base = nullptr;
    other.deg = 0;
}

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A>::BinomialTree(const BinomialTree<T, _Cmp, A> &a, const BinomialTree<T, _Cmp, A> &b) :
        tree_base<T, A>(a.alloc, a.deg) {

    for (uint_fast64_t i = 0; i < (1 << this->deg); ++i)
        this->alloc.construct(this->base + i, *(a.base + i));

    this->merge(b);
}

template <typename T, class _Cmp, class A>
const T &BinomialTree<T, _Cmp, A>::top() const {


    return *this->base;
}

template <typename T, class _Cmp, class A>
uint_fast64_t BinomialTree<T, _Cmp, A>::degree() const {


    return this->deg;
}

template <typename T, class _Cmp, class A>
void BinomialTree<T, _Cmp, A>::merge(const BinomialTree &other) {


    if (this->deg != other.deg)
        throw std::runtime_error("Can't merge with the tree with different size");

    tree_base<T, A> tmp(this->alloc, this->deg + 1);

    tree_base<T, A> cpy(other.alloc, other.deg);

    for (uint_fast64_t i = 0; i < (1 << other.deg); ++i)
        cpy.alloc.construct(cpy.base + i, *(other.base + i));

    if (!cmp(this->base[0], cpy.base[0]))
        std::swap(this->base, cpy.base);

    uint_fast64_t t{1};
    uint_fast64_t counter{0};

    for (uint_fast64_t i = 0; i <= this->deg; ++i, t <<= 1) {

        for (auto j = t / 2; j < t; ++j, ++counter)
            tmp.alloc.construct(tmp.base + counter, *(this->base + j));

        for (auto j = t / 2; j < t; ++j, ++counter)
            tmp.alloc.construct(tmp.base + counter, *(cpy.base + j));
    }

    std::swap(this->base, tmp.base);
    std::swap(this->deg, tmp.deg);
}

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A> &BinomialTree<T, _Cmp, A>::operator=(const BinomialTree<T, _Cmp, A> &a) {


    if (this == &a)
        return *this;

    tree_base<T, A> tmp(a.alloc, a.deg);

    for (auto i = 0; i < (1 << a.deg); ++i)
        tmp.alloc.construct(tmp.base + i, *(a.base + i));

    std::swap(this->base, tmp.base);
    std::swap(this->deg, tmp.deg);

    return *this;
}

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A> &BinomialTree<T, _Cmp, A>::operator=(BinomialTree<T, _Cmp, A> &&a) noexcept {


    std::swap(this->base, a.base);
    std::swap(this->deg, a.deg);

    return *this;
}

template <typename T, class _Cmp, class A>
BinomialTree<T, _Cmp, A>::~BinomialTree() {


    for (uint_fast64_t i = 0; i < (1 << this->deg); ++i)
        this->alloc.destroy(this->base + i);
}

#endif //UNTITLED3_BINOMIALTREE_H
