# JSON Benchmarks

The purpose of these benchmarks is to measure how [jsoncons](https://github.com/danielaparker/jsoncons) compares to other `json` libraries.

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
[jsoncons](https://github.com/danielaparker/jsoncons)|5.796|1.374|1088|
[rapidjson](https://github.com/miloyip/rapidjson)|2.472|0.904|576|
[nlohmann](https://github.com/nlohmann/json)|16.458|11.47|2742|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|16.158|8.816|3345|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|118.362|10.382|2937|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|1.587|17.67|538|No serialization function, using sample pretty-print code

