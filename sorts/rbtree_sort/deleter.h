//
// Created by tarog on 4/6/2020.
//

#ifndef UNTITLED8_DELETER_H
#define UNTITLED8_DELETER_H


template <typename T>
struct deleter {
    T *src;

    explicit deleter(T *src) : src{src} {}

    ~deleter() {

        delete src;
    }
};


#endif //UNTITLED8_DELETER_H
