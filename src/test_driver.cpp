#include <iostream>
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

        measurements results = benchmark_jsoncons("data/input/persons.json",
                                                  "data/output/persons-jsoncons.json");

        std::cout << "jsoncons: time to read=" << (results.time_to_read/1000.0) << " seconds"
                  << ", time to write=" << (results.time_to_write/1000.0) << " seconds"
                  << ", memory footprint of json value=" << results.memory_used << " megabytes" 
            << std::endl;

        measurements results2 = benchmark_rapidjson("data/input/persons.json",
                                                    "data/output/persons-rapidjson.json");

        std::cout << "rapidjson: time to read=" << (results2.time_to_read/1000.0) << " seconds"
                  << ", time to write=" << (results2.time_to_write/1000.0) << " seconds"
                  << ", memory footprint of json value=" << results2.memory_used << " megabytes" 
            << std::endl;

        measurements results3 = benchmark_nlohmann("data/input/persons.json",
                                                   "data/output/persons-nlohmann.json");

        std::cout << "nlohmann: time to read=" << (results3.time_to_read/1000.0) << " seconds"
                  << ", time to write=" << (results3.time_to_write/1000.0) << " seconds"
                  << ", memory footprint of json value=" << results3.memory_used << " megabytes" 
            << std::endl;

		measurements results5 = benchmark_jsoncpp("data/input/persons.json",
			"data/output/persons-json_spirit.json");

		std::cout << "jsoncpp: time to read=" << (results5.time_to_read / 1000.0) << " seconds"
			<< ", time to write=" << (results5.time_to_write / 1000.0) << " seconds"
			<< ", memory footprint of json value=" << results5.memory_used << " megabytes"
			<< std::endl;

        measurements results4 = benchmark_json_spirit("data/input/persons.json",
                                                      "data/output/persons-json_spirit.json");

        std::cout << "json_spirit: time to read=" << (results4.time_to_read/1000.0) << " seconds"
                  << ", time to write=" << (results4.time_to_write/1000.0) << " seconds"
                  << ", memory footprint of json value=" << results4.memory_used << " megabytes" 
            << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}

