#include <iostream>
#include "measurements.hpp"
#include <string>

namespace json_benchmarks {
    
class json_parsing_report_generator
{
private:
    const size_t max_text_length = 30;
    std::string title_;
    std::vector<result_code_info> result_code_info_;
    std::vector<library_info> library_info_;
public:

    json_parsing_report_generator(std::string title,
                                  const std::vector<result_code_info>& result_code_info,
                                  const std::vector<library_info>& library_info)
        : title_(title),
          result_code_info_(result_code_info), 
          library_info_(library_info)
    {
    }

void generate_report(std::vector<test_suite_file>& pathnames,
                     const std::vector<std::vector<test_suite_result>>& results,
                     std::ostream& os)
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
            height: 140px;
            white-space: nowrap;
          }

          th.rotate > div {
            transform: 
              translate(25px, 51px)
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
)";
os << "<h2>" << std::endl;
os << title_;
os << "</h2>" << std::endl;
os << R"(
    <table>
    <tr>
      <th></th>
)";
for (const auto& lib : library_info_)
{
    os << "<th class=\"rotate\"><div><span>";
    os << lib.name;
    os << "</span></div></th>\n"; 
}
os << R"(
    </tr>
)";

for (size_t i = 0; i < result_code_info_.size(); ++i)
{
    os << "<tr><td bgcolor=\"";
    os << result_code_info_[i].color << "\">";
    os << "<font color=\"white\">";
    os << result_code_info_[i].description << "</font></td>";
    for (size_t j = 0; j < results.size(); ++j)
    {
        size_t count = count_results(results[j],result_code_info_[i].code);
        os << "<td>" << count << "</td>\n";
    }
    os << "</tr>\n";
}

os << R"(
    </table>
)";
os << R"(
    </table>
    <table style="width:100%">
    <tr>
      <th></th>
)";
for (const auto& lib : library_info_)
{
    os << "<th class=\"rotate\"><div><span>";
    os << lib.name;
    os << "</span></div></th>\n"; 
}
os << R"(
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
        result_code rc = results[j][i].result;
        auto it = std::find_if(result_code_info_.begin(),
                            result_code_info_.end(),
                  [rc](const result_code_info& a){return a.code == rc;});
        if (it != result_code_info_.end())
        {
            os << "<td bgcolor=\"";
            os << (*it).color;
            os << "\"></td>\n";
        }
    }
    size_t max_length = pathnames[i].text.length();
    if (max_length > max_text_length)
    {
        max_length = max_text_length;
    }
os << "<td>";
os << pathnames[i].text.substr(0,max_length);
if (max_length < pathnames[i].text.length())
{
    os << " ...";
}
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

};

}
