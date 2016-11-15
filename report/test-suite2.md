Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|0.99.4
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[nlohmann](https://github.com/nlohmann/json)|2.0.7
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented))|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

   |jsoncons|rapidjson|nlohmann|jsoncpp|json_spirit|gason
---|---|---|---|---|---|---
Expected result|35|35|35|29|25|26
Expected success, parsing failed|0|0|0|0|0|0
Expected failure, parsing succeeded|0|0|0|6|10|9
Result undefined, parsing succeeded|1|1|1|1|1|1
Result undefined, parsing failed|0|0|0|0|0|0
Process stopped|0|0|0|0|0|0
