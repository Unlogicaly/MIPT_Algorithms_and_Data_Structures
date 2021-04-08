#include <iostream>
#include <vector>
#include <algorithm>

template <typename _Iter, class _Cmp = std::less<>>
inline void insert_sort(_Iter begin, _Iter end, _Cmp cmp = {}){

    for (auto cur = begin; cur != end; ++cur) {
        auto pos = cur;
        --pos;

        while (pos >= begin and cmp(*cur, *pos))
            --pos;

        ++pos;
        for (auto j = cur; j != pos; --j)
            std::swap(*j, *(j - 1));
    }
}

struct cmp {

    bool operator()(const std::vector<int> &lhs, const std::vector<int> &rhs) {

        return (lhs[0] <= rhs[0] and lhs[1] <= rhs[1] and lhs[2] <= rhs[2]);
    }
};

int main(){

    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a;

    for (auto i = 0; i < n; ++i) {
        std::vector<int> tmp(4);

        for (auto j = 0; j < 3; ++j)
            std::cin >> tmp[j];

        insert_sort(tmp.begin(), tmp.end());

        tmp[3] = i;

        a.push_back(tmp);
    }

    insert_sort(a.begin(), a.end(), cmp{});

    for (auto i: a) {
        std::cout << i.back() << " ";
    }
}