
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
[jsoncons](https://github.com/danielaparker/jsoncons)|5.12|1.599|1181|
[rapidjson](https://github.com/miloyip/rapidjson)|2.9|0.962|846|
[nlohmann](https://github.com/nlohmann/json)|23.384|9.824|2796|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|14.6|7.458|3355|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|118.78|9.209|2203|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|1.646|16.491|1130|No serialization function, using sample pretty-print code

## API Comparison

### Default value

Library|Code|Result
---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|`json val;` `std::cout << val;`|{}
[rapidjson](https://github.com/miloyip/rapidjson)|`Value val;``char buffer[255];` `FileWriteStream os(stdout, buffer, sizeof(buffer));` `Writer<FileWriteStream> writer(os);` `val.Accept(writer);` `os.Flush();`|null
[nlohmann](https://github.com/nlohmann/json)|`json val;` `std::cout << val;`|null
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|`Value val;` `write_stream(val, std::cout);`|null
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|`Value val;` `std::cout << val;`|null
