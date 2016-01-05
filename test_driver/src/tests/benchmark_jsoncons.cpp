#include "jsoncons/json.hpp"
#include "jsoncons/json_reader.hpp"
#include <chrono>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;

measurements benchmark_jsoncons(const char *input_filename,
                                const char* output_filename)
{
    size_t start_memory;
    size_t end_memory;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory =  memory_measurer::memory_available();

        jsoncons::json root;
        {
            auto start = high_resolution_clock::now();
            try
            {
                root = jsoncons::json::parse_file(input_filename);
                auto end = high_resolution_clock::now();
                time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
            catch (...)
            {
                std::cout << "Exception" << std::endl;
                exit(1);
            }
        }
        end_memory =  memory_measurer::memory_available();
        {
            std::ofstream os(output_filename,std::ofstream::binary);
            auto start = high_resolution_clock::now();
            os << root;
            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }
    size_t final_memory = memory_measurer::memory_available();
	
	measurements results;
    results.memory_used = (start_memory - end_memory)/1000000;
    results.memory_leaks = start_memory > final_memory ? (start_memory - final_memory)/1000000 : 0;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}


