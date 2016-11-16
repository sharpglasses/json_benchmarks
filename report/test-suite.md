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
Expected result|283|280|280|251|232|237
Expected success, parsing failed|0|0|0|0|0|2
Expected failure, parsing succeeded|0|1|1|32|49|44
Result undefined, parsing succeeded|18|19|12|26|28|30
Result undefined, parsing failed|17|16|23|9|7|5
Process stopped|0|2|2|0|2|0
