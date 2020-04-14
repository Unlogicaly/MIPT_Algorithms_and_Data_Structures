
//
// Created by tarog on 3/19/2020.
//

#include <cinttypes>
#include <memory>
#include <cmath>
#include <vector>
#include <iostream>
#include <stack>

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

int main() {

    std::ios::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    ThinHeap<int, std::greater<>> heap;

    for (auto i = 0; i < k; ++i) {
        int tmp;
        std::cin >> tmp;
        heap.push(tmp);
    }

    for (auto i = 0 ; i < n - k; ++i) {
        int tmp;
        std::cin >> tmp;
        heap.push(tmp);
        heap.pop();
    }

    std::stack<int> res;

    while (!heap.empty()) {
        res.push(heap.top());
        heap.pop();
    }

    while (!res.empty()) {
        std::cout << res.top() << " ";
        res.pop();
    }

    return 0;
}

