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
[jsoncons](https://github.com/danielaparker/jsoncons)|5.944|1.554|1217|
[rapidjson](https://github.com/miloyip/rapidjson)|2.801|0.809|848|
[nlohmann](https://github.com/nlohmann/json)|23.408|9.778|2795|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|14.315|11.868|3354|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|123.764|10.832|2051|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|1.708|17.651|1139|No serialization function, using sample pretty-print code
