
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/input/persons.json|564.6|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|6.021|1.395|1212|
[rapidjson](https://github.com/miloyip/rapidjson)|2.359|0.777|845|
[nlohmann](https://github.com/nlohmann/json)|21.961|9.482|2796|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|14.502|7.36|3353|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|111.186|8.701|1197|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|1.578|15.814|1133|No serialization function, using sample pretty-print code

## API Comparison

### Default value

Library|Code|Result
---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|`json val;` `std::cout << val;`|{}
[rapidjson](https://github.com/miloyip/rapidjson)|`Value val;``char buffer[255];` `FileWriteStream os(stdout, buffer, sizeof(buffer));` `Writer<FileWriteStream> writer(os);` `val.Accept(writer);` `os.Flush();`|null
[nlohmann](https://github.com/nlohmann/json)|`json val;` `std::cout << val;`|null
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|`Value val;` `write_stream(val, std::cout);`|null
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|`Value val;` `std::cout << val;`|null
[gason](https://github.com/vivkin/gason)|`JsonValue val;` `dumpValue(val);`|null
