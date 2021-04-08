#include <iostream>
#include <vector>

struct node{
    int_fast32_t val;
    node *next;
};

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast32_t n, k;
    std::cin >> n >> k;

    node head{1};
    node *cur = &head;

    for(auto i = 0; i < n - 1; ++i) {
        cur->next = new node{i + 2};
        cur = cur->next;
    }

    cur->next = &head;

    cur = &head;

    while (cur->next != cur) {

        for (auto i = 0; i < k - 2; ++i)
            cur = cur->next;

        cur->next = cur->next->next;
        cur = cur->next;
    }

    std::cout << cur->val;

    return 0;
}