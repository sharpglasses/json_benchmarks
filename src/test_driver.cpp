#include <iostream>
#include <fstream>
#include "measurements.hpp"
#include <string>

using namespace json_benchmarks;
    
void make_big_file(const char *filename, size_t count);

measurements measure_jsoncons(const char *input_filename, const char *output_filename);
measurements measure_rapidjson(const char *input_filename, const char *output_filename);
measurements measure_nlohmann(const char *input_filename, const char *output_filename);
measurements measure_json_spirit(const char *input_filename, const char *output_filename);
measurements measure_jsoncpp(const char *input_filename, const char *output_filename);
measurements measure_gason(const char *input_filename, const char *output_filename);

void output_measurements(std::ostream& os, measurements const & results)
{
    os << results.library_name
       << "|" << results.version
       << "|" << (results.time_to_read/1000.0) 
       << "|" << (results.time_to_write/1000.0) 
       << "|" << (results.memory_used)
       << "|" << results.remarks
       << std::endl; 
}

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
        os << std::endl;
        os << "## Read and Write Time Comparison" << std::endl << std::endl;
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
 
        os << "Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        measurements results = measure_jsoncons("data/input/persons.json", "data/output/persons-jsoncons.json");
        output_measurements(os,results);

        results = measure_rapidjson("data/input/persons.json", "data/output/persons-rapidjson.json");
        output_measurements(os,results);

        results = measure_nlohmann("data/input/persons.json", "data/output/persons-nlohmann.json");
        output_measurements(os,results);

        results = measure_jsoncpp("data/input/persons.json", "data/output/persons-jsoncpp.json");
        output_measurements(os,results);

        results = measure_json_spirit("data/input/persons.json", "data/output/persons-json_spirit.json");
        output_measurements(os,results);

        results = measure_gason("data/input/persons.json", "data/output/persons-gason.json");
        output_measurements(os, results);

        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

