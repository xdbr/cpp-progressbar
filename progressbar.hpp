#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <iostream>
#include <map>
#include <utility>
#include <chrono>

#include "vendor/cpp-range/range.hpp"

namespace util {
    template <typename ELEMENTCOUNT>
    struct ProgressBar {
        ELEMENTCOUNT                            elements = 0;
        unsigned int                            percent  = 0;
        std::map<ELEMENTCOUNT, unsigned int>    percentmap;

        decltype(std::chrono::steady_clock::now()) last_time_;
    
        ProgressBar(ELEMENTCOUNT elems)
            : elements(elems)
            , percent(elems/100)
            , last_time_(std::chrono::steady_clock::now())
        {
            for (const auto & i : util::range<int>(0,100)) {
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
            
                std::cout << "\r" << it->second << "% [ETA: " << 
                    std::chrono::duration_cast<std::chrono::minutes>(tot).count() << " minutes total / " <<
                    std::chrono::duration_cast<std::chrono::minutes>(eta).count() << " minutes left]";
                std::cout.flush();
            }
        }
    };
} /* end of namespace util */
#endif /* end of include guard: PROGRESSBAR_HPP */
