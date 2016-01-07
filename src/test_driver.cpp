#include <iostream>
#include <fstream>
#include "measurements.hpp"

using namespace json_benchmarks;
	
void make_big_file(const char *filename, size_t count);

measurements benchmark_jsoncons(const char *input_filename, const char *output_filename);
measurements benchmark_rapidjson(const char *input_filename, const char *output_filename);
measurements benchmark_nlohmann(const char *input_filename, const char *output_filename);
measurements benchmark_json_spirit(const char *input_filename, const char *output_filename);
measurements benchmark_jsoncpp(const char *input_filename, const char *output_filename);

int main()
{
    try
    {
        const char *filename = "data/input/persons.json";
        make_big_file(filename, 1200000);

        size_t file_size;
        {
                std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
                file_size = in.tellg(); 
        }

        std::ofstream os("report/performance.md");
		os << "# Performance Benchmark Report" << std::endl;
        os << std::endl;
        os << "Input filename|Size (MB)|Content" << std::endl;
        os << "---|---|---" << std::endl;
        os << filename << "|" << (file_size/1000000.0) << "|" << "Text,integers" << std::endl;
        os << std::endl;
        os << "Environment"
           << "|" << "Windows, Intel" << std::endl;
        os << "---|---" << std::endl;
        os << "Computer"
           << "|" << "Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD" << std::endl;
        os << "Operating system"
           << "|" << "Windows 2010" << std::endl;
        os << "Compiler"
           << "|" << "Visual Studio 2015" << std::endl;

        os << std::endl;

        os << "Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)" << std::endl;
        os << "---|---|---|---" << std::endl;

        measurements results = benchmark_jsoncons("data/input/persons.json",
                                                  "data/output/persons-jsoncons.json");
        os << "[jsoncons](https://github.com/danielaparker/jsoncons)"
           << "|" << (results.time_to_read/1000.0) 
           << "|" << (results.time_to_write/1000.0) 
           << "|" << (results.memory_used)
           << std::endl; 

        results = benchmark_rapidjson("data/input/persons.json",
                                                    "data/output/persons-rapidjson.json");
        os << "[rapidjson](https://github.com/miloyip/rapidjson)"
           << "|" << (results.time_to_read/1000.0) 
           << "|" << (results.time_to_write/1000.0) 
           << "|" << (results.memory_used)
           << std::endl; 

        results = benchmark_nlohmann("data/input/persons.json",
                                                   "data/output/persons-nlohmann.json");
        os << "[nlohmann](https://github.com/nlohmann/json)"
           << "|" << (results.time_to_read/1000.0) 
           << "|" << (results.time_to_write/1000.0) 
           << "|" << (results.memory_used)
           << std::endl; 

		results = benchmark_jsoncpp("data/input/persons.json",
			"data/output/persons-jsoncpp.json");
        os << "[jsoncpp](https://github.com/open-source-parsers/jsoncpp)"
           << "|" << (results.time_to_read/1000.0) 
           << "|" << (results.time_to_write/1000.0) 
           << "|" << (results.memory_used)
           << std::endl; 

        results = benchmark_json_spirit("data/input/persons.json",
                                                      "data/output/persons-json_spirit.json");
        os << "[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)"
           << "|" << (results.time_to_read/1000.0) 
           << "|" << (results.time_to_write/1000.0) 
           << "|" << (results.memory_used)
           << std::endl; 
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}

