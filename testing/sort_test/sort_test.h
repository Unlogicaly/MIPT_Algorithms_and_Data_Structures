//
// Created by tarog on 3/31/2020.
//

#ifndef SORT_TESTING_SORT_TEST_H
#define SORT_TESTING_SORT_TEST_H

#include "data_prepare.h"
#include <map>

void test_funcs(std::map<std::string, void (*)(int_fast64_t *, int_fast64_t *, typeof(std::less<>))> &funcs,
                uint_fast64_t max_size = 1000000);

#endif //SORT_TESTING_SORT_TEST_H
