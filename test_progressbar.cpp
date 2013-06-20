/*

    test_progressbar.cpp

    Test case for progressbar.hpp
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "progressbar.hpp"
#include "vendor/cpp-range/range.hpp"

using namespace std;

int main() {
    const int num_iterations = 111;
    const int verbosity      = 1;

    /* Initialize ProgressBar with number of iterations in the
       following loop
    */
    util::ProgressBar<decltype(num_iterations)> bar(num_iterations);

    for (const auto & i : util::range<int>(0, num_iterations)) {

        /* present output */
        if (verbosity > 0) bar.output(i);

        /* This only for demonstration purposes */
        std::chrono::milliseconds dura( 20000 );
        std::this_thread::sleep_for( dura );
    }

    return 0;
}