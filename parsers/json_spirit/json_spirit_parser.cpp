#include <fstream>
#include "json_spirit/json_spirit_reader_template.h"
#include "json_spirit/json_spirit_writer_template.h"

using namespace json_spirit;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }
    try
    {
        Value val;
        std::fstream is(argv[1]);
        read_stream(is, val);
        return 0;
    }
    catch (const std::exception&)
    {
        return 1;
    }
}
