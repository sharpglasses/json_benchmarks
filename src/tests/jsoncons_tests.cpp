#include "jsoncons/json.hpp"
#include "jsoncons/json_reader.hpp"
#include <chrono>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace jsoncons;

const std::string library_name = "[jsoncons](https://github.com/danielaparker/jsoncons)";

measurements measure_jsoncons(const char *input_filename,
                                const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();
        {
            jsoncons::json root;
            {
                auto start = high_resolution_clock::now();
                try
                {
                    root = jsoncons::json::parse_file(input_filename);
                    root.shrink_to_fit();
                    auto end = high_resolution_clock::now();
                    time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                    exit(1);
                }
            }
            end_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();
            {
                //char writeBuffer[65536];
                std::ofstream os; //(output_filename/*,std::ofstream::binary*/);
                //os.rdbuf()->pubsetbuf(writeBuffer, sizeof(writeBuffer));
                os.open(output_filename, std::ios_base::out | std::ios_base::binary);
                auto start = high_resolution_clock::now();
                os << root;
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
        }
    }
    size_t final_memory_used = memory_measurer::virtual_memory_currently_used_by_current_process();
    
    measurements results;
    results.library_name = library_name;
    results.version = "0.99.4";
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}


