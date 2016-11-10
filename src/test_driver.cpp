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

std::vector<test_suite_results> JsonTestSuite_jsoncons(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_results> JsonTestSuite_rapidjson(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_results> JsonTestSuite_nlohmann(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_results> JsonTestSuite_json_spirit(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_results> JsonTestSuite_jsoncpp(std::vector<test_suite_file>& pathnames);
std::vector<test_suite_results> JsonTestSuite_gason(std::vector<test_suite_file>& pathnames);

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

void test_suite_report(std::ostream& os, 
                       std::vector<test_suite_file>& pathnames,
                       const std::vector<std::vector<test_suite_results>>& results)
{
os << R"(
<!DOCTYPE html>
<html>
)";
os << R"(
    <head>
      <title>Parsing Tests</title>
      <style>
          th.rotate {
            /* Something you can count on */
            height: 140px;
            white-space: nowrap;
          }

          th.rotate > div {
            transform: 
              /* Magic Numbers */
              translate(25px, 51px)
              /* 45 is really 360 - 45 */
              rotate(315deg);
            width: 30px;
          }
          th.rotate > div > span {
            border-bottom: 1px solid #ccc;
            padding: 5px 10px;
      }
      </style>
    </head>
)";

os << R"(
    <body>
    <h2>JSON Parsing Tests</h2>
    <table>
        <tr><td bgcolor="#d19b73"><font color="white">Expected result</font></td></tr> 
        <tr><td bgcolor="#69005e"><font color="white">Expected success, parsing failed</font></td></tr> 
        <tr><td bgcolor="#001a75"><font color="white">Expected failure, parsing failed</font></td></tr> 
        <tr><td bgcolor="#f7a8ff"><font color="white">Result undefined, parsing succeeded</font></td></tr> 
        <tr><td bgcolor="#050f07"><font color="white">Result undefined, parsing failed</font></td></tr> 
        <tr><td bgcolor="#e00053"><font color="white">Process stopped</font></td></tr> 
    </table>
)";
os << R"(
    <table style="width:100%">
    <tr>
      <th></th>
      <th class="rotate"><div><span>jsoncons</span></div></th> 
      <th class="rotate"><div><span>rapidjson</span></div></th> 
      <th class="rotate"><div><span>nlohmann</span></div></th> 
      <th class="rotate"><div><span>jsoncpp</span></div></th> 
      <th class="rotate"><div><span>json_spirit</span></div></th> 
      <th class="rotate"><div><span>gason</span></div></th> 
      <th></th>
    </tr>
)";

for (size_t i = 0; i < pathnames.size(); ++i)
{
os << "<tr>\n";
os << "<td>";
os << pathnames[i].path.filename().string().c_str();
os << "</td>";
    for (size_t j = 0; j < results.size(); ++j)
    {
switch (results[j][i].result)
{
case test_results::expected_result:
    os << "<td bgcolor=\"#d19b73\"></td>\n";
    break;
case test_results::expected_success_parsing_failed:
    os << "<td bgcolor=\"#69005e\"></td>\n";
    break;
case test_results::expected_failure_parsing_succeeded:
    os << "<td bgcolor=\"#001a75\"></td>\n";
    break;
case test_results::result_undefined_parsing_succeeded:
    os << "<td bgcolor=\"#f7a8ff\"></td>\n";
    break;
case test_results::result_undefined_parsing_failed:
    os << "<td bgcolor=\"#050f07\"></td>\n";
    break;
case test_results::process_stopped:
    os << "<td bgcolor=\"#e00053\"></td>\n";
    break;
default:
    break;
}
}
os << "<td>";
os << pathnames[i].text;
os << "</td>\n";
os << "</tr>\n";
}

os << R"(
    </table>
)";
os << R"(
    </body>
</html>
)";

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

        std::vector<std::vector<test_suite_results>> results;

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

