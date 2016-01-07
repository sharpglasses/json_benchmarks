#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <cstdio>
#include <chrono>
#include <fstream>
#include <iostream>
#include <cassert>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

using namespace json_benchmarks;
using namespace rapidjson;

measurements benchmark_rapidjson(const char *input_filename,
                                 const char* output_filename)
{
    size_t start_memory_used = 0;
    size_t end_memory_used = 0;
    size_t time_to_read = 0;
    size_t time_to_write = 0;

    start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();
    {
        Document d;
        try
        {
            auto start = high_resolution_clock::now();
            FILE* fp = fopen(input_filename, "rb"); // non-Windows use "r"
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));

            d.ParseStream(is);
            auto end = high_resolution_clock::now();
            time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            fclose(fp);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            exit(1);
        }
        end_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();
        {
            try
            {
                FILE* fp = fopen(output_filename, "wb"); // non-Windows use "w"
                assert(fp != nullptr);

                char writeBuffer[65536];
                FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

                Writer<FileWriteStream> writer(os);
                auto start = high_resolution_clock::now();
                d.Accept(writer);
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                fclose(fp);        
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    size_t final_memory_used = memory_measurer::virtual_memory_currently_used_by_current_process();
	
	measurements results;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.memory_leaks = final_memory_used > start_memory_used ? (final_memory_used - start_memory_used) : 0;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

