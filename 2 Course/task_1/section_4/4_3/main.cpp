#include <iostream>
#include <vector>
#include <deque>


template <typename T>
class stack {

  private:
    T* elem;
    uint_fast64_t sz;
    uint_fast64_t space;

  public:

    stack() : elem{nullptr}, sz{0}, space{0} {}

    void push(const T &el) {

        if (sz == space) {

            if (!space) {

                elem = new T[8];
                space = 8;
            }

            T *temp = new T[2 * space];
            for (auto i = 0; i < sz; ++i) {
                temp[i] = elem[i];
            }

            delete[] elem;

            std::swap(elem, temp);
            space *= 2;
        }

        elem[sz] = el;
        ++sz;
    }

    T pop() {
        if (sz == 0)
            throw std::runtime_error("Can't delete element from empty stack");

        --sz;
        return elem[sz];
    }

    bool empty() {
        return sz == 0;
    }

};

template <typename T>
class queue {

  private:
    stack<T> front;
    stack<T> back;

    void recombine() {
        while (!back.empty()) {
            front.push(back.pop());
        }
    }

  public:
    void push(const T &el) {
        back.push(el);
    }

    T pop() {
        if (front.empty())
            recombine();

        if (front.empty())
            throw std::runtime_error("Can't delete element from empty queue");

        return front.pop();
    }

};

int main() {

    std::ios::sync_with_stdio(false);

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

            int_fast32_t el;

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