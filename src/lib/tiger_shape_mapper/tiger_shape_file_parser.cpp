/**
 * @file tiger_shape_file_parser.cpp
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief Implementation for Shape file parser library capable of keyword searches for
 *        region name.
 * @version 1.0
 * @date 01-25-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <tiger_shape_file_parser.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <errno.h>
#include <cstdlib>

/**
 * @brief Construct a new CTigerShapeFileParser object and set up PSQL instance internally.
 * 
 * @param rtcDataFile path to the '.RTC' file containing region ID and name in SSV format.
 * @param bndDataFile path to '.BND' file containing region ID, latitude and longitude info in CSV format.
 */
CTigerShapeFileParser::CTigerShapeFileParser(std::string_view rtcDataFile, std::string_view bndDataFile)
{
   mPsqlWrapper = CPSQLWrapper(PSQL_HOSTNAME, PSQL_DBNAME,PSQL_USER, PSQL_PASSWORD);
   mRtcDataFile = rtcDataFile;
   mBndDataFile = bndDataFile;
}

/**
 * @brief Construct a new CTigerShapeFileParser and only sets up a connection to PSQL Wrapper.
 *        This constructor call is used when only search option is needed.
 */
CTigerShapeFileParser::CTigerShapeFileParser()
{
   mPsqlWrapper = CPSQLWrapper(PSQL_HOSTNAME, PSQL_DBNAME,PSQL_USER, PSQL_PASSWORD);
}

/**
 * @brief Parses RTC and BND files and converts them into a map of bounds data information with
 *        the region ID as key.
 * 
 * @return int_least32_t 0 is returned on Success and -1 on failure. 
 */
