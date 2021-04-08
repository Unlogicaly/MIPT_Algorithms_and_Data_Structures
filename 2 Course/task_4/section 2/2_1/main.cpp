#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

struct athlet {

    uint_fast64_t weight;
    uint_fast64_t strength;
};

struct cmp {

    bool operator()(const athlet &lhs, const athlet &rhs) {

        return lhs.weight < rhs.weight ? true : lhs.weight == rhs.weight ? lhs.strength < rhs.strength : false;
    }
};

uint_fast64_t max_height(std::vector<athlet> &src) {

    uint_fast64_t res{0};
    uint_fast64_t cur_w{0};

    std::sort(src.begin(), src.end(), cmp{});

    for (auto i : src) {

        if (i.strength >= cur_w) {

            ++res;
            cur_w += i.weight;
        }
    }

    return res;
}

int main() {

    std::vector<athlet> src{};
    src.reserve(100000);

    uint_fast64_t weight, strength;

    std::ifstream is("input.txt");
    std::ofstream os("output.txt");

    while (true) {

        is >> weight;

        if (!is.good())
            break;

        is >> strength;

        src.push_back({weight, strength});
    }

    os << max_height(src);

    return 0;
}