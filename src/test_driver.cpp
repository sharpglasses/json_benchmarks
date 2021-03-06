#include "tests/library_tests.hpp"

#include <iostream>
#include <fstream>
#include "measurements.hpp"
#include <string>
#include "json_parsing_report_generator.hpp"

using namespace json_benchmarks;

void make_big_file(const char *filename, size_t count);

void benchmarks()
{
    try
    {
        library_tests tests;

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

        os << "Library|Version" << std::endl;
        os << "---|---" << std::endl;
        auto info = tests.get_library_info();
        for (const auto& val : info)
        {
            os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
        }
        os << std::endl;

        os << "Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        auto measurements = tests.measure("data/input/persons.json","data/output/");
        for (const auto& results : measurements)
        {
            os << results.library_name
               << "|" << (results.time_to_read/1000.0) 
               << "|" << (results.time_to_write/1000.0) 
               << "|" << (results.memory_used)
               << "|" << results.remarks
               << std::endl; 
        }

        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void insert_JSONTestSuite(json_parsing_report_generator& generator)
{
    try
    {
        library_tests tests;
        std::vector<result_code_info> result_code_infos;
        result_code_infos.push_back(result_code_info{result_code::expected_result,"Expected result","#d19b73"});
        result_code_infos.push_back(result_code_info{result_code::expected_success_parsing_failed,"Expected success, parsing failed","#69005e"});
        result_code_infos.push_back(result_code_info{result_code::expected_failure_parsing_succeeded,"Expected failure, parsing succeeded","#001a75"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_succeeded,"Result undefined, parsing succeeded","#f7a8ff"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_failed,"Result undefined, parsing failed","#050f07"});
        result_code_infos.push_back(result_code_info{result_code::process_stopped,"Process stopped","#e00053"});

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
                switch (type)
                {
                case 'y':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_success,buffer});
                    break;
                case 'n':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_failure,buffer});
                    break;
                case 'i':
                    pathnames.push_back(test_suite_file{path,expected_result::result_undefined,buffer});
                    break;
                }
            }
        );

        std::stable_sort(pathnames.begin(),pathnames.end(),
                         [](const test_suite_file& a, const test_suite_file& b)
        {
            return a.type < b.type; 
        }
        );

        auto results = tests.run_test_suite(pathnames);

        generator.insert_results(pathnames,results);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void insert_JSON_checker(json_parsing_report_generator& generator)
{
    try
    {
        library_tests tests;
        std::vector<result_code_info> result_code_infos;
        result_code_infos.push_back(result_code_info{result_code::expected_result,"Expected result","#d19b73"});
        result_code_infos.push_back(result_code_info{result_code::expected_success_parsing_failed,"Expected success, parsing failed","#69005e"});
        result_code_infos.push_back(result_code_info{result_code::expected_failure_parsing_succeeded,"Expected failure, parsing succeeded","#001a75"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_succeeded,"Result undefined, parsing succeeded","#f7a8ff"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_failed,"Result undefined, parsing failed","#050f07"});
        result_code_infos.push_back(result_code_info{result_code::process_stopped,"Process stopped","#e00053"});

        std::vector<test_suite_file> pathnames;

        json_file_finder
        (
            "data/input/JSON_checker",
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
                switch (type)
                {
                case 'p':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_success,buffer});
                    break;
                case 'f':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_failure,buffer});
                    break;
                case 'i':
                    pathnames.push_back(test_suite_file{path,expected_result::result_undefined,buffer});
                    break;
                }
            }
        );

        std::stable_sort(pathnames.begin(),pathnames.end(),
                         [](const test_suite_file& a, const test_suite_file& b)
        {
            return a.type < b.type; 
        }
        );

        auto results = tests.run_test_suite(pathnames);

        generator.insert_results(pathnames,results);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    library_tests tests;
    std::ofstream os("report/library-info.md");
    os << "Library|Version" << std::endl;
    os << "---|---" << std::endl;
    auto info = tests.get_library_info();
    for (const auto& val : info)
    {
        os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
    }
    os << std::endl;

    benchmarks();
/*
    std::vector<result_code_info> result_code_infos;
    result_code_infos.push_back(result_code_info{result_code::expected_result,"Expected result","#d19b73"});
    result_code_infos.push_back(result_code_info{result_code::expected_success_parsing_failed,"Expected success, parsing failed","#69005e"});
    result_code_infos.push_back(result_code_info{result_code::expected_failure_parsing_succeeded,"Expected failure, parsing succeeded","#001a75"});
    result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_succeeded,"Result undefined, parsing succeeded","#f7a8ff"});
    result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_failed,"Result undefined, parsing failed","#050f07"});
    result_code_infos.push_back(result_code_info{result_code::process_stopped,"Process stopped","#e00053"});


    std::ofstream fs("docs/index.html");
    json_parsing_report_generator generator("Parser Comparisons", result_code_infos, library_tests::get_library_info(),fs);
    generator.insert_generator("JSON Test Suite",insert_JSONTestSuite);
    generator.insert_generator("JSON Checker",insert_JSON_checker);
    generator.generate();
*/
}

