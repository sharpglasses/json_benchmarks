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

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|0.99.5
[nlohmann](https://github.com/nlohmann/json)|2.0.7
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented))|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|5.562|1.155|1088|
[nlohmann](https://github.com/nlohmann/json)|14.747|10.249|2743|
[json11](https://github.com/dropbox/json11)|7.732|3.788|3643|
[rapidjson](https://github.com/miloyip/rapidjson)|2.552|0.814|605|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|13.997|7.566|3352|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|111.506|9.468|2113|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|1.497|15.691|1099|No serialization function, using sample pretty-print code

## Parsing comparisons

Results for [JSONTestSuite](https://github.com/nst/JSONTestSuite) and [JSON_checker](http://www.json.org/JSON_checker/) tests may be found [here](https://danielaparker.github.io/json_benchmarks/)

