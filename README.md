# US Census TIGER\Line Shape File Parser Library

[![Build Status](https://travis-ci.com/arunkumar-mourougappane/tiger-boundary-mapper.svg?branch=master)](https://travis-ci.com/arunkumar-mourougappane/tiger-boundary-mapper)    [![CodeFactor](https://www.codefactor.io/repository/github/arunkumar-mourougappane/tiger-boundary-mapper/badge)](https://www.codefactor.io/repository/github/arunkumar-mourougappane/tiger-boundary-mapper) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/786d483d24a048f486f96da7dac45248)](https://www.codacy.com/manual/amouroug/tiger-boundary-mapper?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=arunkumar-mourougappane/tiger-boundary-mapper&amp;utm_campaign=Badge_Grade)


A mapper library to read and save Boundary data. This library is capable of parsing "RTC" and "BND" bounds file to data set that can be traversed with region ID as a key. The RTC and BND fine are provided from U.S. Census Bureau TIGER/Line data, a part of U.S. Census Bureau, are a digital database of geographic features, such as roads, railroads, rivers, lakes, political boundaries, census statistical boundaries, 
etc.

This Library parses through such files and serializes data into easily readable as well as searchable database entries.

# Class List

Here are the classes, structs, unions and interfaces with brief descriptions:


* **class** [**CPSQLWrapper**](markdown/class_c_p_s_q_l_wrapper.md) _A class wrapper for libpq library to store, query result perform commands and handle connections._   
* **class** [**CRtcBndWrapper**](markdown/class_c_rtc_bnd_wrapper.md) _A class to save RTC and BND information based on the region ID. The class instance can take in the bounds of the regions and create instance. Also, the data from instance can be serialized into string._   
* **class** [**CTigerShapeFileParser**](markdown/class_c_tiger_shape_file_parser.md) _Class defenition for C++ API to perform parsing the data files into an organized format of map and Bound infomation, which can then be serialized to database or searched through to find specific information._   