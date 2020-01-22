#include <iostream>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <getopt.h>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

#include <tiger_shape_file_parser.h>

void printUsage(std::string app_path)
{
   std::cout << app_path << " --rtc-dir RTC_DIR_PATH --bnd-dir BND_DIR_PATH [--contains] --search KEYWORD" << std::endl;
}
std::vector<std::string> listFiles(std::string &directoryPath, std::string fileType)
{
   DIR *dirFile = opendir(directoryPath.c_str());
   std::vector<std::string> filesFound;
   if (dirFile)
   {
      struct dirent *hFile;
      errno = 0;
      while ((hFile = readdir(dirFile)) != NULL)
      {
         if ((strcmp(hFile->d_name, ".") != 0) && (strcmp(hFile->d_name, "..") != 0) && (hFile->d_name[0] != '.'))
         {
            std::string fileString = std::string(hFile->d_name);
            if ((fileString.substr(fileString.length() - 4, 4)).compare(fileType) == 0)
            {
               filesFound.push_back(hFile->d_name);
            }
         }
      }
      closedir(dirFile);
   }
   return filesFound;
}

int main(int argc, char **argv)
{
   int c;
   std::string bndDir, rtcDir, keyWord;
   bool useAsWildcard = false;
   while (1)
   {
      int option_index = 0;
      static struct option long_options[] = {
          {"rtc-dir", required_argument, 0, 'r'},
          {"bnd-dir", required_argument, 0, 'b'},
          {"search",  required_argument, 0, 's'},
          {"contains", no_argument,      0, 'p' },
          {"help",    required_argument, 0, 'h' },
          {     0,      0,               0,  0}};

      c = getopt_long_only(argc, argv, "rbsp:h",
                           long_options, &option_index);
      if (c == -1)
         break;
      switch (c)
      {
      case 's':
         keyWord = std::string(optarg);
         break;
      case 'p':
         useAsWildcard =  true;
         break;
      case 'r':
         rtcDir = std::string(optarg);
         break;
      case 'b':
         bndDir = std::string(optarg);
         break;
      default:
         printUsage(argv[0]);
         exit(1);
      }
   }
   if (keyWord.length() != 0)
   {
      CTigerShapeFileParser tigerShapeFileParser;
      region_bnd_map_t bndMapDataMap;
      if (tigerShapeFileParser.searchRegionByName(keyWord, bndMapDataMap , useAsWildcard) == 0)
      {
         for (std::pair<uint_least32_t,CRtcBndWrapper> element : bndMapDataMap)
         {
            std::cout << element.second.to_string();
         }
      }
      else
      {
         std::cout << "No entry Found!" << std::endl;
      }
      return 0;
   }
   else if ((bndDir.length() == 0) || (rtcDir.length() == 0))
   {
      printUsage(argv[0]);
      return -1;
   }
   
   if (useAsWildcard)
   {
      printUsage(argv[0]);
      return -1;
   }

   std::vector<std::string> bndFiles = listFiles(bndDir, ".bnd");
   std::vector<std::string> rtcFiles = listFiles(rtcDir, ".RTC");

   for (auto rtcFile : rtcFiles)
   {
      std::string bndFilePath, rtcFilePath;
      rtcFilePath = rtcDir + rtcFile;
      for (auto &bndFile : bndFiles)
      {
         bndFilePath = bndDir + bndFile;
#ifdef DEBUG
         std::cout << "\nRTC File: " << rtcFile << " BND File: " << bndFile << std::endl;
#endif
         CTigerShapeFileParser tigerShapeFileParser(rtcFilePath, bndFilePath);
         tigerShapeFileParser.parseBndRTCFiles();
         tigerShapeFileParser.saveParsedBndRTCData();
      }
   }
   return 0;
}