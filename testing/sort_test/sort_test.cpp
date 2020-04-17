//
// Created by tarog on 3/31/2020.
//

#include "sort_test.h"
#include "timer.h"

void test_func(void (*func)(int_fast64_t *, int_fast64_t *, typeof(std::less<>)),
               std::map<uint_fast64_t, double> &full_random_time,
               std::map<std::pair<uint_fast64_t, uint_fast64_t>, double> &part_random_time,
               std::istream &full_random_is, std::istream &part_random_is, bool full) {

    uint_fast64_t quantity{0}, size{0}, n{0};

    full_random_is >> n;

    while (n--) {

        full_random_is >> quantity;
        full_random_is >> size;

        double time{0};

        Timer timer{};

        for (uint_fast64_t i = 0; i < quantity; ++i) {

            std::vector<int_fast64_t> tmp(size);

            for (auto j = 0; j < size; ++j)
                full_random_is >> tmp[j];

            timer.start();
            func(tmp.data(), tmp.data() + tmp.size(), std::less<>{});
            timer.stop();

            time += timer.elapsed();
        }

        full_random_time.insert({size, time / quantity});
    }

    if (!full)
        return;

    uint_fast64_t degree{0};

    part_random_is >> n;

    while (n--) {

        part_random_is >> quantity;
        part_random_is >> size;
        part_random_is >> degree;

        double time{0};

        Timer timer{};

        for (uint_fast64_t i = 0; i < quantity; ++i) {

            std::vector<int_fast64_t> tmp(size);

            for (auto j = 0; j < size; ++j)
                part_random_is >> tmp[j];

            timer.start();
            func(tmp.data(), tmp.data() + tmp.size(), std::less<>{});
            timer.stop();

            time += timer.elapsed();
        }

        part_random_time.insert({{size, degree}, time / quantity});
    }
}

template <typename T, typename P>
void del_min_max(std::map<T, std::vector<P>> &map) {
    for (auto &t: map) {

        uint_fast64_t min_i = 0, max_i = 0;

        for (uint_fast64_t i = 0; i < t.second.size(); ++i) {
            min_i = (t.second[i] < t.second[min_i] ? i : min_i);
            max_i = (t.second[i] > t.second[min_i] ? i : max_i);
        }

        t.second.erase(t.second.begin() + min_i);
        if (max_i > min_i)
            --max_i;

        t.second.erase(t.second.begin() + max_i);
    }
}

void test_funcs(std::map<std::string, void (*)(int_fast64_t *, int_fast64_t *, typeof(std::less<>))> &funcs,
                uint_fast64_t max_size, bool full) {

    int_fast64_t min = -max_size, max = max_size;
    std::vector<size_t> sizes{}, quantities{}, degrees{1, 2, 5, 10};

    for (size_t i = 10; i < max_size; i *= 10) {

        for (auto j: {i, 2 * i, 5 * i}) {

            sizes.push_back(j);
            quantities.push_back(10 * max_size / i);
        }
    }

    std::ofstream full_random_os("../__f_rand.in");
    std::ofstream part_random_os("../__p_rand.in");

    generate_data(min, max, sizes, quantities, degrees, true, true, full_random_os, part_random_os);

    full_random_os.close();
    part_random_os.close();

    std::vector<std::map<std::string, std::map<uint_fast64_t, double>>> full_rand_times{};
    std::vector<std::map<std::string, std::map<std::pair<uint_fast64_t, uint_fast64_t>, double>>> part_rand_times{};

    for (auto i = 0; i < 5; ++i) {

        full_rand_times.emplace_back();
        part_rand_times.emplace_back();
        for (const auto &func: funcs) {

            std::ifstream full_random_is("../__f_rand.in");
            std::ifstream part_random_is("../__p_rand.in");

            full_rand_times[i].insert({func.first, {}});
            part_rand_times[i].insert({func.first, {}});
            test_func(func.second, full_rand_times[i].at(func.first), part_rand_times[i].at(func.first), full_random_is,
                      part_random_is, full);
        }
    }

    for (const auto &func: funcs) {

        std::ofstream full_rand_os("../__f_rand_" + func.first + ".out");
        std::ofstream part_rand_os("../__p_rand_" + func.first + ".out");

        std::map<uint_fast64_t, std::vector<double>> cur_full_rand_times;
        std::map<std::pair<uint_fast64_t, uint_fast64_t>, std::vector<double>> cur_part_rand_times;

        for(auto t: full_rand_times[0].begin()->second)
            cur_full_rand_times.insert({t.first, std::vector<double>(5)});

        for(auto t: part_rand_times[0].begin()->second)
            cur_part_rand_times.insert({t.first, std::vector<double>(5)});

        for (auto i = 0; i < 5; ++i) {

            for (auto &t_size: cur_full_rand_times) {
                t_size.second[i] = full_rand_times[i].at(func.first)[t_size.first];
            }

            for (auto &t_size: cur_part_rand_times) {
                t_size.second[i] = part_rand_times[i].at(func.first)[t_size.first];
            }
        }

        del_min_max(cur_full_rand_times);
        del_min_max(cur_part_rand_times);

        for (auto &t_size: cur_full_rand_times) {
            auto mean = (t_size.second[0] + t_size.second[1] + t_size.second[2]) / 3;
            full_rand_os << "size: " << t_size.first << "\ntime: " << mean << "\n\n";
        }

        for (auto &t_size: cur_part_rand_times) {
            auto mean = (t_size.second[0] + t_size.second[1] + t_size.second[2]) / 3;
            part_rand_os << "size: " << t_size.first.first << "\norderliness degree: " << t_size.first.second << "\ntime: " << mean << "\n\n";
        }
    }
}
