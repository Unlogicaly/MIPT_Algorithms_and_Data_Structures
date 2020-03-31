//
// Created by tarog on 3/31/2020.
//

#include "data_prepare.h"

#include <random>
#include <cassert>
#include <algorithm>

uint_fast64_t f(uint_fast64_t n, uint_fast64_t m) {

    return uint_fast64_t(std::log(n) / std::log(100) * (2. * m / 9 + 7. / 9));
}

uint_fast64_t F(uint_fast64_t n, uint_fast64_t m) {

    return uint_fast64_t(std::pow(std::log10(n), std::log(3.05 * std::log(m + 1) / std::log(1.85)) / std::log(2)));
}

void fully_random_data(int_fast64_t min, int_fast64_t max, size_t size, size_t quantity, bool print_s, bool print_q,
                       std::ostream &os) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int_fast64_t> uni(min, max);

    if (print_q)
        os << quantity << '\n';

    if (print_s)
        os << size << '\n';

    for (size_t i = 0; i < quantity; ++i) {

        for (auto j = 0; j < size; ++j) {
            os << uni(rng) << " ";
        }
        os << '\n';
    }
}

void
partially_random_data(int_fast64_t min, int_fast64_t max, size_t size, size_t quantity, size_t degree, bool print_s,
                      bool print_q, std::ostream &os) {

    assert(1 <= degree and degree <= 10);

//    if (size <= 30) {
//        fully_random_data(min, max, size, quantity, print_s, print_q, os);
//        return;
//    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int_fast64_t> uni(min, max);
    std::uniform_int_distribution<uint_fast64_t> gap(f(size, degree), F(size, degree));

    if (print_q)
        os << quantity << '\n';

    if (print_s)
        os << size << '\n';

    os << degree << '\n';

    for (auto i = 0; i < quantity; ++i) {

        uint_fast64_t start{0};
        uint_fast64_t end{gap(rng)};

        while (true) {

            std::vector<int_fast64_t> buf(end - start);

            for (uint_fast64_t j = 0; start < end; ++start, ++j)
                buf[j] = uni(rng);

            std::sort(buf.data(), buf.data() + buf.size());

            for (auto el: buf)
                os << el << ' ';

            if (end == size)
                break;

            end = std::min(end + gap(rng), size);
        }

        os << '\n';
    }
}

void generate_data(int_fast64_t min, int_fast64_t max, const std::vector<size_t> &sizes,
                   const std::vector<size_t> &quantities, const std::vector<size_t> &degrees, bool print_s,
                   bool print_q, std::ostream &full_random_stream, std::ostream &part_random_stream) {

    assert(sizes.size() == quantities.size());

    full_random_stream << sizes.size() << '\n';

    for (auto i = 0; i < sizes.size(); ++i) {
        fully_random_data(min, max, sizes[i], quantities[i], print_s, print_q, full_random_stream);
    }

    part_random_stream << sizes.size() * degrees.size() << '\n';

    for (auto degree: degrees) {
        for (auto i = 0; i < sizes.size(); ++i) {
            partially_random_data(min, max, sizes[i], quantities[i], degree, print_s, print_q, part_random_stream);
        }
    }
}
