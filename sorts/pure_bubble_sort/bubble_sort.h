//
// Created by tarog on 3/19/2020.
//

#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

template <typename _Iter, class _Cmp>
void bubble_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    --end;

    auto last = end;

    for (auto iter1 = begin; iter1 != end; ++iter1, --last) {
        bool sorted = true;
        for (auto iter2 = begin; iter2 != last; ++iter2) {
            if (!cmp(*iter2, *(iter2 + 1))) {
                sorted = false;
                std::swap(*iter2, *(iter2 + 1));
            }
        }

        if (sorted)
            break;
    }
}

template <typename _Iter>
void bubble_sort(_Iter begin, _Iter end) {

    --end;

    auto last = end;

    for (auto iter1 = begin; iter1 != end; ++iter1, --last) {
        bool sorted = true;
        for (auto iter2 = begin; iter2 != last; ++iter2) {
            if (*(iter2 + 1) < *iter2) {
                sorted = false;
                std::swap(*iter2, *(iter2 + 1));
            }
        }

        if (sorted)
            break;
    }
}

#endif //BUBBLE_SORT_H
