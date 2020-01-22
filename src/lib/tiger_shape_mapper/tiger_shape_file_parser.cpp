#include <tiger_shape_file_parser.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <errno.h>
#include <cstdlib>

CTigerShapeFileParser::CTigerShapeFileParser(std::string& rtcDataFile, std::string& bndDataFile)
{
   mPsqlWrapper = CPSQLWrapper(PSQL_HOSTNAME, PSQL_DBNAME,PSQL_USER, PSQL_PASSWORD);
   mRtcDataFile = rtcDataFile;
   mBndDataFile = bndDataFile;
}

CTigerShapeFileParser::CTigerShapeFileParser()
{
   mPsqlWrapper = CPSQLWrapper(PSQL_HOSTNAME, PSQL_DBNAME,PSQL_USER, PSQL_PASSWORD);
}

int_least32_t CTigerShapeFileParser::parseRTCData()
{
   std::stringstream stringToint;
   std::ifstream regionIdNameFileStream(mRtcDataFile);
   std::string regionIDNameString;
   std::string idString, regionName;
   CRtcBndWrapper rtcData;
   if(regionIdNameFileStream.is_open())
   {
      // reads the input file line by line
      while (getline(regionIdNameFileStream, regionIDNameString))
      {
         idString.clear();
         regionName.clear();
         /* ignores the records having 1990 and choose only records having 2000 or blank spaces*/
         if (regionIDNameString[10] == '2' || regionIDNameString[10] == ' ')
         {
            regionName = trim(regionIDNameString.substr(52, 71));
            idString.clear();
            /* Parse and add state*/
            switch (regionIDNameString[24])
            {
               case 'S':
                  idString = regionIDNameString.substr(5, 2);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mStateBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (rtcData.getRegionID(),rtcData));
                  break;
               case 'P':
                  idString = regionIDNameString.substr(5, 2) + regionIDNameString.substr(14, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mPlaceBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (rtcData.getRegionID(),rtcData));
                  break;
               case 'C':
                  idString = regionIDNameString.substr(5, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mCountyBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (rtcData.getRegionID(),rtcData));
                  break;
               case 'M':
                  idString =  regionIDNameString.substr(5, 2) + regionIDNameString.substr(14, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mSubCountyBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (rtcData.getRegionID(),rtcData));
                  break;
            }
         }
      }
      regionIdNameFileStream.close();
   }
   else
   {
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
   std::string boundsFileName;
   std::stringstream stringToint;
   std::string boundFileLineString;
   std::string regionID,minLongitude,minLatitude,maxLongitude,maxLatitude;
   std::ifstream readBoundsFileStream(mBndDataFile);
   region_bnd_map_t stateBndMap, countyBndMap, placeBndMap, subCountyBndMap;
   std::map<uint_least32_t,CRtcBndWrapper>::iterator iteratorBndRRC;
   if(readBoundsFileStream.is_open())
   {
      while(getline(readBoundsFileStream, boundFileLineString))
      {
         uint_least32_t regionIDInt;
         regionID = boundFileLineString.substr(0,7);
         minLongitude =boundFileLineString.substr(7,10);
         minLatitude = boundFileLineString.substr(17,9);
         maxLongitude = boundFileLineString.substr(26,10);
         maxLatitude = boundFileLineString.substr(36,9);
         stringToint.clear();
         stringToint.str(regionID);
         stringToint >> regionIDInt;
         iteratorBndRRC = mStateBndMap.find(regionIDInt);
         if(iteratorBndRRC != mStateBndMap.end() )
         {
            iteratorBndRRC->second.setMinLongitude(minLongitude);
            iteratorBndRRC->second.setMinLatitude(minLatitude);
            iteratorBndRRC->second.setMaxLatitude(maxLatitude);
            iteratorBndRRC->second.setMaxLongitude(maxLongitude);
            stateBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (regionIDInt, CRtcBndWrapper(regionID,iteratorBndRRC->second.getRegionName(), minLatitude, minLongitude, maxLatitude,maxLongitude)));
         }
 
         iteratorBndRRC = mCountyBndMap.find(regionIDInt);
         if(iteratorBndRRC != mCountyBndMap.end() )
         {
            iteratorBndRRC->second.setMinLongitude(minLongitude);
            iteratorBndRRC->second.setMinLatitude(minLatitude);
            iteratorBndRRC->second.setMaxLatitude(maxLatitude);
            iteratorBndRRC->second.setMaxLongitude(maxLongitude);
            countyBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (regionIDInt, CRtcBndWrapper(regionID,iteratorBndRRC->second.getRegionName(), minLatitude, minLongitude, maxLatitude,maxLongitude)));
         }
         iteratorBndRRC = mPlaceBndMap.find(regionIDInt);
         if(iteratorBndRRC != mPlaceBndMap.end() )
         {
            iteratorBndRRC->second.setMinLongitude(minLongitude);
            iteratorBndRRC->second.setMinLatitude(minLatitude);
            iteratorBndRRC->second.setMaxLatitude(maxLatitude);
            iteratorBndRRC->second.setMaxLongitude(maxLongitude);
            placeBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (regionIDInt, CRtcBndWrapper(regionIDInt,iteratorBndRRC->second.getRegionName(), minLatitude, minLongitude, maxLatitude,maxLongitude)));
         }
         iteratorBndRRC = mSubCountyBndMap.find(regionIDInt);
         if(iteratorBndRRC != mSubCountyBndMap.end() )
         {
            iteratorBndRRC->second.setMinLongitude(minLongitude);
            iteratorBndRRC->second.setMinLatitude(minLatitude);
            iteratorBndRRC->second.setMaxLatitude(maxLatitude);
            iteratorBndRRC->second.setMaxLongitude(maxLongitude);
            subCountyBndMap.insert(std::pair<uint_least32_t, CRtcBndWrapper> (regionIDInt, CRtcBndWrapper(regionID,iteratorBndRRC->second.getRegionName(), minLatitude, minLongitude, maxLatitude,maxLongitude)));
         }
         /* Clear all parsed data for loading next line. */
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
   if(stateBndMap.size() != 0)
   {
      mStateBndMap = stateBndMap;
   }
   else
   {
      mStateBndMap.clear();
   }
   if(placeBndMap.size() != 0)
   {
      mPlaceBndMap = placeBndMap;
   }
   else
   {
      mPlaceBndMap.clear();
   }
   
   if(countyBndMap.size() != 0)
   {
      mCountyBndMap = countyBndMap;
   }
   else
   {
      mCountyBndMap.clear();
   }
   
   if(subCountyBndMap.size() != 0)
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

