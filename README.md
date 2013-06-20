cpp-progressbar
===============

A very simple progress bar, usable in loops (C++11)

About
-----

This is only a first step and certainly extendable, e.g.

* customize output (in several ways)
    * where should the output go (instead of std::cout)
    * what should be displayed?
    * etc.
* better (finer) time-estimations
* ...

Usage
-----

    #include "progressbar.hpp"

    ...
    
    const int num_iterations = 111;
    
    util::ProgressBar<decltype(num_iterations)> bar(num_iterations);

    for (const auto & i : util::range<int>(0, num_iterations)) {

        /* present output */
        bar.output(i);

        ...
    }

More examples
-------------

See `test_progressbar.cpp` for an extended usage example

License
-------

WTFPL
