#include <iostream>
#include <fstream>
#include "measurements.hpp"
#include <string>

using namespace json_benchmarks;

void test_suite_report(std::ostream& os, 
                       std::vector<test_suite_file>& pathnames,
                       const std::vector<std::vector<test_suite_result>>& results);
    
void make_big_file(const char *filename, size_t count);

measurements measure_jsoncons(const char *input_filename, const char *output_filename);
measurements measure_rapidjson(const char *input_filename, const char *output_filename);
measurements measure_nlohmann(const char *input_filename, const char *output_filename);
measurements measure_json_spirit(const char *input_filename, const char *output_filename);
measurements measure_jsoncpp(const char *input_filename, const char *output_filename);
measurements measure_gason(const char *input_filename, const char *output_filename);

std::vector<test_suite_result> JsonTestSuite_jsoncons(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_result> JsonTestSuite_rapidjson(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_result> JsonTestSuite_nlohmann(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_result> JsonTestSuite_json_spirit(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_result> JsonTestSuite_jsoncpp(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_result> JsonTestSuite_gason(std::vector<test_suite_file>& pathnames);

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

void benchmarks()
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

        os << "Library|Version|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks" << std::endl;
        os << "---|---|---|---|---|---" << std::endl;

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

void test_suite()
{
    try
    {
        std::vector<test_suite_file> pathnames;

        json_file_finder
        (
            "data/input/JSONTestSuite",
            [&](const boost::filesystem::path& path) 
            {
                std::string buffer;
                {
                    std::ifstream fs(path.string(), std::ios::in|std::ios::binary|std::ios::ate);
                    if (fs.is_open())
                    {
                        size_t size = fs.tellg();
                        buffer.resize(size);
                        fs.seekg (0, std::ios::beg);
                        fs.read (&buffer[0], size);
                    }
                }
                char type = path.filename().string().c_str()[0];
                pathnames.push_back(test_suite_file{path,type,buffer});
            }
        );

        std::stable_sort(pathnames.begin(),pathnames.end(),
                         [](const test_suite_file& a, const test_suite_file& b)
        {
            return b.type < a.type; 
        }
        );

        std::vector<std::vector<test_suite_result>> results;

        auto results1 = JsonTestSuite_jsoncons(pathnames);

        auto results2 = JsonTestSuite_rapidjson(pathnames);

        auto results3 = JsonTestSuite_nlohmann(pathnames);

        auto results4 = JsonTestSuite_jsoncpp(pathnames);

        auto results5 = JsonTestSuite_json_spirit(pathnames);

        auto results6 = JsonTestSuite_gason(pathnames);

        results.push_back(results1);
        results.push_back(results2);
        results.push_back(results3);
        results.push_back(results4);
        results.push_back(results5);
        results.push_back(results6);

        std::ofstream fs("report/test-suite.html");
        test_suite_report(fs,pathnames,results);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    //benchmarks();
    test_suite();
}

