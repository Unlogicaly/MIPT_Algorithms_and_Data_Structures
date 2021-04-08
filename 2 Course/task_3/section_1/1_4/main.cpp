#include <iostream>
#include <memory>
#include <cassert>
#include <queue>

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
class BinomialTree {

  private:

    T key{};

    Node<T> *root{nullptr};

    _Cmp cmp{};

  public:

    BinomialTree() = default;

    explicit BinomialTree(const T &elem) : root(std::make_unique<Node<T>>(elem).release()), key{elem} {}

    void insert(const T &elem);

    void in_order(std::ostream &os);

    void post_order(std::ostream &os);

    void pre_order(std::ostream &os);

    void level_order(std::ostream &os);

    ~BinomialTree() {

        delete root;
    }
};

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::insert(const T &elem) {

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
void BinomialTree<T, _Cmp>::in_order(std::ostream &os) {

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

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::post_order(std::ostream &os) {

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
            cur->visited = true;
            if (cur->left)
                cur->left->visited = false;

            os << cur->val << ' ';

            cur = cur->parent;
        }

        else {
            cur = cur->right;
        }
    }

    this->root->visited = false;
}

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::pre_order(std::ostream &os) {

    if (!root)
        return;

    auto cur = root;

    while (cur) {

        if (cur->left and !cur->left->visited) {
            os << cur->val << ' ';
            cur = cur->left;
        }

        else if (!cur->right) {
            if (!cur->left)
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
            if (!cur->left)
                os << cur->val << ' ';
            cur->visited = true;
            cur = cur->right;
        }
    }

    this->root->visited = false;
}

template <typename T, class _Cmp>
void BinomialTree<T, _Cmp>::level_order(std::ostream &os) {

    std::queue<Node<T> *> buffer{};

    buffer.push(this->root);

    while (!buffer.empty()) {

        if (buffer.front()->left)
            buffer.push(buffer.front()->left);
        if (buffer.front()->right)
            buffer.push(buffer.front()->right);

        os << buffer.front()->val << ' ';

        buffer.pop();
    }
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    BinomialTree<int_fast64_t> a{};

    for (auto i = 0; i < n; ++i) {
        int_fast64_t tmp;
        std::cin >> tmp;
        a.insert(tmp);
    }

    a.level_order(std::cout);

    return 0;
}