//
// Created by tarog on 10.12.2019.
//

#ifndef TESTING_SORTS_TIMER_H
#define TESTING_SORTS_TIMER_H

#include <chrono>

class Timer {
  private:

    std::chrono::high_resolution_clock::time_point s, f;

  public:
    Timer() {start();}
    void start() {
      s = f = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        f = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(f - s).count() / 1000.;
    }
};


#endif //TESTING_SORTS_TIMER_H
