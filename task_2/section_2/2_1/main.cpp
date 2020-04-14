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

template <typename _Iter, class _Cmp>
inline _Iter pivot(_Iter begin, _Iter end, _Cmp cmp = {}) {

    --end;
    auto mid = begin + ((end - begin) >> 2);
    auto a = *begin, b = *mid, c = *end;

    return cmp(a, b) ? cmp(b, c) ? mid : cmp(a, c) ? end : begin :cmp(a, c) ? begin : cmp(b, c) ? end : mid;
}

template <typename _Iter, class _Cmp>
inline _Iter partition(_Iter begin, _Iter end, _Cmp cmp = {}) {

    _Iter p = pivot(begin, end, cmp);

    auto pivot = *p;

    std::swap(*p, *(end - 1));
    --end;

    auto i = begin, j = end - 1;

    while (i < j) {
        while (i != end and cmp(*i, pivot))
            ++i;
        while (j != begin and !cmp(*j, pivot))
            --j;

        if (i < j)
            std::swap(*i, *j);
    }

    std::swap(*end, *i);

    return i;
}

template <typename _Iter, class _Cmp>
inline void quick_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    while (end - begin > 16) {
        _Iter p_ind = partition<_Iter, _Cmp>(begin, end);
        if (p_ind - begin < end - p_ind + 1) {
            quick_sort(begin, p_ind, cmp);
            begin = p_ind + 1;
        }
        else {
            quick_sort(p_ind + 1, end, cmp);
            end = p_ind;
        }
    }
    insert_sort(begin, end, cmp);
}

struct client {
    int enter;
    int quit;
    int ads_shown;
};

std::istream &operator>>(std::istream &is, client &p1) {

    p1.ads_shown = 0;
    return is >> p1.enter >> p1.quit;
}

std::ostream &operator<<(std::ostream &os, client &p1) {

    return os << p1.enter << ' ' << p1.quit << " " << p1.ads_shown;
}

struct cmp {
    bool operator()(const client &lhs, const client &rhs) {

        return lhs.quit < rhs.quit ? true : lhs.quit == rhs.quit and lhs.enter > rhs.enter;
    }
};

int main() {

    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<client> a(static_cast<unsigned long long int>(n));

    for (auto i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    quick_sort(a.begin(), a.end(), cmp{});

    auto res = 0;

    for (auto i = 0; i < a.size(); ++i) {

        if (a[i].ads_shown == 0) {
            for (auto j = i - 1; ++j < a.size() and a[i].quit > a[j].enter;){
                ++a[j].ads_shown;
            }
            ++res;
        }

        if (a[i].ads_shown == 1) {
            for (auto j = i - 1; ++j < a.size() and a[i].quit >= a[j].enter;){
                ++a[j].ads_shown;
            }
            ++res;
        }
    }

    std::cout << res;

    return 0;
}