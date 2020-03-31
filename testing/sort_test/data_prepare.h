//
// Created by tarog on 3/31/2020.
//

#ifndef SORT_TESTING_DATA_PREPARE_H
#define SORT_TESTING_DATA_PREPARE_H

#include <cinttypes>
#include <fstream>
#include <vector>

void fully_random_data(int_fast64_t min, int_fast64_t max, size_t size, size_t quantity, bool print_s,
                       bool print_q,
                       std::ostream &os);

void partially_random_data(int_fast64_t min, int_fast64_t max, size_t size, size_t quantity, size_t degree,
                           bool print_s, bool print_q, std::ostream &os);

void generate_data(int_fast64_t min, int_fast64_t max, const std::vector<size_t> &sizes,
                   const std::vector<size_t> &quantities, const std::vector<size_t> &degrees, bool print_s,
                   bool print_q, std::ostream &full_random_stream, std::ostream &part_random_stream);

#endif //SORT_TESTING_DATA_PREPARE_H
