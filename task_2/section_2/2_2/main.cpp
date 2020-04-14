#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <list>
#include <functional>
#include <memory>

template <typename T>
struct Node {

    T val{};
    uint_fast64_t rk{0};

    Node<T> *child{nullptr};
    Node<T> *left{nullptr};
    Node<T> *right{nullptr};

    bool rec{true};

    Node() = default;

    explicit Node(const T &elem) : val{elem} {}

    ~Node() {

        if (rec) {
            delete child;
            delete right;
        }
    }
};

template <typename T>
struct heap_base {

    Node<T> *first{nullptr};

    Node<T> *last{nullptr};

    heap_base() : first{nullptr}, last{nullptr} {};

    ~heap_base() {

        delete first;
    }
};

#include <cmath>
#include <vector>

const double f{(1 + std::sqrt(5)) / 2};

template<typename T, class _Cmp = std::less<T>>
class ThinHeap : private heap_base<T> {

  private:

    uint_fast64_t sz{0};

    _Cmp cmp{};

    uint_fast64_t n{0};

    void insert(Node<T> *node) {

        if (!this->first) {
            this->first = node;
            this->last = node;
        }
        else if (cmp(node->val, this->first->val)) {
            node->right = this->first;
            this->first = node;
        }
        else {
            this->last->right = node;
            this->last = node;
        }
    }

    void copy_node(Node<T> *node) {

        if (!node)
            return;

        this->push(node->val);
        copy_node(node->child);
        copy_node(node->right);
    }

    bool is_thin(Node<T> *node) {

        return (node->rk ? node->rk == 1 ? !node->child : node->child->rk + 1 != node->rk : false);
    }

  public:

    explicit ThinHeap(const T &elem, _Cmp cmp = {}) : cmp{cmp} {

        this->push(elem);
    }

    explicit ThinHeap(_Cmp cmp = {}) : cmp{cmp} {}

    template <class _Iter>
    ThinHeap(_Iter begin, _Iter end);

    ThinHeap(const ThinHeap<T, _Cmp> &other);

    ThinHeap(ThinHeap<T, _Cmp> &&other) noexcept;

    void push(const T &elem);

    const T &top();

    void pop();

    uint_fast64_t size(){
        return sz;
    }

    bool empty() {
        return !this->n;
    }
};

template <typename T, class _Cmp>
void ThinHeap<T, _Cmp>::push(const T &elem) {

    ++this->sz;

    auto tmp_ptr = std::make_unique<Node<T>>(elem);

    this->insert(tmp_ptr.release());
    ++n;
}

template <typename T, class _Cmp>
const T &ThinHeap<T, _Cmp>::top() {

    return this->first->val;
}

template <typename T, class _Cmp>
void ThinHeap<T, _Cmp>::pop() {

    --this->sz;

    std::unique_ptr<Node<T>> tmp{this->first};

    tmp->rec = false;

    this->first = this->first->right;

    if (!this->first)
        this->last = nullptr;

    auto x = tmp->child;

    Node<T> *next{nullptr};

    while (x) {
        if (is_thin(x))
            --x->rk;

        x->left = nullptr;
        next = x->right;
        x->right = nullptr;
        insert(x);
        x = next;
    }

    x = this->first;
    std::vector<Node<T> *> aux(uint_fast64_t(std::log(n)/std::log(f)) + 1, nullptr);

    while(x) {

        next = x->right;

        while(aux[x->rk]) {

//            if (x->right == aux[x->rk])
//                next = x->right->right;

            if (cmp(aux[x->rk]->val, x->val)) {
                std::swap(aux[x->rk], x);
            }
            aux[x->rk]->right = x->child;
            if (x->child) {
                x->child->left = aux[x->rk];
            }
            aux[x->rk]->left = x;
            x->child = aux[x->rk];
            aux[x->rk] = nullptr;
            ++x->rk;
        }

        x->left = nullptr;
        x->right = nullptr;
        aux[x->rk] = x;
        x = next;
    }

    ThinHeap<T, _Cmp> new_heap{};
    for (auto i = 0; i < aux.size(); ++i) {
        if (aux[i]) {
            new_heap.insert(aux[i]);
        }
    }

    this->first = new_heap.first;
    new_heap.first = nullptr;

    this->last = new_heap.last;
    new_heap.last = nullptr;

    --n;
}

template <typename T, class _Cmp>
template <class _Iter>
ThinHeap<T, _Cmp>::ThinHeap(_Iter begin, _Iter end) {

    this->sz = end - begin;

    for (auto iter = begin; iter != end; ++iter) {

        this->push(*iter);
    }
}

template <typename T, class _Cmp>
ThinHeap<T, _Cmp>::ThinHeap(const ThinHeap<T, _Cmp> &other) : cmp{other.cmp}, sz{other.sz} {

    copy_node(other.first);
}

template <typename T, class _Cmp>
ThinHeap<T, _Cmp>::ThinHeap(ThinHeap<T, _Cmp> &&other) noexcept {

    std::swap(this->first, other.first);
    std::swap(this->last, other.last);
    std::swap(this->n, other.n);
    std::swap(this->cmp, other.cmp);
    std::swap(this->sz, other.sz);
}

template <typename _Iter, class _Cmp = std::less<>>
inline void insert_sort(_Iter begin, _Iter end, _Cmp cmp = {}){

    for (auto cur = begin; cur != end; ++cur) {
        auto pos = cur;
        --pos;

        while (pos >= begin and cmp(*cur, *pos))
            --pos;

        ++pos;
        for (auto j = cur; j != pos; --j)
            std::swap(*j, *(j - 1));
    }
}

