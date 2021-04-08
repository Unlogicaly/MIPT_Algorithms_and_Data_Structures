#include <functional>
#include <stack>
#include <memory>
#include <iostream>
#include <vector>

template <typename T>
struct deleter {
    T *src;

    explicit deleter(T *src) : src{src} {}

    ~deleter() {

        delete src;
    }
};

template <typename T>
struct Node {

    T val{};

    uint_fast64_t n{1}; // Amount of nodes at the subtree

    short diff{0};

    Node<T> *left{nullptr};

    Node<T> *right{nullptr};

    explicit Node(const T &elem) : val{elem} {}

    ~Node() {

        delete left;
        delete right;
    }
};

template <typename T>
uint_fast64_t n(Node<T> *node) {

    return (node ? node->n : 0);
}

template <typename T>
void update_n(Node<T> *node) {

    if (node)
        node->n = 1 + n(node->right) + n(node->left);
}

template <typename T, class _Cmp = std::less<>>
class AVLTree {
  private:

    Node<T> *root{nullptr};

    _Cmp cmp{};

    T key{};

    void small_left_rotation(Node<T> *node, bool balance = true);

    void small_right_rotation(Node<T> *node, bool balance = true);

    void big_left_rotation(Node<T> *node);

    void big_right_rotation(Node<T> *node);

    Node<T> *_first(Node<T> *root);

    Node<T> *_find_node(std::stack<Node<T> *> &path, const T &elem, Node<T> *root, bool ins, uint_fast64_t &pos);

    void replace(Node<T> *lhs, Node<T> *rhs);

    void del_node(std::stack<Node<T> *> &path, Node<T> *node, T &prev_val);

    void back_propagation_del(std::stack<Node<T> *> path, T &prev_val);

    void back_propagation_ins(std::stack<Node<T> *> path, T &prev_val);

  public:
    AVLTree() = default;

    explicit AVLTree(const T &elem) : root{std::make_unique<Node<T>>(elem).release()}, key{elem} {}

    uint_fast64_t insert(const T &elem);

    const T &get_i(uint_fast32_t num);

    bool del(const T &elem);

    ~AVLTree() {

        delete this->root;
    }
};

