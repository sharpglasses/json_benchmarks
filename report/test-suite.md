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
Expected result|285|278|288|252|233|238
Expected success, parsing failed|0|4|1|1|4|3
Expected failure, parsing succeeded|7|8|1|39|53|51
Result undefined, parsing succeeded|16|11|8|15|20|19
Result undefined, parsing failed|5|10|13|6|1|2
Process stopped|0|2|2|0|2|0
