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

struct point{
    int x;
    int y;
};

std::istream &operator >> (std::istream &is, point &p1) {
    return is >> p1.x >> p1.y;
}

struct x_cmp {
    bool operator()(const point &p1, const point &p2) {

        return (p1.x < p2.x ? true : p1.x == p2.x and p1.y <= p2.y);
    }
};

double angle(const point &p1, const point &p2) {
    return p1.x != p2.x ? double(p1.y - p2.y) / (p1.x - p2.x) : 10000000;
}

point p_left;

struct angle_cmp {
    bool operator ()(const point &p1, const point &p2) {
        return angle(p_left, p1) >= angle(p_left, p2);
    }
};


int main(){

    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<point> a(static_cast<unsigned long long int>(n));

    if (n == 0)
        return 0;

    for (auto i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    insert_sort(a.begin(), a.end(), x_cmp{});
    p_left = a.front();

    insert_sort(a.begin() + 1, a.end(), angle_cmp{});

    for (auto i: a) {
        std::cout << i.x << " " << i.y << "\n";
    }
}