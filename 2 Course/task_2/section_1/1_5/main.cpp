#include <iostream>
#include <vector>
#include <algorithm>

struct cmp{

    static int cur_priority;
};

int cmp::cur_priority = 1;

struct greater : public cmp {

    bool operator()(const std::pair<std::string, std::vector<int>> &lhs,
                    const std::pair<std::string, std::vector<int>> &rhs) {
        return lhs.second[cur_priority - 1] > rhs.second[cur_priority - 1];
    }
};

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

int main(){

    std::ios::sync_with_stdio(false);

    int n, k;
    std::cin >> n;
    std::cin >> k;
    std::vector<int> priority(static_cast<unsigned long long int>(k));

    for (auto i = 0; i < k; ++i)
        std::cin >> priority[i];

    std::string s;
    std::vector<std::pair<std::string, std::vector<int>>> a;

    for (auto i = 0; i < n; ++i) {
        std::string name;
        std::cin >> name;
        a.emplace_back(name, std::vector<int>(static_cast<unsigned long long int>(k)));

        for (auto j = 0; j < k; ++j)
            std::cin >> a.back().second[j];
    }

    greater cmp{};

    for (auto i = k - 1; i >= 0; --i) {
        greater::cur_priority = priority[i];
        insert_sort(a.begin(), a.end(), cmp);
    }

    for (const auto &item: a) {
        std::cout << item.first;
        std::cout << "\n";
    }
}