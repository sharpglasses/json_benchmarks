// Copyright 2016 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://sourceforge.net/projects/jsoncons/files/ for latest version
// See https://sourceforge.net/p/jsoncons/wiki/Home/ for documentation.

#ifndef JSON_BENCHMARKS_MEASUREMENTS_HPP
#define JSON_BENCHMARKS_MEASUREMENTS_HPP

#include <chrono>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace json_benchmarks {

template <class F>
void json_file_finder(const char* dir_name, F f)
{
    boost::filesystem::path p{ dir_name };

    if (exists(p) && is_directory(p))
    {
        boost::filesystem::directory_iterator end_iter;
        for (boost::filesystem::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            if (is_regular_file(dir_itr->status()))
            {
                if (dir_itr->path().extension() == ".json")
                {
                    f(dir_itr->path().string());
                }
            }
        }
    }
}

struct measurements
{
    std::string library_name;
    std::string version;
    size_t memory_used;
    size_t time_to_read;
    size_t time_to_write;
    std::string remarks;
};

}

#endif

