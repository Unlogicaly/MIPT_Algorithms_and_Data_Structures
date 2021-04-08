#include <iostream>
#include <string>
#include <stack>

int main() {

    std::ios::sync_with_stdio(false);

    std::string s1, s2;
    std::cin >> s1 >> s2;

    if (s1.size() != s2.size()) {
        std::cout << "NO";
        return 0;
    }

    int_fast32_t i = 0;
    int_fast32_t j = 0;

    std::stack<char> buffer;

    while (i < s1.size()) {

        if (s1[i] == s2[j]) {
            ++i;
            ++j;
        }

        else if (!buffer.empty() and buffer.top() == s2[j]) {
            buffer.pop();
            ++j;
        }

        else {
            buffer.push(s1[i]);
            ++i;
        }

        if (j >= s2.size()) {
            std::cout << "YES";
            return 0;
        }
    }

    while (true) {

        if (buffer.empty()) {
            std::cout << "YES";
            return 0;
        }

        if (buffer.top() != s2[j]) {
            break;
        }

        buffer.pop();
        ++j;
    }

    std::cout << "NO";

    return 0;
}