template <typename T, class _Cmp>
Node<T> *AVLTree<T, _Cmp>::_find_node(std::stack<Node<T> *> &path, const T &elem, Node<T> *_root, bool ins,
                                      uint_fast64_t &pos) {

    auto cur = _root;

    while (cur and cur->val != elem) {

        path.push(cur);

        ins ? ++cur->n : --cur->n;

        if (cmp(cur->val, elem)) {
            if (ins)
                pos += 1 + n(cur->left);
            cur = cur->right;
        }
        else
            cur = cur->left;
    }

    return cur;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::replace(Node<T> *lhs, Node<T> *rhs) {

    lhs->val = rhs->val;
    lhs->diff = rhs->diff;
    lhs->left = rhs->left;
    rhs->left = nullptr;
    lhs->right = rhs->right;
    rhs->right = nullptr;

    deleter<Node<T>>{rhs};
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::del_node(std::stack<Node<T> *> &path, Node<T> *node, T &prev_val) {

    --node->n;

    if (!node->right and !node->left) {

        if (path.empty()) {
            this->root = nullptr;
            return;
        }

        (path.top()->right == node ? path.top()->right : path.top()->left) = nullptr;

        deleter<Node<T>>{node};
    }

    else if (node->left and node->right) {

        auto tmp = node->right;

        path.push(node);

        while (tmp->left) {

            --tmp->n;

            path.push(tmp);
            tmp = tmp->left;
        }

        node->val = tmp->val;

        prev_val = tmp->val;

        del_node(path, tmp, prev_val);
    }
    else {

        auto tmp = (node->left ? node->left : node->right);

        replace(node, tmp);
    }
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::small_left_rotation(Node<T> *node, bool balance) {

    auto b = node->right;
    std::swap(node->val, b->val);
    node->right = b->right;
    b->right = b->left;
    auto t_node = node->left;
    node->left = b;
    b->left = t_node;

    update_n(node->left);
    update_n(node);

    if (balance) {
        node->diff = static_cast<short>(-(b->diff + 1));
        b->diff = static_cast<short>(std::abs(node->diff));
    }
    std::swap(node->diff, b->diff);
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::small_right_rotation(Node<T> *node, bool balance) {

    auto b = node->left;
    std::swap(node->val, b->val);
    node->left = b->left;
    b->left = b->right;
    auto t_node = node->right;
    node->right = b;
    b->right = t_node;

    update_n(node->right);
    update_n(node);

    if (balance) {
        node->diff = static_cast<short>(std::abs(b->diff - 1));
        b->diff = static_cast<short>(b->diff - 1);
    }
    std::swap(node->diff, b->diff);
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::big_left_rotation(Node<T> *node) {

    auto b = node->right;

    small_right_rotation(b, false);
    small_left_rotation(node, false);

    switch (node->diff) {
        case 0:
            node->right->diff = 0;
            b->diff = 0;
            break;
        case 1:
            node->right->diff = -1;
            b->diff = 0;
            break;
        case -1:
            node->right->diff = 0;
            b->diff = 1;
    }
    node->diff = 0;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::big_right_rotation(Node<T> *node) {

    auto b = node->left;

    small_left_rotation(b, false);
    small_right_rotation(node, false);

    switch (node->diff) {
        case 0:
            node->left->diff = 0;
            b->diff = 0;
            break;
        case 1:
            node->left->diff = 0;
            b->diff = -1;
            break;
        case -1:
            node->left->diff = 1;
            b->diff = 0;
            break;
    }
    node->diff = 0;
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::back_propagation_del(std::stack<Node<T> *> path, T &prev_val) {

    while (!path.empty()) {

        auto root = path.top();
        path.pop();
        cmp(root->val, prev_val) or !cmp(prev_val, root->val) ? ++root->diff : --root->diff;
        prev_val = root->val;

        if (!root->diff)
            continue;

        if (root->diff == 1 or root->diff == -1)
            break;

        if (root->diff == -2) {
            if (root->right->diff == 1)
                big_left_rotation(root);
            else
                small_left_rotation(root);
        }
        else {
            if (root->left->diff == -1)
                big_right_rotation(root);
            else
                small_right_rotation(root);
        }

        if (root->diff == 1 or root->diff == -1)
            break;
    }
}

template <typename T, class _Cmp>
void AVLTree<T, _Cmp>::back_propagation_ins(std::stack<Node<T> *> path, T &prev_val) {

    while (!path.empty()) {

        auto root = path.top();
        path.pop();
        cmp(root->val, prev_val) ? --root->diff : ++root->diff;
        prev_val = root->val;

        if (!root->diff)
            break;

        if (root->diff == 1 or root->diff == -1)
            continue;

        if (root->diff == -2) {
            if (root->right->diff == 1)
                big_left_rotation(root);
            else
                small_left_rotation(root);
        }
        else {
            if (root->left->diff == -1)
                big_right_rotation(root);
            else
                small_right_rotation(root);
        }

        if (!root->diff)
            break;
    }
}

template <typename T, class _Cmp>
uint_fast64_t AVLTree<T, _Cmp>::insert(const T &elem) {

    auto cur = this->root;

    if (!cur) {

        this->key = elem;

        this->root = std::make_unique<Node<T>>(elem).release();
        return 0;
    }

    this->key = std::min(key, elem, cmp);

    std::stack<Node<T> *> path{};

    uint_fast64_t res{0};

    _find_node(path, elem, this->root, true, res);

    cur = std::make_unique<Node<T>>(elem).release();

    (cmp(path.top()->val, elem) ? path.top()->right : path.top()->left) = cur;

    T prev_val{cur->val};

    back_propagation_ins(path, prev_val);

    return res;
}

template <typename T, class _Cmp>
Node<T> *AVLTree<T, _Cmp>::_first(Node<T> *root) {

    while (root->left)
        root = root->left;

    return root;
}

template <typename T, class _Cmp>
bool AVLTree<T, _Cmp>::del(const T &elem) {

    if (!this->root)
        return false;

    std::stack<Node<T> *> path{};

    uint_fast64_t _;

    auto cur = _find_node(path, elem, this->root, false, _);

    if (!cur)
        return false;

    T prev_val{cur->val};

    del_node(path, cur, prev_val);

    back_propagation_del(path, prev_val);

    if (this->root and this->key == elem) {
        this->key = this->_first(this->root)->val;
    }

    return true;
}

template <typename T, class _Cmp>
const T &AVLTree<T, _Cmp>::get_i(uint_fast32_t num) {

    uint_fast32_t count{0};

    auto cur = this->root;

    while (count + n(cur->left) != num) {

        if (!cur->left) {

            cur = cur->right;
            ++count;
        }

        else if (count == num)
            while (cur->left) {

                cur = cur->left;
            }

        else if (count + cur->left->n > num) {

            cur = cur->left;
        }

        else {

            count += 1 + n(cur->left);
            cur = cur->right;
        }
    }

    return cur->val;
}

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    int_fast64_t a;
    uint_fast64_t k;

    AVLTree<int_fast64_t> tree{};
    std::vector<int_fast64_t> result{};

    for (uint_fast64_t i = 0; i < n; ++i) {
        std::cin >> a >> k;

        if (a > 0) {
            tree.insert(a);
        }
        else
            tree.del(-a);

        result.push_back(tree.get_i(static_cast<uint_fast32_t>(k)));
    }

    for (auto i: result)
        std::cout << i << ' ';
}
