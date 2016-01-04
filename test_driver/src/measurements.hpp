// Copyright 2016 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://sourceforge.net/projects/jsoncons/files/ for latest version
// See https://sourceforge.net/p/jsoncons/wiki/Home/ for documentation.

#ifndef JSON_BENCHMARKS_MEASUREMENTS_HPP
#define JSON_BENCHMARKS_MEASUREMENTS_HPP

#include <chrono>

namespace json_benchmarks {

struct measurements
{
    size_t memory_used;
    size_t time_to_read;
    size_t memory_leaks;
};

}

#endif