template <typename _Iter, class _Cmp>
inline _Iter pivot(_Iter begin, _Iter end, _Cmp cmp = {}) {

    --end;
    auto mid = begin + ((end - begin) >> 2);
    auto a = *begin, b = *mid, c = *end;

    return cmp(a, b) ? cmp(b, c) ? mid : cmp(a, c) ? end : begin :cmp(a, c) ? begin : cmp(b, c) ? end : mid;
}

template <typename _Iter, class _Cmp>
inline _Iter partition(_Iter begin, _Iter end, _Cmp cmp = {}) {

    _Iter p = pivot(begin, end, cmp);

    auto pivot = *p;

    std::swap(*p, *(end - 1));
    --end;

    auto i = begin, j = end - 1;

    while (i < j) {
        while (i != end and cmp(*i, pivot))
            ++i;
        while (j != begin and !cmp(*j, pivot))
            --j;

        if (i < j)
            std::swap(*i, *j);
    }

    std::swap(*end, *i);

    return i;
}

template <typename _Iter, class _Cmp>
inline void quick_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    while (end - begin > 16) {
        _Iter p_ind = partition<_Iter, _Cmp>(begin, end);
        if (p_ind - begin < end - p_ind + 1) {
            quick_sort(begin, p_ind, cmp);
            begin = p_ind + 1;
        }
        else {
            quick_sort(p_ind + 1, end, cmp);
            end = p_ind;
        }
    }
    insert_sort(begin, end, cmp);
}

struct date {
    int day;

    int month;

    int year;

    date &operator--() {

        day--;
        if (day == 0) {
            month--;
            if (month == 0) {
                year--;
                month = 12;
            }
            else if (month == 2) {
                day = (month % 4 ? 28 : 29);
            }
            if ((month % 2 and month <= 7) or (!(month % 2) and month > 7))
                day = 31;
            else
                day = 30;
        }
        return *this;
    }
};

std::istream &operator>>(std::istream &is, date &d) {

    return is >> d.day >> d.month >> d.year;
}

std::ostream &operator<<(std::ostream &os, date &d) {

    return os << d.day << " " << " " << d.month << " " << d.year;
}

struct person {
    date birth;
    date funeral;
};

std::istream &operator>>(std::istream &is, person &p) {

    return is >> p.birth >> p.funeral;
}

std::ostream &operator<<(std::ostream &os, person &p) {

    return os << p.birth << ' ' << p.funeral;
}

int age(const person &p) {

    return (p.funeral.year - p.birth.year +
            (p.funeral.month > p.birth.month ? true : p.funeral.month == p.birth.month and
                                                      p.funeral.day >= p.birth.day)) - 1;
}

bool operator<(const date &lhs, const date &rhs) {

    return (lhs.year < rhs.year ? true : lhs.year == rhs.year and lhs.month < rhs.month ? true : lhs.year == rhs.year and
                                                                                                 lhs.month == rhs.month and lhs.day < rhs.day);
}

bool operator==(const date &lhs, const date &rhs) {

    return lhs.year == rhs.year and lhs.month == rhs.month and lhs.day == rhs.day;
}

bool operator<=(const date &lhs, const date &rhs) {

    return lhs < rhs or lhs == rhs;
}

bool coeval(const person &lhs, const person &rhs) {
    return (rhs.birth < lhs.funeral and lhs.birth <= rhs.birth) or
           (rhs.birth <= lhs.birth and lhs.birth < rhs.funeral);
}

struct b_cmp {
    bool operator()(const person &lhs, const person &rhs) {

        return lhs.birth < rhs.birth;
    }
};

struct f_cmp {

    bool operator()(const person &lhs, const person &rhs) {

        return lhs.funeral < rhs.funeral;
    }
};

int main() {

    std::ifstream is("input.txt");
    std::ofstream os("output.txt");

    int n;
    is >> n;

    std::vector<person> a;

    for (auto i = 0; i < n; ++i) {

        person tmp{{0, 0, 0},
                   {0, 0, 0}};

        is >> tmp;

        if (age(tmp) < 18 or (age(tmp) == 18 and tmp.birth.month == tmp.funeral.month and tmp.birth.day == tmp.funeral.day)) {
            --n;
            --i;
            continue;
        }

        if (age(tmp) >= 80) {
            tmp.funeral.year -= (age(tmp) - 80);
            if (tmp.funeral.month < tmp.birth.month or (tmp.funeral.month == tmp.birth.month and tmp.funeral.day < tmp.birth.day))
                --tmp.funeral.year;
            tmp.funeral.month = tmp.birth.month;
            tmp.funeral.day = tmp.birth.day;
        }

        tmp.birth.year += 18;

        a.push_back(tmp);
    }

    quick_sort(a.begin(), a.end(), b_cmp{});

    ThinHeap<person, f_cmp> src{};
    int res = 0;

    for (auto i = 0; i < n; ++i) {
        if (src.empty()) {
            src.push(a[i]);
        }
        else if (coeval(a[i], src.top())) {
            src.push(a[i]);
        }
        else {
            res = std::max(res, static_cast<int>(src.size()));
            while (!src.empty() and !coeval(a[i], src.top()))
                src.pop();
            src.push(a[i]);
        }
    }

    res = std::max(res, static_cast<int>(src.size()));

    os << res << "\n";

    return 0;
}