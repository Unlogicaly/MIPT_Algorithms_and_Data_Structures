#include <iostream>
#include <memory>
#include <cassert>

template <typename T>
struct Node {

    T val{};

    bool visited{false};

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

  public:

    BinaryTree() = default;

    explicit BinaryTree(const T &elem) : root(std::make_unique<Node<T>>(elem).release()), key{elem} {}

    void insert(const T &elem);

    void in_order(std::ostream &os);

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

template <typename T, class _Cmp>
void BinaryTree<T, _Cmp>::in_order(std::ostream &os) {

    if (!root)
        return;

    auto cur = root;

    while (cur) {

        if (cur->left and !cur->left->visited)
            cur = cur->left;

        else if (!cur->right) {
            os << cur->val << ' ';
            cur->visited = true;

            if (cur->left)
                cur->left->visited = false;

            cur = cur->parent;
        }

        else if (cur->right->visited) {
            cur->right->visited = false;

            if (cur->left)
                cur->left->visited = false;

            cur = cur->parent;
        }

        else {
            cur->visited = true;
            os << cur->val << ' ';
            cur = cur->right;
        }
    }

    this->root->visited = false;
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    BinaryTree<int_fast64_t> a{};

    for (auto i = 0; i < n; ++i) {
        int_fast64_t tmp;
        std::cin >> tmp;
        a.insert(tmp);
    }

    a.in_order(std::cout);

    return 0;
}