
//#include "json_spirit/json_spirit_reader.h"
//#include "json_spirit/json_spirit_writer.h"
#include "json_spirit/json_spirit_reader_template.h"
#include "json_spirit/json_spirit_writer_template.h"
#include <chrono>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include <fstream>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace json_spirit;

#ifndef JSON_SPIRIT_VALUE_ENABLED
#define JSON_SPIRIT_VALUE_ENABLED
#endif

const std::string library_name = "[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)";

measurements measure_json_spirit(const char *input_filename,
                                   const char *output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();

        Value root;
        {
            {
                auto start = high_resolution_clock::now();
                try
                {
                    std::ifstream is(input_filename);
                    read_stream(is, root);
                    auto end = high_resolution_clock::now();
                    time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                }
                catch (const std::exception & e)
                {
                    std::cout << e.what() << std::endl;
                    exit(1);
                }
            }
        }
        end_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();
        {
            //char writeBuffer[65536];
            std::ofstream os; //(output_filename/*,std::ofstream::binary*/);
                              //os.rdbuf()->pubsetbuf(writeBuffer, sizeof(writeBuffer));
            os.open(output_filename, std::ios_base::out | std::ios_base::binary);
            auto start = high_resolution_clock::now();
            write_stream(root,os);
            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }
    size_t final_memory_used = memory_measurer::virtual_memory_currently_used_by_current_process();

    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    results.remarks = "Boost spirit parsing is slow";
    return results;
}


