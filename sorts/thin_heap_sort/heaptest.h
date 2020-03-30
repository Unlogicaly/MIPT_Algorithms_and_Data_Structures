//
// Created by tarog on 3/30/2020.
//

#ifndef TESTING_HEAPTEST_H
#define TESTING_HEAPTEST_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "data_create.h"

template <typename T, class _Cmp, class Heap>
struct HeapTest {

    bool sug;

    std::string path{"../__in.txt"};

    std::istream &is;

    std::ostream &log;

    std::ostream &err;

    std::ostream &out;

    HeapTest(bool sug, std::istream &is, std::ostream &log, std::ostream &err, std::ostream &out = std::cout) :
            sug{sug}, is{is}, log{log}, err{err}, out{out} {

        std::ios::sync_with_stdio(false);
    }

    bool ask(const std::string &test) {

        std::string ans;

        if (sug)
            out << test << "\ny - continue, n - exit tests: ";

        std::getline(is, ans);

        while (ans != "y" and ans != "n") {
            if (sug)
                out << "wrong input\ny - continue, n - exit tests: ";

            std::getline(is, ans);
        }

        return ans == "y";
    }

    void w_log(const std::string &test, uint_fast64_t n, bool ok) {

        log << test << " n: " << (ok ? "ok" : "error") << '\n';
    }

    void w_err(const std::string &test, uint_fast64_t n, const std::string &error) {

        err << test << " " << n << ": " << error << '\n';
    }

    void constructor_test() {

        {
            std::string test{"default constructor test"};
            if (ask(test))
                for (uint_fast64_t i = 0; i < 1000; ++i) {
                    bool ok{true};
                    try {
                        Heap t{};
                    }
                    catch (std::exception &e) {
                        ok = false;
                        w_err(test, i + 1, e.what());
                    }
                    w_log(test, i + 1, ok);
                }
        }

        {
            std::string test{"single element constructor test"};
            if (ask(test))
                for (uint_fast64_t i = 0; i < 1000; ++i) {
                    bool ok{true};
                    try {
                        Heap t{T{}};
                    }
                    catch (std::exception &e) {
                        ok = false;
                        w_err(test, i + 1, e.what());
                    }
                    w_log(test, i + 1, ok);
                }
        }

        {
            std::string test{"range iterator constructor test"};
            if (ask(test))
                for (uint_fast64_t i = 0; i < 1000; ++i) {
                    bool ok{true};

                    std::vector<T> _a(i, {});

                    try {
                        Heap t{_a.begin(), _a.end()};
                    }
                    catch (std::exception &e) {
                        ok = false;
                        w_err(test, i + 1, e.what());
                    }
                    w_log(test, i + 1, ok);
                }
        }

        {
            std::string test{"copy constructor test"};
            if (ask(test))
                for (uint_fast64_t i = 0; i < 1000; ++i) {
                    bool ok{true};

                    std::vector<T> _a(i, {});

                    try {
                        Heap _t{_a.begin(), _a.end()};
                        Heap t{_t};
                    }
                    catch (std::exception &e) {
                        ok = false;
                        w_err(test, i + 1, e.what());
                    }
                    w_log(test, i + 1, ok);
                }
        }

        {
            std::string test{"move constructor test"};
            if (ask(test))
                for (uint_fast64_t i = 0; i < 1000; ++i) {
                    bool ok{true};

                    std::vector<T> _a(i, {});

                    try {
                        Heap _t{_a.begin(), _a.end()};
                        Heap t{std::move(_t)};
                    }
                    catch (std::exception &e) {

                        ok = false;
                        w_err(test, i + 1, e.what());
                    }
                    w_log(test, i + 1, ok);
                }
        }
    }

    void push_test(int_fast32_t min = -10000, int_fast32_t max = 10000, uint_fast64_t size = 1000, uint_fast64_t quantity = 1000) {

        std::string test{"push test"};

        out << "push test: this test might be carried out correctly only on int_32 heap with compare function 'less'\n";

        if (!ask(test))
            return;

        std::ifstream t_in(path);
        create_data(min, max, size, quantity, false, false, path);

        for (auto i = 0; i < quantity; ++i) {

            try {
                int_fast32_t cur_min{max};

                log << "test " << i + 1 << "\ninput data:\n";

                int_fast32_t elem;

                Heap t{};

                for (auto j = 0; j < size; ++j) {
                    t_in >> elem;
                    log << elem << ' ';
                    cur_min = std::min(cur_min, elem);
                    t.push(elem);
                }

                log << "\nexpected value: " << cur_min << "\nreceived value: " << t.top() << "\n\n";

                if (cur_min != t.top()) {
                    throw std::runtime_error(
                            "unmatched values: right value " + std::to_string(cur_min) + "received value " +
                            std::to_string(t.top()));
                }
            }
            catch (std::exception &e) {
                log << "\nerror\n\n";
                w_err(test, i + 1, e.what());
            }
        }

        log << "\n\n";
        err << "\n\n";
    }

    void pop_test(int_fast32_t min = -10000, int_fast32_t max = 10000, uint_fast64_t size = 1000, uint_fast64_t quantity = 1000) {

        std::string test{"pop test"};

        out << "pop test: this test might be carried out correctly only on int_32 heap with compare function 'less' and correct range iterator constructor\n";

        if (!ask(test))
            return;

        std::ifstream t_in(path);
        create_data(min, max, size, quantity, false, false, path);

        for (auto i = 0; i < quantity; ++i) {

            try {

                log << "test " << i + 1 << "\ninput data:\n";

                std::vector<int_fast32_t> a(size);

                for (auto j = 0; j < size; ++j) {
                    t_in >> a[j];
                    log << a[j] << ' ';
                }

                log << "\noutput:\n";

                Heap t(a.begin(), a.end());

                std::sort(a.begin(), a.end());

                bool ok = true;

                for (auto j = 0; j < size; ++j) {
                    auto elem{t.top()};
                    t.pop();
                    log << elem << ' ';
                    if (elem != a[j]) {
                        ok = false;
                    }
                }

                log << "\nexpected output:\n";

                for (auto j: a)
                    log << j << ' ';

                log << "\n\n";

                if (!ok)
                    throw std::runtime_error("unmatched values");
            }
            catch (std::exception &e) {
                log << "\nerror\n\n";
                w_err(test, i + 1, e.what());
            }
        }
    }
};

#endif //TESTING_HEAPTEST_H
