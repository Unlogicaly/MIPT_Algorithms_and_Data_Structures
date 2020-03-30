//
// Created by tarog on 3/30/2020.
//

#ifndef TESTING_DATA_CREATE_H
#define TESTING_DATA_CREATE_H

#include <random>
#include <fstream>

void create_data(int_fast64_t min, int_fast64_t max, size_t size, size_t quantity, bool print_s = false, bool print_q = false,
                 const std::string &path = "../__in.txt") {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int_fast64_t> uni(min, max);

    std::ofstream os(path);

    if (print_q)
        os << quantity << '\n';

    for (size_t i = 0; i < quantity; ++i) {
        if (print_s)
            os << size << '\n';
        for (auto j = 0; j < size; ++j) {
            os << uni(rng) << " ";
        }
        os << '\n';
    }
}

#endif //TESTING_DATA_CREATE_H
