#include <iostream>

int_fast32_t count5(size_t num) {
    int_fast32_t res = 0;
    while (!(num % 5)) {
        res++;
        num /= 5;
    }
    return res;
}

int_fast32_t count0(size_t num) {
    size_t tmp = 5;
    int_fast32_t res = 0;
    while (tmp <= num) {
        res += count5(tmp);
        tmp += 5;
    }
    return res;
}

int main() {

    std::ios::sync_with_stdio(false);

	size_t a;
	std::cin >> a;

	std::cout << count0(a);

    return 0;
}