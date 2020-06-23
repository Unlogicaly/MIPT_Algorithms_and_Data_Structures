#include <iostream>
#include <vector>

struct node {

    int ind{};
    bool visited{false};
    int max_deep{};
    std::vector<std::pair<node *, int>> nodes{};
};

int _max_deep(node *cur) {

    if (cur->nodes.size() == 1 and (*cur->nodes.begin()).first->visited)
        return 0;

    int res{0};

    cur->visited = true;

    for (auto &n: cur->nodes) {

        if (n.first->visited)
            continue;

        if (n.second) {
            res = std::max(res, n.second);
            continue;
        }

        n.second = _max_deep(n.first);

        res = std::max(res, n.second);
    }

    cur->visited = false;

    return res + 1;
}

int main() {

    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<node *> nodes{};

    nodes.reserve(n);

    for (auto i = 0; i < n; ++i)
        nodes.push_back(new node{i});

    int a, b;

    for (auto i = 0; i < n - 1; ++i) {

        std::cin >> a >> b;

        nodes[a]->nodes.emplace_back(nodes[b], 0);
        nodes[b]->nodes.emplace_back(nodes[a], 0);
    }

    for (auto cur: nodes) {

        std::cout << _max_deep(cur) << "\n";
    }

    return 0;
}