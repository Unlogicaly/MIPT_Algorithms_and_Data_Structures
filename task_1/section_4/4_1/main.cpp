#include <iostream>
#include <vector>

template <typename T>
class queue {
  private:
    T *elem;
    uint_fast64_t sz;
    uint_fast64_t space;
    uint_fast64_t start;

  public:
    queue() : elem{nullptr}, sz{0}, space{0}, start{0} {
    }

    void push(const T &el) {
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

    T pop() {
        if (sz == 0)
            throw std::runtime_error("Can't delete element from empty queue");

        T res = elem[start];

        start = (start + 1) % space;
        --sz;

        return res;
    }
};

int main() {

    int_fast32_t n;
    std::cin >> n;

    queue<int_fast32_t> q;

    int_fast32_t command;
    int_fast32_t value;

    for (auto i = 0; i < n; ++i) {

        std::cin >> command >> value;

        if (command == 3) {
            q.push(value);
        }
        else {

            try {
                if (q.pop() != value) {
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
        }
    }

    std::cout << "YES";

    return 0;
}