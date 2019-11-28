#include <iostream>
#include <string>
#include <cstdlib>
#include <dirent.h>

#include <tiger_shape_file_parser.h>


int main(int argc, const char** argv) 
{
   std::string rtcFile("/home/amouroug/projects/tiger-boundary-mapper/data_files/TGR17037.RTC");
   std::string bndFile("/home/amouroug/projects/tiger-boundary-mapper/data_files/county.bnd");
   CTigerShapeFileParser tigerShapeFileParser(rtcFile,bndFile);
   if(tigerShapeFileParser.parseBndRTCFiles() != 0)
      return -1;
   return tigerShapeFileParser.saveParsedBndRTCData();
}