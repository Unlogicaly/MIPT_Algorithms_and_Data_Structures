#include <iostream>
#include <vector>
#include <fstream>

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

struct segment {
    int start;
    int end;
    int overlapped{0};
};

std::istream &operator >> (std::istream &is, segment &s) {
    is >> s.start >> s.end;
    s.overlapped = s.start;
    return is;
}

std::ostream &operator << (std::ostream &os, segment &s) {
    return os << s.start << " " << s.end;
}

struct cmp {

    bool operator()(const segment &lhs, const segment &rhs) {
        return lhs.start < rhs.start;
    }
};

int main() {

    std::ifstream is("input.txt");
    std::ofstream os("output.txt");

    int n;
    is >> n;

    std::vector<segment> a(n);

    for (auto i = 0; i < n; ++i) {
        is >> a[i];
    }

    quick_sort(a.begin(), a.end(), cmp{});

    segment cur = a[0];
    cur.overlapped = cur.start;
    int len{0};

    for (auto i = 1; i < n; ++i) {
        if (a[i].start <= cur.end) {
            if (a[i].start - cur.overlapped > 0)
                len += (a[i].start - cur.overlapped);
            cur.overlapped = std::max(cur.overlapped, std::min(a[i].end, cur.end));
            cur.end = std::max(a[i].end, cur.end);
        }
        else {
            len += (cur.end - cur.overlapped);
            cur = a[i];
            cur.overlapped = cur.start;
        }
    }

    len += (cur.end - cur.overlapped);

    os << len;

    return 0;
}
