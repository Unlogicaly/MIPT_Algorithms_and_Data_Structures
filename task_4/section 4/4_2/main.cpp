#include <iostream>
#include <vector>

struct Node {

    short ind;

    int distance{};
    int subtrees{1};

    bool visited = false;
    std::vector<Node *> nodes{};
};

int dfs(Node *root, int depth) {

    root->visited = true;

    int c = 0;

    for (auto node: root->nodes) {

        if (!node->visited) {

            c += depth + dfs(node, depth + 1);
            root->subtrees += node->subtrees;
        }
    }

    root->visited = false;

    return c;
}

Node *parent(Node *node) {

    for (auto n: node->nodes) {

        if (n->ind < node->ind)
            return n;
    }
    return nullptr;
}

void calculate(std::vector<Node *> &nodes) {

    for (auto i = 1; i < nodes.size(); ++i) {

        nodes[i]->distance = parent(nodes[i])->distance + nodes[0]->subtrees - 2 * nodes[i]->subtrees;
    }
}

int main() {

    short n;
    std::cin >> n;

    std::vector<Node *> nodes{};

    nodes.reserve(n);

    for (short i = 0; i < n; ++i)
        nodes.push_back(new Node{i});

    short a, b;

    for (auto i = 0; i < n - 1; ++i) {

        std::cin >> a >> b;

        nodes[a]->nodes.push_back(nodes[b]);
        nodes[b]->nodes.push_back(nodes[a]);
    }

    nodes[0]->distance = dfs(nodes[0], 1);

    calculate(nodes);

    for (auto i :nodes) {
        std::cout << i->distance << '\n';
    }

    return 0;
}

