//
// Created by tarog on 3/31/2020.
//

#ifndef SORT_TESTING_SORT_TEST_H
#define SORT_TESTING_SORT_TEST_H

#include "data_prepare.h"
#include <map>

/**
 * The function is for testing different sorts and comparing their usability on arrays
 * with different lengths and orderliness degree
 *
 * Whole process might take long time due to many tests. With maximum array size ~100000 it might take ~30 minutes.
 * Recommended to use release mode to speed up testing
 *
 * @param funcs functions to be tested. Input format: std::map with keys from functions names and values functions.
 * It's implied that sorting function accepts iterator on the beginning and on the end of the sorting array (vector, list, etc.)
 * and comparison function. In the testing function will be used std::vector with 64-bit integers in range [-max_size, max_size]
 * and comparison function std::less<>
 *
 * @param max_size max size of sorting arrays. Also this parameter impacts on number generating range and amount of tests, so
 * increasing the parameter will slow down implementation of the testing function exponentially
 *
 * Example of creating map funcs: @code
 *      std::map<std::string, void (*)(int_fast64_t *, int_fast64_t *, typeof(std::less<>))> funcs {
 *          {"quick sort", &quick_sort<int_fast64_t *, std::less<>>}
 *      };
 */

void test_funcs(std::map<std::string, void (*)(int_fast64_t *, int_fast64_t *, typeof(std::less<>))> &funcs,
                uint_fast64_t max_size = 1000000);

#endif //SORT_TESTING_SORT_TEST_H
