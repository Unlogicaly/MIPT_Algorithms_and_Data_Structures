#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

struct app {

    uint_fast64_t start;

    uint_fast64_t end;
};

struct cmp {

    bool operator()(const app &lhs, const app &rhs) {

        return lhs.end < rhs.end;
    }
};

uint_fast64_t max_amount(std::vector<app> &src) {

    std::sort(src.begin(), src.end(), cmp{});

    uint_fast64_t max_amount{1};

    auto prev = src[0];

    for (auto i = 1; i < src.size(); ++i) {

        if (src[i].start >= prev.end) {

            ++max_amount;
            prev = src[i];
        }
    }

    return max_amount;
}

int main() {

    uint_fast64_t start, end;

    std::vector<app> src{};
    src.reserve(10000);

    std::ifstream is("../input.txt");
    std::ofstream os("../output.txt");

    while (is >> start >> end) {

        src.push_back({start, end});
    }

    os << max_amount(src);

    return 0;
}
