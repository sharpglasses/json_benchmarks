#include <iostream>
#include <fstream>
#include "measurements.hpp"
#include "features.hpp"
#include <string>

using namespace json_benchmarks;
	
void make_big_file(const char *filename, size_t count);

measurements benchmark_jsoncons(const char *input_filename, const char *output_filename);
measurements benchmark_rapidjson(const char *input_filename, const char *output_filename);
measurements benchmark_nlohmann(const char *input_filename, const char *output_filename);
measurements benchmark_json_spirit(const char *input_filename, const char *output_filename);
measurements benchmark_jsoncpp(const char *input_filename, const char *output_filename);
measurements benchmark_gason(const char *input_filename, const char *output_filename);

features features_jsoncons();
features features_rapidjson();
features features_nlohmann();
features features_json_spirit();
features features_jsoncpp();
features features_gason();

void output_measurements(std::ostream& os, measurements const & results)
{
    os << results.library_name
       << "|" << (results.time_to_read/1000.0) 
       << "|" << (results.time_to_write/1000.0) 
       << "|" << (results.memory_used)
       << "|" << results.remarks
       << std::endl; 
}

void output_features(std::ostream& os, features const & list)
{
    os << list.library_name
       << "|" << list.default_construction
       << "|" << list.default_result
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

        measurements results = benchmark_jsoncons("data/input/persons.json", "data/output/persons-jsoncons.json");
        output_measurements(os,results);

        results = benchmark_rapidjson("data/input/persons.json", "data/output/persons-rapidjson.json");
        output_measurements(os,results);

        results = benchmark_nlohmann("data/input/persons.json", "data/output/persons-nlohmann.json");
        output_measurements(os,results);

		results = benchmark_jsoncpp("data/input/persons.json", "data/output/persons-jsoncpp.json");
        output_measurements(os,results);

        results = benchmark_json_spirit("data/input/persons.json", "data/output/persons-json_spirit.json");
        output_measurements(os,results);

		results = benchmark_gason("data/input/persons.json", "data/output/persons-gason.json");
		output_measurements(os, results);

        os << std::endl;
        os << "## API Comparison\n\n";
        os << "### Default value\n\n";
        os << "Library|Code|Result" << std::endl;
        os << "---|---|---" << std::endl;

        features list = features_jsoncons();
        output_features(os,list);
        list = features_rapidjson();
        output_features(os,list);
        list = features_nlohmann();
        output_features(os,list);
        list = features_json_spirit();
        output_features(os,list);
        list = features_jsoncpp();
        output_features(os,list);
        list = features_gason();
        output_features(os,list);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

