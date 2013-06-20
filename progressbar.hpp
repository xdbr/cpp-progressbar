#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>    // std::max
#include <chrono>

template <typename ELEMENTCOUNT>
struct ProgressBar {
    // using namespace std::chrono;
    ELEMENTCOUNT                            elements = 0;
    unsigned int                            percent  = 0;
    std::map<ELEMENTCOUNT, unsigned int>    percentmap;
    // std::list<std::time_point>              tickmap;
    decltype(std::chrono::steady_clock::now()) last_time_;
    // auto start_registering = std::chrono::steady_clock::now();
    
    ProgressBar(ELEMENTCOUNT elems)
        : elements(elems)
        , percent(elems/100)
        , last_time_(std::chrono::steady_clock::now())
    {
        for (const auto & i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100}) {
            percentmap.insert(std::make_pair(i*percent, i));
        }
    }
    
    void output(ELEMENTCOUNT i) {
        auto it = percentmap.find(i);
        if (it != percentmap.end()) {
            
            auto now = std::chrono::steady_clock::now();
            
            auto diff = (now - last_time_);
                        
            auto eta = diff*distance(it, end(percentmap));
            auto tot = diff*100;
            
            last_time_ = now;
            
            std::cout << "\r" << it->second << "\% [ETA: " << 
                std::chrono::duration_cast<std::chrono::minutes>(tot).count() << " minutes total / " <<
                std::chrono::duration_cast<std::chrono::minutes>(eta).count() << " minutes left]";
            std::cout.flush();
        }
    }
};

#endif /* end of include guard: PROGRESSBAR_HPP */
