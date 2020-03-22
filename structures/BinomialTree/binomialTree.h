//
// Created by tarog on 3/23/2020.
//

#ifndef BINOMIALTREE_H
#define BINOMIALTREE_H

#include <memory>

template <typename T, class Cmp = std::less<T>>
class BinomialTree {

  private:

    T *base{nullptr};
    uint_fast64_t deg{};

  public:

    explicit BinomialTree(const T &elem) : base{new T{elem}}, deg{0} {}

    BinomialTree(BinomialTree &&lhs, BinomialTree &&rhs) {

        if (lhs.deg != rhs.deg)
            throw std::runtime_error("Can't build binomial tree on trees with different sizes");

        std::swap(this->base, lhs.base);
        this->deg = lhs.deg;

        this->merge(rhs);
    }

    BinomialTree(const BinomialTree &lhs, const BinomialTree &rhs) {
        if (lhs.deg != rhs.deg)
            throw std::runtime_error("Can't build binomial tree on trees with different sizes");

        this->base = new T[2 << lhs.deg];

        std::uninitialized_copy(lhs.base, lhs.base + 2 << lhs.deg, this->base);

        this->deg = lhs.deg;

        this->merge(rhs);
    }

    template <typename _Iter>
    BinomialTree(_Iter first, _Iter last) {

        int_fast64_t n = last - first;

        if (n & (n - 1))
            throw std::runtime_error("Can't build binomial tree on array with size " + std::to_string(n));

        if (n == 1) {
            base = new T[last - first];
            std::uninitialized_copy(first, last, base);
            deg = 0;
        }
        else {
            BinomialTree<T, Cmp> a(first, first + (last - first) / 2);
            BinomialTree<T, Cmp> b(first + (last - first) / 2, last);

            std::swap(this->base, a.base);
            std::swap(this->deg, a.deg);

            this->merge(b);
        }
    }

    void merge(const BinomialTree &tree) {

        if (this->deg != tree.deg)
            throw std::runtime_error("Can't merge with the tree with different size");

        Cmp cmp{};

        auto tmp = new T [2 * (2 << this->deg)];

        auto copy = tree.base;

        if (!cmp(this->base[0], copy[0])) {
            std::swap(this->base, copy);
        }

        uint_fast64_t  t{1};

        uint_fast64_t counter{0};

        for (auto i = 0; i <= this->deg; ++i) {

            for (auto j = t / 2; j < t; ++j)
                tmp[counter++] = this->base[j];

            for (auto j = t / 2; j < t; ++j)
                tmp[counter++] = copy[j];

            t <<= 1;
        }

        std::swap(tmp, this->base);
        ++this->deg;
    }

    const T &top() const {
        return base[0];
    }

    uint_fast64_t degree() const {
        return deg;
    }
};

#endif //BINOMIALTREE_H
