#include <iostream>
#include <vector>
#include <random>
#include <fstream>

class hash_table {

  private:

    struct node {

        bool full{false};
        bool deleted{false};

        std::string s{};
    };

    uint_fast64_t size;

    uint_fast64_t space;

    uint_fast64_t odd;

    double alpha{0.75}; // Коэффициент заполненности, при которой необходимо делать resize

    node *base;

    [[nodiscard]] uint_fast64_t hash(const std::string &s) const;

    void resize();

  public:

    hash_table();

    explicit hash_table(const std::string &s);

    bool insert(const std::string &s);

    bool del(const std::string &s);

    [[nodiscard]] bool contain(const std::string &s) const;
};

hash_table::hash_table() : base(new node[8]), size{0}, space{8} {

    std::random_device d;
    std::mt19937 rng(d());
    std::uniform_int_distribution<uint_fast64_t> uni(1, space);

    odd = uni(rng);
}

hash_table::hash_table(const std::string &s) : hash_table() {

    this->insert(s);
}

uint_fast64_t hash_table::hash(const std::string &s) const {

    uint_fast64_t sum = s[0];

    for (auto i = 1; i < s.size(); ++i) {

        sum = (sum * odd + s[i]) % space;
    }

    return sum % space;
}

void hash_table::resize() {

    space *= 2;

    std::random_device d;
    std::mt19937 rng(d());
    std::uniform_int_distribution<uint_fast64_t> uni(1, space);

    odd = uni(rng);

    auto old_base = new node[space];

    std::swap(this->base, old_base);

    for (auto i = 0; i < space / 2; ++i) {

        if (old_base[i].full) {

            this->insert(old_base[i].s);
        }
    }

    delete[] old_base;
}

bool hash_table::insert(const std::string &s) {

    if (size + 1 == uint_fast64_t (space * alpha))
        this->resize();

    auto place = hash(s);

    uint_fast64_t c{1};

    while (base[place].full) {

        if (base[place].s == s)
            return false;

        place = (place + c * c) % space;

        ++c;
    }

    base[place].full = true;
    base[place].deleted = false;
    base[place].s = s;

    ++size;

    return true;
}

bool hash_table::del(const std::string &s) {

    auto place = hash(s);
    uint_fast64_t c = 0;

    do {

        if (!(base[place].full or base[place].deleted))
            return false;

        place = (place + c * c) % space;
        ++c;

    } while (base[place].s != s);

    if (!base[place].full)
        return false;

    base[place].deleted = true;
    base[place].full = false;
    --size;

    return true;
}

bool hash_table::contain(const std::string &s) const {

    auto place = hash(s);

    uint_fast64_t c = 0;

    while (base[place].full) {

        if (base[place].s == s)
            return true;

        place = (place + c * c) % space;

        ++c;
    }

    return false;
}

int main() {

    hash_table h{};

    char operation;
    std::string s;

    std::ifstream is("../input.txt");
    std::ofstream os("../output.txt");

    while (true) {

        is >> operation;

        if (is.eof())
            break;

        is >> s;

        os << ( (operation == '+' ? h.insert(s) : (operation == '-' ? h.del(s) : h.contain(s))) ? "OK" : "FAIL") << '\n';
    }

    return 0;
}
