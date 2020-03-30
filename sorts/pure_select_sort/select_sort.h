//
// Created by tarog on 3/19/2020.
//

#ifndef SELECT_SORT_H
#define SELECT_SORT_H

template<typename _Iter, class _Cmp>
void select_sort(_Iter begin, _Iter end, _Cmp cmp = {}){

    for (auto iter = begin; iter != end - 1; ++iter) {
        auto pos = iter;
        for (auto iter1 = pos + 1; iter1 != end; ++iter1) {
            if (cmp(*iter1, *pos))
                pos = iter1;
        }
        std::swap(*iter, *pos);
    }
}

template<typename _Iter>
void select_sort(_Iter begin, _Iter end){

    for (auto iter = begin; iter != end - 1; ++iter) {
        auto pos = iter;
        for (auto iter1 = pos + 1; iter1 != end; ++iter1) {
            if (*iter1 < *pos)
                pos = iter1;
        }
        std::swap(*iter, *pos);
    }
}

#endif //SELECT_SORT_H
