#include <iostream>
#include <vector>
#include <fstream>

int main() {

    std::ifstream is("input.txt");
    std::ofstream os("output.txt");

    size_t n, k;
    is >> n >> k;

    std::vector<int> array(n);

    for (auto i = 0; i < n; ++i)
        is >> array.at(i);

    size_t start = 0, end = n - 1;

    size_t i, j;

    while (end - start > 1) {

        i = start;
        j = start + 1;

        std::swap(array.at((start + end) / 2), array.at(end));

        while (i < end and array[i] <= array[end]) {
            ++i;
            ++j;
        }

        if (i == end) {
            if (k == end) {
                os << array.at(k);
                return 0;
            }
            --end;
            continue;
        }

        while (j < end) {
            if (array.at(j) <= array.at(end))
                std::swap(array.at(i++), array.at(j++));
            else
                ++j;
        }

        std::swap(array.at(end), array.at(i));

        if (k <= i)
            end = i;
        else
            start = i;
    }

    os << array.at(start == k ? start : end);

    return 0;
}