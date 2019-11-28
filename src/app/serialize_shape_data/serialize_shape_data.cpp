#include <iostream>
#include <string>
#include <cstdlib>
#include <dirent.h>

#include <tiger_shape_file_parser.h>


int main(int argc, const char** argv) 
{
   std::string rtcFile("./data_files/TGR17037.RTC");
   std::string bndFile("./data_files/state17s.bnd");
   CTigerShapeFileParser tigerShapeFileParser(rtcFile,bndFile);
   tigerShapeFileParser.parseBndRTCFiles();
   tigerShapeFileParser.saveParsedBndRTCData();
}