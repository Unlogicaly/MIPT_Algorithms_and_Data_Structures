#include <iostream>
#include <cassert>

struct node {

    int_fast32_t val{};
    node *next{nullptr};
};

node *create_cycled(uint_fast32_t tail, uint_fast32_t cycle) {

    assert(tail and cycle > 2);

    auto head = new node{};

    auto cur = head;

    int_fast32_t counter{1};

    for (auto i = 1; i < tail; ++i) {

        cur->next = new node{counter++};

        cur = cur->next;
    }

    auto cycle_node = new node{counter++};

    cur->next = cycle_node;
    cur = cycle_node;

    for (auto i = 1; i < cycle; ++i) {

        cur->next = new node{counter++};

        cur = cur->next;
    }

    cur->next = cycle_node;

    return head;
}

node *find_cycled(node *head) {

    auto slow = head->next, fast = slow->next;

    while (slow != fast) {

        slow = slow->next;
        fast = fast->next->next;
    }

    node *res = head;

    while (res != slow) {

        res = res->next;
        slow = slow->next;
    }

    return res;
}

int main() {

    uint_fast32_t tail{7}, cycle{6};

    auto head = create_cycled(tail, cycle);

    auto cycled = find_cycled(head);

    for (auto i = 0; i < tail; ++i)
        head = head->next;

    std::cout << head->val << '\n' << cycled->val;

    return 0;
}