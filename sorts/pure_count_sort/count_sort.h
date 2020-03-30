//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_COUNT_SORT_H
#define UNTITLED_COUNT_SORT_H

template<typename _Iter>
void count_sort(_Iter begin, _Iter end) {

    auto max = *begin;
    for (auto iter = begin; iter != end; ++iter)
        max = std::max(max, *iter);

    ++max;

    auto src = new decltype(max) [max];
    for (auto i = 0; i < max; ++i)
        src[i] = 0;

    for (auto iter = begin; iter != end; ++iter)
        ++src[*iter];

    uint_fast64_t sum{0};

    for (auto i = 0; i < max; ++i) {
        auto tmp = src[i];
        src[i] = sum;
        sum += tmp;
    }

    auto tmp = new decltype(max) [end - begin];

    for (auto iter = begin; iter != end; ++iter)
        tmp[src[*iter]++] = *iter;

    for(auto i = 0; i < end - begin; ++i)
        *(begin + i) = *(tmp + i);

    delete[] src;
    delete[] tmp;
}

#endif //UNTITLED_COUNT_SORT_H
