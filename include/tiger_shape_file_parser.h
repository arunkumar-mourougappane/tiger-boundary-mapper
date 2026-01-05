/**
 * @file tiger_shape_file_parser.h
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief A C++ API to parse RTC bound data information and 
 *        store them to Databse, search database by region name
 *        or its patter to obtain bounds informations.
 * @version 1.2
 * @date 01-25-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef TIGER_SHAPE_FILE_PARSER_H
#define TIGER_SHAPE_FILE_PARSER_H
#include <rtc_bnd_wrapper.h>
#include <psql_wrapper.h>
#include <map>
#include <string_view>
#include <string>

/**
 * @brief  Typedefenition for a map with region ID as key and
 *          CRtcBndWrapper as its value.
 */
using region_bnd_map_t = std::map<uint_least32_t, CRtcBndWrapper>;

/**
 * @brief enumeration of handling differnt region Types State, County, Subcounty
 *        Place.
 */
enum class region_type_e
{
   State=0,
   County=1,
   SubCounty=2,
   Place=3,
   invalid = 4
};

/**
 * @brief  Class defenition for C++ API to perform
 *         parsing the data files into an organized format
 *         of map and Bound infomation, which can then be
 *         serialized to database or searched through to
 *         find specific information.
 */
class CTigerShapeFileParser
{
   public:
      CTigerShapeFileParser(std::string_view rtcDataFile, std::string_view bndDataFile);
      CTigerShapeFileParser();
      ~CTigerShapeFileParser() = default;
      int_least32_t parseBndRTCFiles();
      int_least32_t saveParsedBndRTCData();
      [[nodiscard]] int_least32_t searchRegionByName(std::string_view regionName, region_bnd_map_t& regionMap, bool searchByPattern);
   
   private:
      region_bnd_map_t mStateBndMap;
      region_bnd_map_t mCountyBndMap;
      region_bnd_map_t mSubCountyBndMap;
      region_bnd_map_t mPlaceBndMap;
      CPSQLWrapper mPsqlWrapper;
      std::string mRtcDataFile;
      std::string mBndDataFile;
      
      [[nodiscard]] std::string trim(std::string_view str);
      int_least32_t parseBNDData();
      int_least32_t parseRTCData();
      int_least32_t serializeMapData( region_bnd_map_t regionMap, region_type_e regionType );
      [[nodiscard]] int_least32_t searchRegionByName(std::string_view regionName, region_bnd_map_t& regionMap, std::string_view tableName, bool searchByPattern);
      [[nodiscard]] std::string getRegionTableName(region_type_e regionType);
      
      // Database login parameters for PSQL Connection.
      static constexpr std::string_view PSQL_DBNAME = "shape_file_database";
      static constexpr std::string_view PSQL_PASSWORD = "FullMetalAlchemist#8";
      static constexpr std::string_view PSQL_USER = "amouroug";
      static constexpr std::string_view PSQL_HOSTNAME = "127.0.0.1";
};

#endif