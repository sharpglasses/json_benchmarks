#include <fstream>
#include <chrono>
#include <iostream>
#include "json/json.h"
#include "../measurements.hpp"
#include "../features.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace Json;

const std::string library_name = "[jsoncpp](https://github.com/open-source-parsers/jsoncpp)";

measurements benchmark_jsoncpp(const char *input_filename,
                               const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();

        Value root;
        {
            try
            {
                auto start = high_resolution_clock::now();
                std::ifstream is(input_filename);
                is >> root;
                //Reader reader;
                //if (!reader.parse(input_filename, root))
                //{
                //    std::cerr << "jsoncpp failed." << std::endl;
                //}
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
            char writeBuffer[65536];
            std::ofstream os; //(output_filename/*,std::ofstream::binary*/);
            os.rdbuf()->pubsetbuf(writeBuffer, sizeof(writeBuffer));
            os.open(output_filename, std::ios_base::out | std::ios_base::binary);
            auto start = high_resolution_clock::now();
            //os << root;

            StyledWriter styledWriter;
            //std::ofstream writer(filename, std::ifstream::binary);
            os << styledWriter.write(root);

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
    return results;
}

features features_jsoncpp()
{
    std::cout << library_name << std::endl;
    // Default
    Value val;
    std::cout << val << std::endl;
    std::cout << std::endl;

    //root["key1"] = "value1";

    //Value a = root;
    //a["key1"] = "value2";

    //std::cout << "copy: " << root << "," << a << std::endl;


    features results;
    results.library_name = library_name;
    results.default_construction = "`Value val;` `std::cout << val;`";
    results.default_result = "null";

    return results;

}


