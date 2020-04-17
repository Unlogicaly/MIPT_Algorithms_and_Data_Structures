//
// Created by tarog on 19.11.2019.
//

#include "tracer.h"

int Tracer::level = 0;

Tracer::Tracer(const char *function, const char *file, int line) : func{function} {
    std::cerr << indent() << "IN --> " << func << " [" << file << ": " << line << "]" << std::endl;
    ++level;
}

Tracer::~Tracer() {
    --level;
    std::cerr << indent() << "OUT <-- " << func << std::endl;
}

std::string Tracer::indent() const {
    constexpr char tab[] = ". ";
    std::string space;

    for (decltype(level) i{0}; i < level; ++i)
        space += tab;

    return space;
}