int_least32_t CTigerShapeFileParser::parseRTCData()
{
   // open and read RTC Files
   std::ifstream regionIdNameFileStream(mRtcDataFile);
   // string containing region ID and region Name
   std::string regionIDNameString;
   // Save to individual params
   std::string idString, regionName;
   // Initial variable declaration - to be later assiged a new instance on successful read.
   CRtcBndWrapper rtcData;
   if(regionIdNameFileStream.is_open())
   {
      // reads the input file line by line
      while (getline(regionIdNameFileStream, regionIDNameString))
      {
         idString.clear();
         regionName.clear();
         // ignores the records having 1990 and choose only records having 2000 or blank spaces
         if (regionIDNameString[10] == '2' || regionIDNameString[10] == ' ')
         {
            regionName = trim(regionIDNameString.substr(52, 71));
            idString.clear();
            // Parse and add  region data.
            switch (regionIDNameString[24])
            {
               case 'S':
                  idString = regionIDNameString.substr(5, 2);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mStateBndMap.insert({rtcData.getRegionID(), rtcData});
                  break;
               case 'P':
                  idString = regionIDNameString.substr(5, 2) + regionIDNameString.substr(14, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mPlaceBndMap.insert({rtcData.getRegionID(), rtcData});
                  break;
               case 'C':
                  idString = regionIDNameString.substr(5, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mCountyBndMap.insert({rtcData.getRegionID(), rtcData});
                  break;
               case 'M':
                  idString =  regionIDNameString.substr(5, 2) + regionIDNameString.substr(14, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mSubCountyBndMap.insert({rtcData.getRegionID(), rtcData});
                  break;
            }
         }
      }
      // close file after read.
      regionIdNameFileStream.close();
   }
   else
   {
      // on failure to read return -1.
      std::cerr << "Cannot open file.\n";
      return -1;
   }
#ifdef DEBUG
   std::cout << "Parsed RTC Data Successfully.\n";
#endif
   return 0;
}

int_least32_t CTigerShapeFileParser::parseBNDData()
{
   // stream to convert region ID string to int
   //TODO: Remove string stream and streamline this function.
   std::stringstream stringToint;
   // Bounds infomartion read from file.
   std::string boundFileLineString;
   // All bounds co-ordinates and string information.
   std::string regionID,minLongitude,minLatitude,maxLongitude,maxLatitude;
   //open file.
   std::ifstream readBoundsFileStream(mBndDataFile);
   region_bnd_map_t stateBndMap, countyBndMap, placeBndMap, subCountyBndMap;
   
   if(readBoundsFileStream.is_open())
   {
      while(getline(readBoundsFileStream, boundFileLineString))
      {
         // Extract data from each line to corressponding entries.
         // RegionID followed by bounds Co-ordinates. 
         // 1301500-083243161+32578368-083208715+32607111
         uint_least32_t regionIDInt;
         regionID = boundFileLineString.substr(0,7);
         minLongitude =boundFileLineString.substr(7,10);
         minLatitude = boundFileLineString.substr(17,9);
         maxLongitude = boundFileLineString.substr(26,10);
         maxLatitude = boundFileLineString.substr(36,9);
         stringToint.clear();
         stringToint.str(regionID);
         stringToint >> regionIDInt;
         
         if (auto it = mStateBndMap.find(regionIDInt); it != mStateBndMap.end())
         {
             auto& [key, wrapper] = *it;
             wrapper.setMinLongitude(minLongitude);
             wrapper.setMinLatitude(minLatitude);
             wrapper.setMaxLatitude(maxLatitude);
             wrapper.setMaxLongitude(maxLongitude);
             stateBndMap.insert({regionIDInt, CRtcBndWrapper(regionID, wrapper.getRegionName(), minLatitude, minLongitude, maxLatitude, maxLongitude)});
         }

         if (auto it = mCountyBndMap.find(regionIDInt); it != mCountyBndMap.end())
         {
             auto& [key, wrapper] = *it;
             wrapper.setMinLongitude(minLongitude);
             wrapper.setMinLatitude(minLatitude);
             wrapper.setMaxLatitude(maxLatitude);
             wrapper.setMaxLongitude(maxLongitude);
             countyBndMap.insert({regionIDInt, CRtcBndWrapper(regionID, wrapper.getRegionName(), minLatitude, minLongitude, maxLatitude, maxLongitude)});
         }

         if (auto it = mPlaceBndMap.find(regionIDInt); it != mPlaceBndMap.end())
         {
             auto& [key, wrapper] = *it;
             wrapper.setMinLongitude(minLongitude);
             wrapper.setMinLatitude(minLatitude);
             wrapper.setMaxLatitude(maxLatitude);
             wrapper.setMaxLongitude(maxLongitude);
             placeBndMap.insert({regionIDInt, CRtcBndWrapper(regionIDInt, wrapper.getRegionName(), minLatitude, minLongitude, maxLatitude, maxLongitude)});
         }

         if (auto it = mSubCountyBndMap.find(regionIDInt); it != mSubCountyBndMap.end())
         {
             auto& [key, wrapper] = *it;
             wrapper.setMinLongitude(minLongitude);
             wrapper.setMinLatitude(minLatitude);
             wrapper.setMaxLatitude(maxLatitude);
             wrapper.setMaxLongitude(maxLongitude);
             subCountyBndMap.insert({regionIDInt, CRtcBndWrapper(regionID, wrapper.getRegionName(), minLatitude, minLongitude, maxLatitude, maxLongitude)});
         }
         
         // Clear all parsed data for loading next line.
         minLatitude.clear();
         minLongitude.clear();
         maxLatitude.clear();
         maxLongitude.clear();
         regionID.clear();
      }
      readBoundsFileStream.close();
   }
   else
   {
      std::cerr << "Cannot open file. ";
      return -1;
   }
   // Clear all incomplete maps. Update member  instances if they only have complete data.
   if(!stateBndMap.empty())
   {
      mStateBndMap = stateBndMap;
   }
   else
   {
      mStateBndMap.clear();
   }
   
   if(!placeBndMap.empty())
   {
      mPlaceBndMap = placeBndMap;
   }
   else
   {
      mPlaceBndMap.clear();
   }
   
   if(!countyBndMap.empty())
   {
      mCountyBndMap = countyBndMap;
   }
   else
   {
      mCountyBndMap.clear();
   }
   
   if(!subCountyBndMap.empty())
   {
      mSubCountyBndMap = subCountyBndMap;
   }
   else
   {
      mSubCountyBndMap.clear();
   }
#ifdef DEBUG
   std::cout << "Parsed BND Data Successfully.\n";
#endif
   return 0;
}
/**
 * @brief Parses RTC and BND Files given to the instance and populates all the member map information.
 * 
 * @return int_least32_t Returns 0 on Success and -1 on failure.
 */
int_least32_t CTigerShapeFileParser::parseBndRTCFiles()
{
   if(parseRTCData() == 0)
   {
      if( parseBNDData() != 0 )
      {
         std::cerr << "Failed to parse BND file.\n";
         return -1;
      }
   }
   else
   {
      std::cerr << "Failed to parse RTC file.\n";
      return -1;
   }
   return 0;
}
/**
 * @brief Performs the serialization of Map instances in memory to database entries.
 * 
 * @param regionMap - map that needs to be serialized.
 * @param regionType - map type to select table information.
 * @return int_least32_t  - Returns 0 on success, -1 on failure.
 */
int_least32_t CTigerShapeFileParser::serializeMapData( region_bnd_map_t regionMap, region_type_e regionType )
{
   std::string tableName;
   bool queryProcessingFailed = false;
   tableName = getRegionTableName(regionType);
   for(const auto& [id, wrapper] : regionMap)
   {
      // Insert query Statement.
      std::string queryString = "INSERT INTO "+tableName+" (ID,IName,Min_Latitude,Max_Latitude,Min_Longitude,Max_Longitude) values (" +
               std::to_string(wrapper.getRegionID()) +",'" + std::string(wrapper.getRegionName()) +"','"+
               std::string(wrapper.getMinLatitude())+"','"+std::string(wrapper.getMaxLatitude())+"','"+
               std::string(wrapper.getMinLongitude())+"','"+std::string(wrapper.getMaxLongitude())+ "') on conflict (id) do nothing;";
      // Check for success or failure.
      if( mPsqlWrapper.processQuery(queryString) != PGRES_COMMAND_OK )
      {
         queryProcessingFailed = true;
         std::cerr << mPsqlWrapper.getQueryErrorMessage() << std::endl;
      }
   }
   // on Failure return -1.
   if(queryProcessingFailed)
   {
      return -1;
   }
   else
   {
      return 0;
   }
}

/**
 * @brief Saves for all parsed RTC BND data of all regions read from file.
 * 
 * @return int_least32_t Returns 0 on success, -1 on failure and fatally exits if 
 *         there is database connection issues.
 */
int_least32_t CTigerShapeFileParser::saveParsedBndRTCData()
{
   bool queryProcessingFailed = false;
   // open a database connection.
   if(mPsqlWrapper.openConnection() != 0)
   {
      std::cout << "Cannot open connection.\n";
      exit(EXIT_FAILURE);
   }
   // Call for serialization of map information.
   if( serializeMapData(mStateBndMap, region_type_e::State) != 0)
   {
      queryProcessingFailed = true;
   }
   if( serializeMapData(mCountyBndMap, region_type_e::County) != 0)
   {
      queryProcessingFailed = true;
   }
   if( serializeMapData(mSubCountyBndMap, region_type_e::SubCounty) != 0)
   {
      queryProcessingFailed = true;
   }
   if( serializeMapData(mPlaceBndMap, region_type_e::Place)!= 0)
   {
      queryProcessingFailed = true;
   }
   // close on success
   if(mPsqlWrapper.closeConnection() != 0)
   {
      return -1;
   }
   // report error if query processing failed.
   if(queryProcessingFailed)
   {
      return -2;
   }
#ifdef DEBUG
   std::cout << "Shape Data Has been successfully Updated.\n";
#endif
   return 0;
}

/**
 * @brief Trim unwanted whitespace at end of string.
 * 
 * @param str - string to be trimmed.
 * @return std::string - result of trimmed string.
 */
/**
 * @brief Trim unwanted whitespace at end of string.
 * 
 * @param str - string to be trimmed.
 * @return std::string - result of trimmed string.
 */
std::string CTigerShapeFileParser::trim(std::string_view str)
{
   std::string returnString;
   for (size_t i = 0; i < str.size(); i++)
   {
      if((str[i] == ' ') && (i + 1 < str.size() && str[i+1] == ' '))
      {
         break;
      }
      else
      {
         returnString += str[i];
      }
    }
   return returnString;
}

/**
 * @brief A regtion Type to table name mapper that returns table name for the used region type.
 * 
 * @param regionType Region type from the enumeration region_type_e
 * @return std::string Table Name for the particular region name.
 */
std::string CTigerShapeFileParser::getRegionTableName(region_type_e regionType)
{
   std::string tableName = "";
   switch (regionType)
   {
      case region_type_e::State :
         tableName = "STATE";
         break;
      case region_type_e::County :
         tableName = "COUNTY";
         break;
      case region_type_e::Place :
         tableName = "PLACE";
         break;
      case region_type_e::SubCounty :
         tableName = "SUBCOUNTY";
         break; 
      default:
         break;
   }
   return tableName;
}

/**
 * @brief Search for keyword in region name.
 * 
 * @param regionName Keyword to search for.
 * @param regionMap Map to which results needs to be saved.
 * @param tableName Table to search under.
 * @param searchByPattern boolean to check for wildcard search.
 * @return int_least32_t returns 0 on success , -1 or -2 on failure and fatally exists if there si
 *         issue opening database connection.
 */
int_least32_t CTigerShapeFileParser::searchRegionByName (std::string_view regionName, region_bnd_map_t& regionMap, std::string_view tableName, bool searchByPattern)
{
   region_bnd_map_t bndRegionMap;
   // Set up a connection.
   if(mPsqlWrapper.openConnection() != 0)
   {
      std::cout << "Cannot open connection.\n";
      exit(EXIT_FAILURE);
   }
   
   // Search for whole word if wildcard option is disabled.
   if(!searchByPattern)
   {
      std::string queryToProcess = std::string("SELECT * FROM ") + std::string(tableName) +" WHERE iname = '" + std::string(regionName) +"';";
      ExecStatusType execStatus = mPsqlWrapper.processQuery(queryToProcess);
      if ( execStatus !=  PGRES_TUPLES_OK )
      {
         std::cout << "Program did not complete success fully." << std::endl;
      }
      else if (  execStatus == PGRES_EMPTY_QUERY )
      {
   #ifdef DEBUG
         std::cout << "Cannot find any entries from " << tableName << std::endl;
   #endif
         return -2;
      }
   }
   else
   {
      // Do a wild card based sanitized search.
      std::string queryToProcess  = std::string("SELECT * FROM ")+ std::string(tableName) +(" WHERE iname LIKE '%' || $1 || '%';");
      std::string regionNameStr(regionName);
      const char* iname = regionNameStr.c_str();
      int nParams = 1;
      const char *const paramValues[] = {iname};
      const int paramLengths[] = {(int)sizeof(iname)}; 
      ExecStatusType execStatus = mPsqlWrapper.processExecParamsQuery( queryToProcess, nParams, paramValues, paramLengths);
      if ( execStatus !=  PGRES_TUPLES_OK )
      {
         std::cout << "Program did not complete success fully." << std::endl;
      }
      else if (  execStatus == PGRES_EMPTY_QUERY )
      {
#ifdef DEBUG
         std::cout << "Cannot find any entries from " << tableName << std::endl;
#endif
         return -2;
      }
   }
   if(mPsqlWrapper.closeConnection() != 0)
   {
      return -1;
   }
#ifdef DEBUG
   if (mPsqlWrapper.GetResultSetSize() > 0)
   {
      std::cout << "Found a matching entry for " << regionName << " in " <<  tableName << std::endl;
   } 
#endif
   for (int resultIndex=0; resultIndex < mPsqlWrapper.GetResultSetSize(); resultIndex++)
   {
      // if any of the string is empty ignore it.
      if((PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,0) == 0) && (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,1) == 0) &&
         (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,2) == 0) && (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,3) == 0) &&
         (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,4) == 0) && (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,5) == 0))
      {
         std::string regionId = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,0));
         std::string regionNameRes = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,1));
         std::string minLatitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,2));
         std::string maxLatitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,3));
         std::string minLongitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,4));
         std::string maxLongitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,5));
         CRtcBndWrapper rtcBndWrapper = CRtcBndWrapper(regionId, regionNameRes, minLatitude, minLongitude, maxLatitude, maxLongitude);
         bndRegionMap.insert({rtcBndWrapper.getRegionID(), rtcBndWrapper});
      }
   }
   if(!bndRegionMap.empty())
   {
      regionMap = bndRegionMap;
      return 0;
   }
   return -1;
}

