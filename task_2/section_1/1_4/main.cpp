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
    bool operator()(const std::string &lhs, const std::string &rhs) {

        size_t i = 0;
        while (i < lhs.size() and i < rhs.size()) {
            if (lhs[i] == rhs[i])
                ++i;
            else
                return lhs[i] < rhs[i];
        }

        return i == lhs.size();
    }
};

int main(){

    std::ios::sync_with_stdio(false);

    int n;

    std::string s;
    std::getline(std::cin, s);
    n = std::stoi(s);

    std::vector<std::string> a(static_cast<unsigned long long int>(n));

    for (auto i = 0; i < n; ++i) {
        std::getline(std::cin, a[i]);
    }

    insert_sort(a.begin(), a.end(), cmp{});

    for (const auto &i: a) {
        std::cout << i;
        std::cout << "\n";
    }
}