int_least32_t CTigerShapeFileParser::serializeMapData( region_bnd_map_t regionMap,region_type_e regionType )
{
   std::string tableName;
   bool queryProcessingFailed = false;
   std::map<uint_least32_t, CRtcBndWrapper>::iterator itrRtcBnd; 
   tableName = getRegionTableName(regionType);
   for(itrRtcBnd = regionMap.begin(); itrRtcBnd != regionMap.end(); ++itrRtcBnd)
   {
      std::string queryString = "INSERT INTO "+tableName+" (ID,IName,Min_Latitude,Max_Latitude,Min_Longitude,Max_Longitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +",'" + itrRtcBnd->second.getRegionName() +"','"+
               itrRtcBnd->second.getMinLatitude()+"','"+itrRtcBnd->second.getMaxLatitude()+"','"+
               itrRtcBnd->second.getMinLongitude()+"','"+itrRtcBnd->second.getMaxLongitude()+ "') on conflict (id) do nothing;";
      if( mPsqlWrapper.processQuery(queryString) != PGRES_COMMAND_OK )
      {
         queryProcessingFailed = true;
         std::cerr << mPsqlWrapper.getQueryErrorMessage() << std::endl;
      }
   }
   if(queryProcessingFailed)
   {
      return -1;
   }
   else
   {
      return 0;
   }
}

