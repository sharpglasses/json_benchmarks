#include <assert.h>
#include <fstream>
#include <chrono>
#include <boost/filesystem.hpp>
#include "nlohmann/json.hpp"
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace nlohmann;

namespace json_benchmarks {

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
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> JsonTestSuite_nlohmann(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        std::string command = "build\\vs2015\\x64\\Release\\nlohmann_parser.exe ";
        command = command + file.path.string();
        int result = std::system(command.c_str());
        if (file.type == expected_result::expect_success)
        {
            if (result == 0)
            {
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
            else if (result == 1)
            {
                results.push_back(
                    test_suite_result{result_code::expected_success_parsing_failed}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::process_stopped}
                );
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            if (result == 0)
            {
                results.push_back(
                    test_suite_result{result_code::expected_failure_parsing_succeeded}
                );
            }
            else if (result == 1)
            {
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::process_stopped}
                );
            }
        }
        else if (file.type == expected_result::result_undefined)
        {
            if (result == 0)
            {
                results.push_back(
                    test_suite_result{result_code::result_undefined_parsing_succeeded}
                );
            }
            else if (result == 1)
            {
                results.push_back(
                    test_suite_result{result_code::result_undefined_parsing_failed}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::process_stopped}
                );
            }
        }
    }
    
    return results;
}
}
