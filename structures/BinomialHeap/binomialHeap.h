//
// Created by tarog on 3/23/2020.
//

#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <vector>
#include "binomialTree.h"

template <typename T, class Cmp = std::less<T>>
class BinomialHeap {

  private:

    uint_fast64_t size{0};

    std::vector<BinomialTree<T, Cmp> *> base{};

    uint_fast64_t min{0};

    void search_min() {

        TRACE_FUNC;
        min = 0;

        for (uint_fast64_t i = 1; i < base.size(); ++i)
            if (!base[min] or (base[i] and base[i]->top() < base[min]->top()))
                min = i;
    }

    std::pair<BinomialTree<T, Cmp> *, BinomialTree<T, Cmp> *>
    _merge(BinomialTree<T, Cmp> *a, BinomialTree<T, Cmp> *b, BinomialTree<T, Cmp> *c) {

        TRACE_FUNC;

        std::pair<BinomialTree<T, Cmp> *, BinomialTree<T, Cmp> *> res{nullptr, nullptr};

        if ((a != nullptr) ^ (b != nullptr) ^ (c != nullptr)) {

            if (a and b and c) {
                return {new BinomialTree<T, Cmp>{*a, *b}, new BinomialTree<T, Cmp>(*c)};
            }

            res.second = new BinomialTree<T, Cmp>(*(a ? a : b ? b : c));
        }
        else {

            if (!a and !b and !c) {
                return res;
            }

            res.first = new BinomialTree<T, Cmp>{*(a ? a : b), *(c ? c : b)};
        }

        return res;
    }

  public:

    BinomialHeap() = default;

    explicit BinomialHeap(const T &elem) : size{1}, base{new BinomialTree<T, Cmp>(elem)}, min{0} {}

    BinomialHeap(const BinomialHeap<T, Cmp> &rhs) : size{rhs.size}, min{rhs.min}, base(rhs.base.size(), nullptr) {

        TRACE_FUNC;
        for (auto i = 0; i < rhs.base.size(); ++i) {

            if (rhs.base[i])
                base[i] = new BinomialTree<T, Cmp>(*rhs.base[i]);
        }
    }

    template <typename _Iter>
    BinomialHeap(_Iter begin, _Iter end) : size{uint_fast64_t(end - begin)} {

        TRACE_FUNC;

        if (!size)
            return;

        auto sz = this->size;

        uint_fast64_t max_deg{0};

        while (sz >= (1 << max_deg)) {
            ++max_deg;
        }

        base.resize(max_deg, nullptr);

        uint_fast64_t start{0};

        for (uint_fast64_t degree = 0; degree < max_deg; ++degree) {

            if (sz % 2) {

                base[degree] = new BinomialTree<T, Cmp>{begin + start, begin + start + (1 << degree)};

                if (start == 0 or !base[min] or base[degree]->top() < base[min]->top()) {
                    min = degree;
                }

                start += (1 << degree);
            }

            sz /= 2;
        }
    }

    const T &top() {

        TRACE_FUNC;
        return base[min]->top();
    }

    void pop() {

        TRACE_FUNC;
        if (this->empty())
            throw std::runtime_error("Can't delete element from empty heap");

        if (this->size == 1) {

            base.clear();
            --size;
            return;
        }

        if (!min) {

            delete base[min];
            base[min] = nullptr;
            search_min();
            --size;
            return;
        }

        BinomialHeap<T, Cmp> tmp(base[min]->base + 1, base[min]->base + (1 << base[min]->deg));

        size -= (1 << base[min]->deg);
        delete base[min];
        base[min] = nullptr;

        merge(tmp);
    }

    void add(const T &elem) {

        BinomialHeap<T, Cmp> tmp(elem);

        merge(tmp);
    }

    void merge(BinomialHeap<T, Cmp> &rhs) {

        TRACE_FUNC;

        if (this->empty()) {

            if (rhs.empty())
                return;

            this->size = rhs.size;
            this->min = rhs.min;

            base.clear();
            this->base.resize(rhs.base.size(), nullptr);

            for (auto i = 0; i < rhs.base.size(); ++i) {

                base[i] = rhs.base[i] ? new BinomialTree<T, Cmp>(*rhs.base[i]) : nullptr;
            }

            return;
        }

        this->size += rhs.size;

        auto t = std::max(base.size(), rhs.base.size()) + 1;

        base.resize(t, nullptr);

        BinomialTree<T, Cmp> *prev{nullptr};

        uint_fast64_t i = 0;
        for (; i < rhs.base.size(); ++i) {

            auto tmp = _merge(prev, base[i], rhs.base[i]);

            delete base[i];
            base[i] = tmp.second;

            delete prev;
            prev = tmp.first;
        }

        while (prev) {
            auto tmp = _merge(prev, base[i], nullptr);

            delete base[i];
            base[i] = tmp.second;

            delete prev;
            prev = tmp.first;

            ++i;
        }

        search_min();
    }

    ~BinomialHeap() {

        for (auto i = 0; i < base.size(); ++i)
            delete base[i];
    }

    bool empty() {

        return !size;
    }
};


#endif //BINOMIALHEAP_H