/**
 * @brief An API to search for region by whole name or by widcard.
 * 
 * @param regionName Keyword to use to serch for region information.
 * @param regionMap Map to save the results of search.
 * @param searchByPattern flag to decide to use wild card search or Whole Key word search.
 * @return int_least32_t returns 0 on success , -1 or -2 on failure and fatally exists if there si
 *         issue opening database connection.
 */
int_least32_t CTigerShapeFileParser::searchRegionByName(std::string_view regionName, region_bnd_map_t& regionMap, bool searchByPattern)
{
   int_least32_t regionTypeCount;
   region_bnd_map_t searchResults;
   std::string tableName;
   // Iterate and search by region Type.
   for (regionTypeCount = 0; regionTypeCount < static_cast<int>(region_type_e::invalid); regionTypeCount++)
   {
      region_bnd_map_t searchResultsByType;
      tableName = getRegionTableName((region_type_e)regionTypeCount);
      // Check if a region was found to match atleast.
      if( searchRegionByName(regionName, searchResultsByType, tableName, searchByPattern) == 0)
      {
         if(!searchResultsByType.empty())
         {
            searchResults.insert(searchResultsByType.begin(), searchResultsByType.end());
         }
      }
#ifdef DEBUG
      else
      {
         std::cout << "Cannot find any for region for " << regionName << " from " << tableName << std::endl;
      }
#endif
   }
   if (searchResults.empty())
   {
      return -1;
   }
   // Update the list of matching regions.
   regionMap = searchResults;
   return 0;
}
