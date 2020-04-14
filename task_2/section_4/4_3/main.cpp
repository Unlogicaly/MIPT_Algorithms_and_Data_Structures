//
// Created by tarog on 3/19/2020.
//

#include <iostream>
#include <vector>
#include <fstream>

#define ull unsigned long long

template <typename T>
bool greater(const T &lhs, const T &rhs) {

    return lhs <= rhs;
}

template <typename T>
ull merge(const std::vector<T> &lhs, const std::vector<T> &rhs, std::vector<T> &result, size_t start = 0,
          bool(*cmp)(const T &, const T &) = greater<T>) {

    result.reserve(lhs.size() + rhs.size());

    size_t i = 0, j = 0;

    ull res{0};

    while (i < lhs.size() and j < rhs.size()) {
        if (cmp(lhs[i], rhs[j]))
            result[start++] = lhs[i++];
        else {
            res += lhs.size() - i;
            result[start++] = rhs[j++];
        }
    }

    while (i < lhs.size())
        result.at(start++) = (lhs.at(i++));

    while (j < rhs.size())
        result.at(start++) = (rhs.at(j++));

    return res;
}

template <typename T>
ull _merge_sort(size_t left, size_t right, std::vector<T> &array, bool(*cmp)(const T &, const T &) = greater<T>) {

    if (right - left <= 1)
        return 0;

    ull res{0};

    res += _merge_sort(left, (right + left) / 2, array, cmp);
    res += _merge_sort((right + left) / 2, right, array, cmp);

    std::vector<T> a(array.begin() + left, array.begin() + (right + left) / 2);
    std::vector<T> b(array.begin() + (right + left) / 2, array.begin() + right);

    res += merge(a, b, array, left, cmp);

    return res;
}

template <typename T>
ull merge_sort(std::vector<T> &array, bool (*cmp)(const T &, const T &) = greater<T>) {

    if (array.size() <= 1)
        return 0;
    return _merge_sort(0, static_cast<int>(array.size()), array, cmp);
}

int main() {

    std::vector<ull> src;

    src.reserve(static_cast<ull>(10e6));

    std::ifstream is("input.txt");
    std::ofstream os("output.txt");

    ull tmp;

    while (is >> tmp) {
        src.push_back(tmp);
    }

    os << merge_sort(src);

    return 0;
}

