
# Class CRtcBndWrapper


[**Class List**](../README.md) **>** [**CRtcBndWrapper**](class_c_rtc_bnd_wrapper.md)



_A class to save RTC and BND information based on the region ID. The class instance can take in the bounds of the regions and create instance. Also, the data from instance can be serialized into string._ 

* `#include <rtc_bnd_wrapper.h>`















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CRtcBndWrapper**](class_c_rtc_bnd_wrapper.md#function-crtcbndwrapper-1-4) (std::string regionID, std::string regionName, std::string minLatitude, std::string minLongitude, std::string maxLatitude, std::string maxLongitude) <br>_Construct a new_ [_**CRtcBndWrapper**_](class_c_rtc_bnd_wrapper.md) _object with Region and bounds information._ |
|   | [**CRtcBndWrapper**](class_c_rtc_bnd_wrapper.md#function-crtcbndwrapper-2-4) (uint\_least32\_t regionID, std::string regionName, std::string minLatitude, std::string minLongitude, std::string maxLatitude, std::string maxLongitude) <br>_Construct a new_ [_**CRtcBndWrapper**_](class_c_rtc_bnd_wrapper.md) _object with Region and bounds information._ |
|   | [**CRtcBndWrapper**](class_c_rtc_bnd_wrapper.md#function-crtcbndwrapper-3-4) (std::string regionID, std::string regionName) <br>_Construct a new_ [_**CRtcBndWrapper**_](class_c_rtc_bnd_wrapper.md) _objectt with Region information._ |
|   | [**CRtcBndWrapper**](class_c_rtc_bnd_wrapper.md#function-crtcbndwrapper-4-4) () <br> |
|  std::string | [**GetDecimalLatitude**](class_c_rtc_bnd_wrapper.md#function-getdecimallatitude) (std::string degreeDecimal) const<br>_Convert the numberal value of degress to degree, minute,seconds and direction._  |
|  std::string | [**GetDecimalLongitude**](class_c_rtc_bnd_wrapper.md#function-getdecimallongitude) (std::string degreeDecimal) const<br>_Convert the numberal value of degress to degree, minute,seconds and direction._  |
|  std::string | [**getMaxLatitude**](class_c_rtc_bnd_wrapper.md#function-getmaxlatitude) () const<br>_Getter for the Latitude end for the saved instance of region._  |
|  std::string | [**getMaxLongitude**](class_c_rtc_bnd_wrapper.md#function-getmaxlongitude) () const<br>_Getter for the Longitude end for the saved instance of region._  |
|  std::string | [**getMinLatitude**](class_c_rtc_bnd_wrapper.md#function-getminlatitude) () const<br>_Getter for the Latitude start for the saved instance of region._  |
|  std::string | [**getMinLongitude**](class_c_rtc_bnd_wrapper.md#function-getminlongitude) () const<br>_Getter for the Longitude start for the saved instance of region._  |
|  uint\_least32\_t | [**getRegionID**](class_c_rtc_bnd_wrapper.md#function-getregionid) () <br>_Getter for region ID._  |
|  std::string | [**getRegionName**](class_c_rtc_bnd_wrapper.md#function-getregionname) () <br>_Getter for the Region Name from instance._  |
|  void | [**setMaxLatitude**](class_c_rtc_bnd_wrapper.md#function-setmaxlatitude) (std::string maxLatitude) <br>_Setter for the Latitude end for the saved instance of region._  |
|  void | [**setMaxLongitude**](class_c_rtc_bnd_wrapper.md#function-setmaxlongitude) (std::string maxLongitude) <br>_Setter for the Longitude end for the saved instance of region._  |
|  void | [**setMinLatitude**](class_c_rtc_bnd_wrapper.md#function-setminlatitude) (std::string minLatitude) <br>_Setter for the Latitude start for the saved instance of region._  |
|  void | [**setMinLongitude**](class_c_rtc_bnd_wrapper.md#function-setminlongitude) (std::string minLongitude) <br>_Setter for the Longitude end for the saved instance of region._  |
|  std::string | [**to\_string**](class_c_rtc_bnd_wrapper.md#function-to-string) () const<br>_Used serialized the RTC and BND information from instance into a formatted string._  |
|   | [**~CRtcBndWrapper**](class_c_rtc_bnd_wrapper.md#function-crtcbndwrapper) () <br> |








## Public Functions Documentation


### <a href="#function-crtcbndwrapper-1-4" id="function-crtcbndwrapper-1-4">function CRtcBndWrapper [1/4]</a>


```cpp
CRtcBndWrapper::CRtcBndWrapper (
    std::string regionID,
    std::string regionName,
    std::string minLatitude,
    std::string minLongitude,
    std::string maxLatitude,
    std::string maxLongitude
) 
```




**Parameters:**


* `regionID` ID of the Region as integer 
* `regionName` Name of the region to be converted to object. 
* `minLatitude` Starting of the latitude bounds of the region. 
* `minLongitude` Starting of the Longitude bounds of the region. 
* `maxLatitude` Ending of the latitude bounds of the region. 
* `maxLongitude` Ending of the Longitude bounds of the region. 



        

### <a href="#function-crtcbndwrapper-2-4" id="function-crtcbndwrapper-2-4">function CRtcBndWrapper [2/4]</a>


```cpp
CRtcBndWrapper::CRtcBndWrapper (
    uint_least32_t regionID,
    std::string regionName,
    std::string minLatitude,
    std::string minLongitude,
    std::string maxLatitude,
    std::string maxLongitude
) 
```




**Parameters:**


* `regionID` ID of the Region as string. 
* `regionName` Name of the region to be converted to object. 
* `minLatitude` Starting of the latitude bounds of the region. 
* `minLongitude` Starting of the Longitude bounds of the region. 
* `maxLatitude` Ending of the latitude bounds of the region. 
* `maxLongitude` Ending of the Longitude bounds of the region. 



        

### <a href="#function-crtcbndwrapper-3-4" id="function-crtcbndwrapper-3-4">function CRtcBndWrapper [3/4]</a>


```cpp
CRtcBndWrapper::CRtcBndWrapper (
    std::string regionID,
    std::string regionName
) 
```




**Parameters:**


* `regionID` ID of the Region as string. 
* `regionName` Name of the region to be converted to object. 



        

### <a href="#function-crtcbndwrapper-4-4" id="function-crtcbndwrapper-4-4">function CRtcBndWrapper [4/4]</a>


```cpp
inline CRtcBndWrapper::CRtcBndWrapper () 
```



### <a href="#function-getdecimallatitude" id="function-getdecimallatitude">function GetDecimalLatitude </a>


```cpp
std::string CRtcBndWrapper::GetDecimalLatitude (
    std::string degreeDecimal
) const
```




**Parameters:**


* `degreeDecimal` decimal value of latitude co-ordinates.



**Returns:**

std::string Format string of latitude with degrees, minutes & seconds denomination. 




        

### <a href="#function-getdecimallongitude" id="function-getdecimallongitude">function GetDecimalLongitude </a>


```cpp
std::string CRtcBndWrapper::GetDecimalLongitude (
    std::string degreeDecimal
) const
```




**Parameters:**


* `degreeDecimal` decimal value of Longitude co-ordinates.



**Returns:**

std::string Format string of Longitude with degrees, minutes & seconds denomination. 




        

### <a href="#function-getmaxlatitude" id="function-getmaxlatitude">function getMaxLatitude </a>


```cpp
std::string CRtcBndWrapper::getMaxLatitude () const
```




**Returns:**

std::string Returns the immuatable string for end Latitude for the saved instance of region. 




        

### <a href="#function-getmaxlongitude" id="function-getmaxlongitude">function getMaxLongitude </a>


```cpp
std::string CRtcBndWrapper::getMaxLongitude () const
```




**Returns:**

std::string Returns the immuatable string for Ending Longitude for the saved instance of region. 




        

### <a href="#function-getminlatitude" id="function-getminlatitude">function getMinLatitude </a>


```cpp
std::string CRtcBndWrapper::getMinLatitude () const
```




**Returns:**

std::string Returns the immuatable string for Start Latitude for the saved instance of region. 




        

### <a href="#function-getminlongitude" id="function-getminlongitude">function getMinLongitude </a>


```cpp
std::string CRtcBndWrapper::getMinLongitude () const
```




**Returns:**

std::string Returns the immuatable string for Start Longitude for the saved instance of region. 




        

### <a href="#function-getregionid" id="function-getregionid">function getRegionID </a>


```cpp
uint_least32_t CRtcBndWrapper::getRegionID () 
```




**Returns:**

uint\_least32\_t Returns the region ID saved in the instance. 




        

### <a href="#function-getregionname" id="function-getregionname">function getRegionName </a>


```cpp
std::string CRtcBndWrapper::getRegionName () 
```




**Returns:**

std::string Returns the string for Region Name saved in the instance. 




        

### <a href="#function-setmaxlatitude" id="function-setmaxlatitude">function setMaxLatitude </a>


```cpp
void CRtcBndWrapper::setMaxLatitude (
    std::string maxLatitude
) 
```




**Parameters:**


* `maxLatitude` Ending Latitude numerals in std::string. 



        

### <a href="#function-setmaxlongitude" id="function-setmaxlongitude">function setMaxLongitude </a>


```cpp
void CRtcBndWrapper::setMaxLongitude (
    std::string maxLongitude
) 
```




**Parameters:**


* `maxLongitude` Ending Longitude numerals in std::string. 



        

### <a href="#function-setminlatitude" id="function-setminlatitude">function setMinLatitude </a>


```cpp
void CRtcBndWrapper::setMinLatitude (
    std::string minLatitude
) 
```




**Parameters:**


* `minLatitude` Starting Latitude numerals in std::string. 



        

### <a href="#function-setminlongitude" id="function-setminlongitude">function setMinLongitude </a>


```cpp
void CRtcBndWrapper::setMinLongitude (
    std::string minLongitude
) 
```




**Parameters:**


* `minLongitude` Starting Longitude numerals in std::string. 



        

### <a href="#function-to-string" id="function-to-string">function to\_string </a>


```cpp
std::string CRtcBndWrapper::to_string () const
```




**Returns:**

std::string Returns a formatted string containing RTC and BND infomation. 




        

### <a href="#function-crtcbndwrapper" id="function-crtcbndwrapper">function ~CRtcBndWrapper </a>


```cpp
inline CRtcBndWrapper::~CRtcBndWrapper () 
```



------------------------------
The documentation for this class was generated from the following file `include/rtc_bnd_wrapper.h`