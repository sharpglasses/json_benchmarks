#include <fstream>
#include <chrono>
#include "nlohmann/json.hpp"
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace nlohmann;

const std::string library_name = "[nlohmann](https://github.com/nlohmann/json)";

measurements measure_nlohmann(const char *input_filename,
                               const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();

        nlohmann::json root;
        {
            try
            {
                auto start = high_resolution_clock::now();
                std::ifstream is(input_filename);
                is >> root;
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
            os << root;
            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }
    size_t final_memory_used = memory_measurer::virtual_memory_currently_used_by_current_process();
    
    measurements results;
    results.library_name = library_name;
    results.version = "2.0.7";
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

measurements JsonTestSuite_nlohmann()
{
    json_file_finder
    (
        "data/input/JSONTestSuite",
        [](const std::string& filename) 
        {
            if (filename[0] == 'y')
            {
                try
                {
                    if (filename.find("utf16") == std::string::npos)
                    {
                        nlohmann::json val;
                        std::ifstream is(filename.c_str());
                        is >> val;
                    }
                }
                catch (const std::exception&)
                {
                    // failure
                }
            }
            else if (filename[0] == 'n')
            {
                try
                {
                    nlohmann::json val;
                    std::ifstream is(filename.c_str());
                    is >> val;
                    // failure
                }
                catch (const std::exception&)
                {
                    // success
                }
            }
        }
    );
}
