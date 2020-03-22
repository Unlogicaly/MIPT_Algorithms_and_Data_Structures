//
// Created by tarog on 3/19/2020.
//

#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include <vector>
#include <algorithm>

template <typename T, class Cmp = std::less<T>>
void _insert_sort(std::vector<T> &array, size_t left, size_t right, Cmp cmp = {}) {

    for (auto i = left; i < right; ++i) {
        auto pos = std::lower_bound(array.begin() + left, array.begin() + i, array[i], cmp) - array.begin();
        auto tmp = array[i];
        memcpy(array.data() + pos + 1, array.data() + pos, (i - pos ) * sizeof(T));
        array[pos] = tmp;
    }
}

template <typename T, class Cmp = std::less<T>>
void insert_sort(std::vector<T> &array, Cmp cmp = {}) {

    _insert_sort<T, Cmp>(array, 0, array.size());
}

#endif //INSERT_SORT_H
