#include <boost/chrono.hpp>
#include <boost/chrono/duration.hpp>
#include "jsoncons/json_serializer.hpp"

void make_big_file(const char *filename, size_t count);

int main()
{

    try
    {
        const char *filename = "data/input/persons.json";
        make_big_file(filename, 1000000);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void make_big_file(const char *filename, size_t count)
{
    std::ofstream os(filename, std::ofstream::binary | std::ios_base::out| std::ios_base::trunc);
    if (os.bad() || !os.is_open())
    {
        throw jsoncons::json_exception_1<char>("Cannot open file %s", std::string(filename));
    }
	std::cout << filename << std::endl;

    jsoncons::output_format format;
    jsoncons::json_serializer handler(os, format, true);

    boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();

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
    boost::chrono::duration<double> sec = boost::chrono::steady_clock::now() - start;
    os.flush();
    std::cout << "It took " << sec.count() << " seconds to write.\n";
    os.close();
}

