# Performance Benchmark Report

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
[jsoncons](https://github.com/danielaparker/jsoncons)|5.759|1.276|1217|
[rapidjson](https://github.com/miloyip/rapidjson)|2.53|0.821|847|
[nlohmann](https://github.com/nlohmann/json)|22.946|9.585|2794|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|14.707|11.894|3355|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|116.362|9.21|2188|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|1.696|16.707|1137|No serialization function, using sample pretty-print code
