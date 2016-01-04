#include "jsoncons/json.hpp"
#include "jsoncons/json_reader.hpp"
#include <chrono>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;

measurements benchmark_jsoncons(const char *input_filename)
{
    size_t start_memory;
    size_t end_memory;
    double sec;

    {
        start_memory =  memory_measurer::memory_available();
        auto start = high_resolution_clock::now();

        jsoncons::json root;
        {
            try
            {
                root = jsoncons::json::parse_file(input_filename);
                auto end = high_resolution_clock::now();
                sec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
            catch (...)
            {
                std::cout << "Exception" << std::endl;
                exit(1);
            }
        }
        end_memory =  memory_measurer::memory_available();
    }
    size_t final_memory = memory_measurer::memory_available();
	
	measurements results;
    results.memory_used = (start_memory - end_memory)/1000000;
    results.memory_leaks = start_memory > final_memory ? (start_memory - final_memory)/1000000 : 0;
    results.time_to_read = sec;
    return results;
    //std::ifstream is(input_filename, std::ios::in | std::ofstream::binary);
    //jsoncons::json_deserializer handler;
    //jsoncons::json_reader reader(is, handler);
    //try
    //{
    //    reader.read();
    //}
    //catch (...)
    //{
    //    std::cout << "Exception" << std::endl;
    //    exit(1);
    //}
    //jsoncons::json root;
    //root.swap(handler.root());

    //std::cout << root << std::endl;
}


