
# Class CTigerShapeFileParser


[**Class List**](../README.md) **>** [**CTigerShapeFileParser**](class_c_tiger_shape_file_parser.md)



_Class defenition for C++ API to perform parsing the data files into an organized format of map and Bound infomation, which can then be serialized to database or searched through to find specific information._ 

* `#include <tiger_shape_file_parser.h>`















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CTigerShapeFileParser**](class_c_tiger_shape_file_parser.md#function-ctigershapefileparser-1-2) (std::string & rtcDataFile, std::string & bndDataFile) <br>_Construct a new_ [_**CTigerShapeFileParser**_](class_c_tiger_shape_file_parser.md) _object and set up PSQL instance internally._ |
|   | [**CTigerShapeFileParser**](class_c_tiger_shape_file_parser.md#function-ctigershapefileparser-2-2) () <br>_Construct a new_ [_**CTigerShapeFileParser**_](class_c_tiger_shape_file_parser.md) _and only sets up a connection to PSQL Wrapper. This constructor call is used when only search option is needed._ |
|  int\_least32\_t | [**parseBndRTCFiles**](class_c_tiger_shape_file_parser.md#function-parsebndrtcfiles) () <br>_Parses RTC and BND Files given to the instance and populates all the member map information._  |
|  int\_least32\_t | [**saveParsedBndRTCData**](class_c_tiger_shape_file_parser.md#function-saveparsedbndrtcdata) () <br>_Saves for all parsed RTC BND data of all regions read from file._  |
|  int\_least32\_t | [**searchRegionByName**](class_c_tiger_shape_file_parser.md#function-searchregionbyname-1-2) (std::string & regionName, [**region\_bnd\_map\_t**](tiger__shape__file__parser_8h.md#typedef-region-bnd-map-t) & regionMap, bool searchByPattern) <br>_An API to search for region by whole name or by widcard._  |
|   | [**~CTigerShapeFileParser**](class_c_tiger_shape_file_parser.md#function-ctigershapefileparser) () <br> |








## Public Functions Documentation


### <a href="#function-ctigershapefileparser-1-2" id="function-ctigershapefileparser-1-2">function CTigerShapeFileParser [1/2]</a>


```cpp
CTigerShapeFileParser::CTigerShapeFileParser (
    std::string & rtcDataFile,
    std::string & bndDataFile
) 
```




**Parameters:**


* `rtcDataFile` path to the '.RTC' file containing region ID and name in SSV format. 
* `bndDataFile` path to '.BND' file containing region ID, latitude and longitude info in CSV format. 



        

### <a href="#function-ctigershapefileparser-2-2" id="function-ctigershapefileparser-2-2">function CTigerShapeFileParser [2/2]</a>


```cpp
CTigerShapeFileParser::CTigerShapeFileParser () 
```



### <a href="#function-parsebndrtcfiles" id="function-parsebndrtcfiles">function parseBndRTCFiles </a>


```cpp
int_least32_t CTigerShapeFileParser::parseBndRTCFiles () 
```




**Returns:**

int\_least32\_t Returns 0 on Success and -1 on failure. 




        

### <a href="#function-saveparsedbndrtcdata" id="function-saveparsedbndrtcdata">function saveParsedBndRTCData </a>


```cpp
int_least32_t CTigerShapeFileParser::saveParsedBndRTCData () 
```




**Returns:**

int\_least32\_t Returns 0 on success, -1 on failure and fatally exits if there is database connection issues. 




        

### <a href="#function-searchregionbyname-1-2" id="function-searchregionbyname-1-2">function searchRegionByName [1/2]</a>


```cpp
int_least32_t CTigerShapeFileParser::searchRegionByName (
    std::string & regionName,
    region_bnd_map_t & regionMap,
    bool searchByPattern
) 
```




**Parameters:**


* `regionName` Keyword to use to serch for region information. 
* `regionMap` Map to save the results of search. 
* `searchByPattern` flag to decide to use wild card search or Whole Key word search. 



**Returns:**

int\_least32\_t returns 0 on success , -1 or -2 on failure and fatally exists if there si issue opening database connection. 




        

### <a href="#function-ctigershapefileparser" id="function-ctigershapefileparser">function ~CTigerShapeFileParser </a>


```cpp
inline CTigerShapeFileParser::~CTigerShapeFileParser () 
```



------------------------------
The documentation for this class was generated from the following file `include/tiger_shape_file_parser.h`