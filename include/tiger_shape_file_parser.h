#ifndef TIGER_SHAPE_FILE_PARSER_H
#define TIGER_SHAPE_FILE_PARSER_H
#include <rtc_bnd_wrapper.h>
#include <psql_wrapper.h>
#include <map>

typedef std::map<uint_least32_t,CRtcBndWrapper> region_bnd_map_t;

typedef enum
{
   State=0,
   County=1,
   SubCounty=2,
   Place=3
} region_type_e;

class CTigerShapeFileParser
{
   public:
      CTigerShapeFileParser(std::string& rtcDataFile, std::string& bndDataFile);
      CTigerShapeFileParser();
      ~CTigerShapeFileParser(){};
      int_least32_t parseBndRTCFiles();
      int_least32_t saveParsedBndRTCData();

   private:
      region_bnd_map_t mStateBndMap;
      region_bnd_map_t mCountyBndMap;
      region_bnd_map_t mSubCountyBndMap;
      region_bnd_map_t mPlaceBndMap;
      CPSQLWrapper mPsqlWarapper;
      std::string mRtcDataFile;
      std::string mBndDataFile;
      std::string trim(std::string str);
      int_least32_t parseBNDData();
      int_least32_t parseRTCData();
      int_least32_t serializeMapData( region_bnd_map_t regionMap,region_type_e regionType );

      static constexpr const char* PSQL_DBNAME = "amouroug";
      static constexpr const char* PSQL_PASSWORD = "FullMetalAlchemist#8";
      static constexpr const char* PSQL_USER = "amouroug";
      static constexpr const char* PSQL_HOSTNAME = "localhost";
};

#endif