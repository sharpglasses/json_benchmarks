#include "measurements.hpp"
#include "tests/library_tests.hpp"
#include <vector>

namespace json_benchmarks {

    measurements measure_jsoncons(const char *input_filename, const char *output_filename);
    std::vector<test_suite_result> JsonTestSuite_jsoncons(std::vector<test_suite_file>& pathnames);

    measurements measure_rapidjson(const char *input_filename, const char *output_filename);
    std::vector<test_suite_result> JsonTestSuite_rapidjson(std::vector<test_suite_file>& pathnames);

    measurements measure_nlohmann(const char *input_filename, const char *output_filename);
    std::vector<test_suite_result> JsonTestSuite_nlohmann(std::vector<test_suite_file>& pathnames);

    measurements measure_jsoncpp(const char *input_filename, const char *output_filename);
    std::vector<test_suite_result> JsonTestSuite_jsoncpp(std::vector<test_suite_file>& pathnames);

    measurements measure_json_spirit(const char *input_filename, const char *output_filename);
    std::vector<test_suite_result> JsonTestSuite_json_spirit(std::vector<test_suite_file>& pathnames);

    measurements measure_gason(const char *input_filename, const char *output_filename);
    std::vector<test_suite_result> JsonTestSuite_gason(std::vector<test_suite_file>& pathnames);

    measurements measure_json11(const char *input_filename, const char *output_filename);
    std::vector<test_suite_result> JsonTestSuite_json11(std::vector<test_suite_file>& pathnames);

    std::vector<library_info> library_tests::get_library_info() 
    {
        std::vector<library_info> info;

        info.push_back(library_info{"jsoncons","https://github.com/danielaparker/jsoncons","0.99.5", "With strict_parse_error_handler, uses wjson if utf16" });
        info.push_back(library_info{"nlohmann","https://github.com/nlohmann/json","2.0.7", ""});
        info.push_back(library_info{"json11","https://github.com/dropbox/json11","master 20161125", ""});
        info.push_back(library_info{"rapidjson","https://github.com/miloyip/rapidjson","1.1.0", ""});
        info.push_back(library_info{"jsoncpp","https://github.com/open-source-parsers/jsoncpp","1.7.7", ""});
        info.push_back(library_info{"json_spirit","http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)","4.08", ""});
        info.push_back(library_info{"gason","https://github.com/vivkin/gason","master 20161107", ""});

        return info;
    }

    std::vector<measurements> library_tests::measure(const char *input_filename, const char *output_dir)
    {
        std::vector<measurements> tests;

        tests.push_back(measure_jsoncons(input_filename, "data/output/persons-jsoncons.json"));

        tests.push_back(measure_nlohmann(input_filename, "data/output/persons-nlohmann.json"));

        tests.push_back(measure_json11(input_filename, "data/output/persons-json11.json"));

        tests.push_back(measure_rapidjson(input_filename, "data/output/persons-rapidjson.json"));

        tests.push_back(measure_jsoncpp(input_filename, "data/output/persons-jsoncpp.json"));

        tests.push_back(measure_json_spirit(input_filename, "data/output/persons-json_spirit.json"));

        tests.push_back(measure_gason(input_filename, "data/output/persons-gason.json"));

        return tests;
    }

    std::vector<std::vector<test_suite_result>> library_tests::run_test_suite(std::vector<test_suite_file>& pathnames) const
    {
        std::vector<std::vector<test_suite_result>> results;

        results.push_back(JsonTestSuite_jsoncons(pathnames));

        results.push_back(JsonTestSuite_nlohmann(pathnames));

        results.push_back(JsonTestSuite_json11(pathnames));

        results.push_back(JsonTestSuite_rapidjson(pathnames));

        results.push_back(JsonTestSuite_jsoncpp(pathnames));

        results.push_back(JsonTestSuite_json_spirit(pathnames));

        results.push_back(JsonTestSuite_gason(pathnames));

        return results;
    }


}

