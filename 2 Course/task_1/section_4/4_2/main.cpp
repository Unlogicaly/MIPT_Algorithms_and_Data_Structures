#include <iostream>
#include <vector>
#include <deque>


template <typename T>
class deque {
  private:
    T *elem;

    uint_fast64_t sz;

    uint_fast64_t space;

    uint_fast64_t start;

  public:
    deque() : elem{nullptr}, sz{0}, space{0}, start{0} {
    }

    uint_fast64_t size() const {

        return sz;
    }

    void push_back(const T &el) {

        if (sz == space) {
            if (!space) {
                elem = new T[8];
                space = 8;
            }

            T *temp = new T[2 * space];
            for (auto i = 0; i < sz; ++i) {
                temp[i] = elem[(i + start) % sz];
            }
            delete[] elem;
            std::swap(elem, temp);
            space *= 2;
            start = 0;
        }

        elem[(sz + start) % space] = el;
        ++sz;
    }

    T pop_front() {

        if (sz == 0)
            throw std::runtime_error("Can't delete element from empty queue");

        T res = elem[start];

        start = (start + 1) % space;
        --sz;

        return res;
    }

    void push_front(const T &el) {

        if (sz == space) {
            if (!space) {
                elem = new T[8];
                space = 8;
            }

            T *temp = new T[2 * space];
            for (auto i = 0; i < sz; ++i) {
                temp[i] = elem[(i + start) % sz];
            }
            delete[] elem;
            std::swap(elem, temp);
            space *= 2;
            start = 0;
        }

        start = (start == 0 ? space - 1 : start - 1);

        elem[start] = el;
        ++sz;
    }

    T pop_back() {

        if (sz == 0)
            throw std::runtime_error("Can't delete element from empty queue");

        T res = elem[(start + sz - 1) % space];

        --sz;

        return res;
    }
};

int main() {

    std::ios::sync_with_stdio(false);

    int_fast32_t n;
    std::cin >> n;

    deque<int_fast32_t> deq;

    int_fast32_t command;
    int_fast32_t value;

    for (auto i = 0; i < n; ++i) {

        std::cin >> command >> value;

        switch (command) {
            case 1: {
                deq.push_front(value);
                break;
            }

            case 3: {
                deq.push_back(value);
                break;
            }

            case 2: {
                try {
                    if (deq.pop_front() != value) {
                        std::cout << "NO";
                        return 0;
                    }
                }
                catch (std::exception &e) {
                    if (value != -1) {
                        std::cout << "NO";
                        return 0;
                    }
                }

                break;
            }
            case 4: {
                try {
                    if (deq.pop_back() != value) {
                        std::cout << "NO";
                        return 0;
                    }
                }
                catch (std::exception &e) {
                    if (value != -1) {
                        std::cout << "NO";
                        return 0;
                    }
                }

                break;
            }
        }
    }

    std::cout << "YES";

    return 0;
}