int_least32_t CTigerShapeFileParser::saveParsedBndRTCData()
{
   bool queryProcessingFailed = false;
   std::map<uint_least32_t, CRtcBndWrapper>::iterator itrRtcBnd; 
   if(mPsqlWrapper.openConnection() != 0)
   {
      std::cout << "Cannot open connection.\n";
      exit(ENAVAIL);
   }
   if( serializeMapData(mStateBndMap,region_type_e::State) != 0)
   {
      queryProcessingFailed = true;
   }
   if( serializeMapData(mCountyBndMap,region_type_e::County) != 0)
   {
      queryProcessingFailed = true;
   }
   if( serializeMapData(mSubCountyBndMap,region_type_e::SubCounty) != 0)
   {
      queryProcessingFailed = true;
   }
   if( serializeMapData(mPlaceBndMap,region_type_e::Place)!= 0)
   {
      queryProcessingFailed = true;
   }

   if(mPsqlWrapper.closeConnection() != 0)
   {
      return -1;
   }
   if(queryProcessingFailed)
   {
      return -2;
   }
#ifdef DEBUG
   std::cout << "Shape Data Has been successfully Updated.\n";
#endif
   return 0;
}

std::string CTigerShapeFileParser::trim(std::string str)
{
   std::string returnString;
   for ( unsigned int i=0; i< str.size(); i++)
   {
      if((str[i] == ' ') && (str[i+1] == ' '))
      {
         break;
      }
      else
      {
         returnString = returnString  + str[i];
      }
    }
   return returnString;
}


std::string CTigerShapeFileParser::getRegionTableName(region_type_e regionType)
{
   std::string tableName = " ";
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

int_least32_t CTigerShapeFileParser::searchRegionByName ( std::string& regionName, region_bnd_map_t& regionMap, std::string tableName , bool searchByPattern)
{
   region_bnd_map_t bndRegionMap;
   if(mPsqlWrapper.openConnection() != 0)
   {
      std::cout << "Cannot open connection.\n";
      exit(ENAVAIL);
   }
   
   if(!searchByPattern)
   {
      std::string queryToProcess = std::string("SELECT * FROM ") + tableName +" WHERE iname = '" + regionName +"';";
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
      std::string queryToProcess  = std::string("SELECT * FROM ")+ tableName +(" WHERE iname LIKE '%' || $1 || '%';");
      const char* iname = regionName.c_str();
      int nParams = 1;
      const char *const paramValues[] = {iname};
      const int paramLengths[] = {sizeof(iname)};
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
      if((PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,0) == 0) && (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,1) == 0) &&
         (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,2) == 0) && (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,3) == 0) &&
         (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,4) == 0) && (PQgetisnull(mPsqlWrapper.GetQueryResult(),resultIndex,5) == 0))
      {
         std::string regionId = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,0));
         std::string regionName = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,1));
         std::string minLatitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,2));
         std::string maxLatitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,3));
         std::string minLongitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,4));
         std::string maxLongitude = std::string(PQgetvalue(mPsqlWrapper.GetQueryResult(),resultIndex,5));
         CRtcBndWrapper rtcBndWrapper = CRtcBndWrapper(regionId,regionName,minLatitude,minLongitude,maxLatitude,maxLongitude );
         bndRegionMap.insert(std::pair<uint_least32_t,CRtcBndWrapper>(rtcBndWrapper.getRegionID(), rtcBndWrapper));
      }
   }
   if(bndRegionMap.size() != 0)
   {
      regionMap = bndRegionMap;
      return 0;
   }
   return -1;
}


int_least32_t CTigerShapeFileParser::searchRegionByName( std::string& regionName, region_bnd_map_t& regionMap, bool searchByPattern )
{
   int_least32_t regionTypeCount;
   region_bnd_map_t searchResults;
   std::string tableName;
   for (regionTypeCount = 0; regionTypeCount < region_type_e::invalid; regionTypeCount++)
   {
      region_bnd_map_t searchResultsByType;
      tableName = getRegionTableName((region_type_e)regionTypeCount);
      
      if( searchRegionByName(regionName, searchResultsByType, tableName, searchByPattern) == 0)
      {
         if(searchResultsByType.size() != 0)
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
   if (searchResults.size() == 0)
   {
      return -1;
   }
   regionMap = searchResults;
   return 0;
}
