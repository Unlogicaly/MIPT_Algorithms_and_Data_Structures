//
// Created by tarog on 19.11.2019.
//

#ifndef TRACEBACK_TRACER_H
#define TRACEBACK_TRACER_H

#include <iostream>

#define NO_TRACING

class Tracer {
public:
    Tracer(const char *function, const char *file, int line);

    Tracer(const Tracer &) = delete;

    Tracer &operator=(const Tracer &) = delete;

    ~Tracer();

private:
    static int level;
    std::string func;

    std::string indent() const;

    // disallow copying
};

#ifndef NO_TRACING
#define TRACE(func) Tracer tracer_object{(func), __FILE__, __LINE__}

#else
#define TRACE(func)
#endif

#define TRACE_FUNC TRACE(__func__)

#endif //TRACEBACK_TRACER_H
