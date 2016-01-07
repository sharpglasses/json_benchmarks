# Performance Benchmark Report

Input filename|Size (MB)|Content
---|---|---
data/input/persons.json|564.6|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)
---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|6.756|1.5|1188
[rapidjson](https://github.com/miloyip/rapidjson)|2.569|0.806|850
[nlohmann](https://github.com/nlohmann/json)|22.904|9.76|2792
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|14.606|12.522|3356
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|122.568|9.063|2221
