#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <chrono>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "vendor/cpp-range/range.hpp"

namespace util {
    
namespace chr = std::chrono;

template
<class timing_unit = chr::milliseconds >
struct ProgressBar
{
    
    typedef std::unordered_map<std::type_index, std::string>    type_names_t;
    typedef std::map<unsigned/*iter_num*/, unsigned/*%-equiv*/> percentmap_t;
    
    ProgressBar(unsigned elems)
        : elements  { (unsigned)elems }
        , percent   { elems/100 }
        , last_time_{ std::chrono::steady_clock::now() }
    {
        init_type_names();
        init_percent_map();
    }
    
    void init_type_names();
    void init_percent_map();
    void output(unsigned int i);
    
    unsigned int                                elements    = {0};
    unsigned int                                percent     = {0};
    percentmap_t                                percentmap;
    type_names_t                                type_names_;
    decltype(std::chrono::steady_clock::now())  last_time_;

};


template
<class timing_unit>
void
ProgressBar<timing_unit>::
init_type_names()
{
    type_names_[ std::type_index(typeid( chr::nanoseconds  )) ] = "nanoseconds";
    type_names_[ std::type_index(typeid( chr::microseconds )) ] = "microseconds";
    type_names_[ std::type_index(typeid( chr::milliseconds )) ] = "milliseconds";
    type_names_[ std::type_index(typeid( chr::seconds      )) ] = "seconds";
    type_names_[ std::type_index(typeid( chr::minutes      )) ] = "minutes";
    type_names_[ std::type_index(typeid( chr::hours        )) ] = "hours";
}


template
<class timing_unit>
void
ProgressBar<timing_unit>::
init_percent_map()
{
    for (const auto & i : util::range<unsigned>(0,100)) {
        percentmap.insert(std::make_pair(i*percent, i));
    }
}


template
<class timing_unit>
void
ProgressBar<timing_unit>::
output(unsigned int i)
{
    auto it = percentmap.find(i);
    if (it != percentmap.end()) {
    
        auto now = std::chrono::steady_clock::now();
    
        auto diff = (now - last_time_);
                
        auto eta = diff*distance(it, end(percentmap));
        auto tot = diff*100;
    
        last_time_ = now;
    
        std::cout << "\r" << it->second << "% [ETA: "
            << chr::duration_cast<timing_unit>(tot).count()
            << " " << type_names_[std::type_index(typeid(timing_unit))] << " total / "
            << chr::duration_cast<timing_unit>(eta).count()
            << " " << type_names_[std::type_index(typeid(timing_unit))] << " left]";
        std::cout.flush();
    }
}

} /* end of namespace util */
#endif /* end of include guard: PROGRESSBAR_HPP */
