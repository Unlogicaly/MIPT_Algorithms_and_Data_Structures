#include <iostream>
#include <cmath>
#include <map>
#include <queue>
#include <deque>
#include <stack>

struct bracket {

    short type;

    short pair() {

        return static_cast<short>(type + pow(-1, type));
    }

    explicit bracket(char ch, const std::map<short, char> &brackets) {
        for (auto i: brackets) {
            if (i.second == ch) {
                type = i.first;
                break;
            }
        }
    }
};

#include <fstream>

int main() {

    std::ios::sync_with_stdio(false);

    std::map<short, char> brackets{{0, '('}, {1, ')'}, {2, '['}, {3, ']'}, {4, '{'}, {5, '}'}};

    char ch;;

    ch = getchar();

    if (std::isspace(ch))
        return 0;

    std::stack<bracket> seq;
    seq.emplace(ch, brackets);

    std::vector<char> all{ch};

    ch = getchar();

    while (ch != EOF) {
        bracket tmp{ch, brackets};
        all.push_back(ch);

        if (!seq.empty() and tmp.type == seq.top().pair() and tmp.type > seq.top().type) {
            seq.pop();
        }

        else {
            if (!seq.empty() and ((seq.top().type + 3) % 6 == tmp.type or (seq.top().type + 5) % 6 == tmp.type) and !(seq.top().type % 2)) {
                std::cout << "IMPOSSIBLE\n";
                return 0;
            }

            seq.emplace(ch, brackets);
        }

        ch = getchar();
    }

    std::queue<char> left;

    while (!seq.empty()) {
        auto cur = seq.top();

        if (cur.type % 2) {
            left.push(brackets[cur.pair()]);
        }

        else {
            all.push_back(brackets[cur.pair()]);
        }

        seq.pop();
    }

    while (!left.empty()) {
        std::cout << left.front();
        left.pop();
    }

    for (auto i: all) {
        std::cout << i;
    }

    return 0;
}
