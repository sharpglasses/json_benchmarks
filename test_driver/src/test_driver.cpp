#include <iostream>
#include "measurements.hpp"

using namespace json_benchmarks;
	
measurements benchmark_jsoncons(const char *input_filename, const char *output_filename);
measurements benchmark_rapidjson(const char *input_filename, const char *output_filename);

int main()
{
    measurements results = benchmark_jsoncons("data/input/persons.json",
                                              "data/output/persons-jsoncons.json");

	std::cout << "jsoncons: time_to_read=" << (results.time_to_read/1000.0) << " seconds"
              << ", time_to_write=" << (results.time_to_write/1000.0) << " seconds"
              << ", memory_used=" << results.memory_used << " megabytes" 
              << ", memory leaks=" << results.memory_leaks << " megabytes" << std::endl
        ;

    measurements results2 = benchmark_rapidjson("data/input/persons.json",
                                                "data/output/persons-rapidjson.json");

    std::cout << "rapidjson: time_to_read=" << (results2.time_to_read/1000.0) << " seconds"
              << ", time_to_write=" << (results2.time_to_write/1000.0) << " seconds"
              << ", memory_used=" << results2.memory_used << " megabytes" 
              << ", memory leaks=" << results2.memory_leaks << " megabytes" << std::endl
        ;
}

