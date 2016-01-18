#include <chrono>
#include "jsoncons/json_serializer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

void make_big_file(const char *filename, size_t count)
{
    std::ofstream os(filename, std::ofstream::binary | std::ios_base::out| std::ios_base::trunc);
    if (os.bad() || !os.is_open())
    {
        throw jsoncons::json_exception_1<std::exception>("Cannot open file %s", std::string(filename));
    }

    jsoncons::output_format format;
    jsoncons::json_serializer handler(os, format, true);

    auto start = high_resolution_clock::now();

    handler.begin_json();
    handler.begin_array();
    for (size_t i = 0; i < count; i+=2)
    {
        handler.begin_object();
        handler.name("person");
        handler.begin_object();
        handler.name("first_name");
        handler.value("john");
        handler.name("last_name"   );
        handler.value("doe");
        handler.name("birthdate");
        handler.value("1998-05-13");
        handler.name("sex");
        handler.value("m");
        handler.name("salary");
        handler.value(70000);
        handler.name("married");
        handler.value(false);
        handler.name("interests");
        handler.begin_array();
        handler.value("Reading");
        handler.value("Mountain biking");
        handler.value("Hacking");
        handler.end_array();
        handler.name("favorites");
        handler.begin_object();
        handler.name("color");
        handler.value("blue");
        handler.name("sport");
        handler.value("soccer");
        handler.name("food");
        handler.value("spaghetti");
        handler.end_object();

        handler.end_object();
        handler.end_object();
    }
    for (size_t i = 0; i < count; i+=2)
    {
        handler.begin_object();
        handler.name("person");
        handler.begin_object();
        handler.name("first_name");
        handler.value("jane");
        handler.name("last_name"   );
        handler.value("doe");
        handler.name("birthdate");
        handler.value("1998-05-13");
        handler.name("sex");
        handler.value("f");
        handler.name("salary");
        handler.value(80000);
        handler.name("married");
        handler.value(true);
        handler.name("pets");
        handler.value(jsoncons::null_type());
        handler.name("interests");
        handler.begin_array();
        handler.value("Skiing");
        handler.value("Hiking");
        handler.value("Camoing");
        handler.end_array();
        handler.name("favorites");
        handler.begin_object();
        handler.name("color");
        handler.value("Red");
        handler.name("sport");
        handler.value("skiing");
        handler.name("food");
        handler.value("risotto");
        handler.end_object();

        handler.end_object();
        handler.end_object();
    }
    handler.end_array();
    handler.end_json();
    auto end = high_resolution_clock::now();
    auto time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Big file took " << (time_to_write/1000.0) << " seconds to write.\n";
}

