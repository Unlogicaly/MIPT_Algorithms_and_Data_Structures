#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {

    for (auto i = 0; i < 10000; ++i) {
        auto a = new int_fast32_t[1000];
        a = nullptr;
    }

    _CrtDumpMemoryLeaks();

    return 0;

}
