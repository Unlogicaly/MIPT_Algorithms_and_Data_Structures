//
// Created by tarog on 4/3/2020.
//

#ifndef UNTITLED3_DELETER_H
#define UNTITLED3_DELETER_H

template <typename T>
struct deleter {
    T *src;

    explicit deleter(T *src) : src{src} {}

    ~deleter() {

        delete src;
    }
};

#endif //UNTITLED3_DELETER_H
