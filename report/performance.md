
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/input/persons.json|537.6|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Version|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|0.99.5|5.641|1.414|1088|
[rapidjson](https://github.com/miloyip/rapidjson)|2.0.7|2.331|0.839|576|
[nlohmann](https://github.com/nlohmann/json)|2.0.7|15.806|10.875|2742|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7|14.857|8.339|3345|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08|111.557|10.159|2927|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|master 20161107|1.631|16.482|538|No serialization function, using sample pretty-print code

