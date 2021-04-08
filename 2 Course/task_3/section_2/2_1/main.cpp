#include <memory>
#include <functional>
#include <cassert>
#include <random>
#include <iostream>

template <typename T>
struct Node {

    T val{};

    Node<T> *parent{nullptr};

    Node<T> *left{nullptr};

    Node<T> *right{nullptr};

    explicit Node(const T &elem) : val{elem} {}

    ~Node() {

        delete left;
        delete right;
    }
};

template <typename T, class _Cmp = std::less<>>
class BinaryTree {

  private:

    T key{};

    Node<T> *root{nullptr};

    _Cmp cmp{};

    Node<T> *_first(Node<T> *root);

    uint_fast64_t _depth(Node<T> *root) {

        return (root ? std::max(_depth(root->left), _depth(root->right)) + 1 : 0);
    }

  public:

    BinaryTree() = default;

    explicit BinaryTree(const T &elem) : root(std::make_unique<Node<T>>(elem).release()), key{elem} {}

    template <class _Iter>
    BinaryTree(_Iter begin, _Iter end);

    void insert(const T &elem);

    bool del(const T &elem);

    const T &first();

    bool empty() {
        return !(this->root);
    }

    void del_first();

    void in_order(std::ostream &os);

    void post_order(std::ostream &os);

    void pre_order(std::ostream &os);

    void level_order(std::ostream &os);

    uint_fast64_t depth() {
        return this->_depth(this->root);
    }

    ~BinaryTree() {

        delete root;
    }
};

template <typename T, class _Cmp>
void BinaryTree<T, _Cmp>::insert(const T &elem) {

    auto cur = this->root;

    if (!cur) {

        this->key = elem;

        this->root = std::make_unique<Node<T>>(elem).release();
        return;
    }

    this->key = std::min(key, elem);

    auto prev = cur;

    while (cur) {

        prev = cur;

        cur = (cmp(cur->val, elem) ? cur->right : cur->left);
    }

    cur = std::make_unique<Node<T>>(elem).release();
    cur->parent = prev;
    (cmp(prev->val, elem) ? prev->right : prev->left) = cur;
}

template <typename K, typename P>
struct _Node {

    K key{};

    P priority{};

    _Node<K, P> *left{nullptr};

    _Node<K, P> *right{nullptr};

    _Node(const K &key, const P &priority) : key{key}, priority{priority} {}

    explicit _Node(const std::pair<K, P> &elem) : key{elem.first}, priority{elem.second} {}

    ~_Node() {

        delete left;
        delete right;
    }
};

template <typename K, typename P, class _k_cmp = std::less<K>, class _p_cmp = std::less<P>>
class Treap {

  private:

    K fst{};

    _Node<K, P> *root{nullptr};

    _k_cmp k_cmp{};

    _p_cmp p_cmp{};

    std::pair<_Node<K, P> *, _Node<K, P> *> _split(_Node<K, P> *root, K key);

    _Node<K, P> *_merge(_Node<K, P> *lhs, _Node<K, P> *rhs);

    _Node<K, P> *_first(_Node<K, P> *root);

    uint_fast64_t _depth(_Node<K, P> *root) {

        return (root ? std::max(_depth(root->left), _depth(root->right)) + 1 : 0);
    }

  public:

    Treap() = default;

    explicit Treap(const std::pair<K, P> elem) : root{std::make_unique<_Node<K, P>>(elem).release()}, fst{elem.first} {}

    template <typename _Iter>
    Treap(_Iter begin, _Iter end);

    void insert(const std::pair<K, P> &elem);

    void del(const K &key);

    const K &first() {

        return fst;
    }

    void del_first();

    uint_fast64_t depth();

    ~Treap() {

        delete this->root;
    }
};

template <typename K, typename P, class _k_cmp, class _p_cmp>
std::pair<_Node<K, P> *, _Node<K, P> *> Treap<K, P, _k_cmp, _p_cmp>::_split(_Node<K, P> *root, K key) {

    if (!root)
        return {nullptr, nullptr};

    if (k_cmp(root->key, key)) {
        auto[node1, node2] = _split(root->right, key);
        root->right = node1;
        return {root, node2};
    }

    auto[node1, node2] = _split(root->left, key);
    root->left = node2;
    return {node1, root};
}


template <typename K, typename P, class _k_cmp, class _p_cmp>
void Treap<K, P, _k_cmp, _p_cmp>::insert(const std::pair<K, P> &elem) {

    if (!this->root) {
        this->fst = elem.first;
        this->root = std::make_unique<_Node<K, P>>(elem).release();
        return;
    }

    auto cur = this->root;
    auto prev = cur;

    this->fst = std::min(fst, elem.first, k_cmp);

    while (cur and !p_cmp(cur->priority, elem.second)) {

        prev = cur;
        cur = (k_cmp(elem.first, cur->key) ? cur->left : cur->right);
    }

    auto new_node = std::make_unique<_Node<K, P>>(elem).release();

    auto [left, right] = this->_split(cur, elem.first);

    new_node->left = left;
    new_node->right = right;

    (prev == cur ? this->root : k_cmp(elem.first, prev->key) ? prev->left : prev->right) = new_node;
}


template <typename K, typename P, class _k_cmp, class _p_cmp>
uint_fast64_t Treap<K, P, _k_cmp, _p_cmp>::depth() {

    return this->_depth(this->root);
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    Treap<int_fast64_t, int_fast64_t> treap{};
    BinaryTree<int_fast64_t> binomialTree{};

    for (auto i = 0; i < n; ++i) {
        int_fast64_t k, p;
        std::cin >> k >> p;

        treap.insert({k, p});
        binomialTree.insert(k);
    }

    std::cout << std::abs(int_fast64_t (treap.depth()) - int_fast64_t (binomialTree.depth()));

    return 0;
}