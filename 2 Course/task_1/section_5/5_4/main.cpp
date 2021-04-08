#include <iostream>
#include <vector>
#include <stack>
#include <queue>

struct operand {

    bool number;
    int_fast32_t num;
    char op;

    operand(bool number, int_fast32_t val) {
        this->number = number;
        if (number)
            num = val;
        else
            op = static_cast<char>(val);
    }
};

std::ostream &operator << (std::ostream &os, const operand &rhs) {
    if (rhs.number) {
        return os << rhs.num;
    }
    return os << rhs.op;
}

int_fast32_t calculate(int_fast32_t a, int_fast32_t b, char operation) {

    switch (operation) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            throw std::runtime_error("Unknown operation");
    }
}

void split_incoming(std::vector<operand> &result) {

    std::string s;
    std::getline(std::cin, s);

    std::string cur;
    for (auto i: s) {
        if (std::isdigit(i)) {
            cur += i;
            continue;
        }

        if (!cur.empty()) {
            result.emplace_back(true, std::stoi(cur));
            cur = "";
        }

        result.emplace_back(false, i);
    }

    if (!cur.empty()) {
        result.emplace_back(true, std::stoi(cur));
        cur = "";
    }
    else if(s.back() != ')')
        result.emplace_back(false, s.back());
}

bool less(const operand &lhs, const operand &rhs) { // lhs is less relevant than rhs
    return (lhs.op == '+' or lhs.op == '-');
}

void create_postfix(std::queue<operand> &result) {

    std::vector<operand> src;

    split_incoming(src);

    std::stack<operand> operators;

    for (auto op: src) {

        if (op.number)
            result.push(op);

        else {

            if (op.op == ')') {
                while (operators.top().op != '(') {
                    result.push(operators.top());
                    operators.pop();
                }
                operators.pop();
            }

            else if (op.op == '(') {
                operators.push(op);
            }

            else if (operators.empty() or operators.top().op == '(')
                operators.push(op);

            else if (!less(op, operators.top())) {
                operators.push(op);
            }

            else {
                while (!operators.empty() and operators.top().op != '(') {
                    result.push(operators.top());
                    operators.pop();
                }
                operators.push(op);
            }
        }
    }

    while (!operators.empty()) {
        result.push(operators.top());
        operators.pop();
    }
}

int_fast32_t compute(std::queue<operand> &src) {

    std::stack<int_fast32_t> res;

    while(!src.empty()) {

        auto cur = src.front();
        src.pop();

        if (cur.number) {
            res.push(cur.num);
            continue;
        }

        auto tmp = res.top();
        res.pop();

        res.top() = calculate(res.top(), tmp, cur.op);
    }

    return res.top();
}

int main() {

    std::queue<operand> res;

    create_postfix(res);

    std::cout << compute(res);

    return 0;
}