#include <tiger_shape_file_parser.h>
#include <sstream>
#include <fstream>
#include <iostream>

CTigerShapeFileParser::CTigerShapeFileParser(std::string& rtcDataFile, std::string& bndDataFile)
{
   mPsqlWarapper = CPSQLWrapper("localhost", "amouroug", "FullMetalAlchemist#8");
   mRtcDataFile = rtcDataFile;
   mBndDataFile = bndDataFile;
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
   
   return 0;
   
}

int_least32_t CTigerShapeFileParser::parseBNDData()
{
   std::string boundsFileName;
   std::stringstream stringToint;
   std::string boundFileLineString;
   std::string regionID,minLongitude,minLatitude,maxLongitude,maxLatitude;
   uint_least32_t regionIDInt;
   std::ifstream readBoundsFileStream(mBndDataFile);
   region_bnd_map_t stateBndMap, countyBndMap, placeBndMap, subCountyBndMap;
   std::map<uint_least32_t,CRtcBndWrapper>::iterator iteratorBndRRC;
   if(readBoundsFileStream.is_open())
   {

      while(getline(readBoundsFileStream, boundFileLineString))
      {
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
   return 0;
}

int_least32_t CTigerShapeFileParser::parseBndRTCFiles()
{
   if(parseRTCData() == 0)
   {
      std::cout << "Parsing bounds data.\n";
      return parseBNDData();
   }
   else
   {
      return -1;
   }

}


int_least32_t CTigerShapeFileParser::saveParsedBndRTCData()
{
   bool queryProcessingFailed = false;
   std::map<uint_least32_t, CRtcBndWrapper>::iterator itrRtcBnd; 

   if(mPsqlWarapper.openConnection() != 0)
   {
      std::cout << "Cannot open connection.\n";
      return -1;
   }
   for(itrRtcBnd = mStateBndMap.begin(); itrRtcBnd != mStateBndMap.end(); ++itrRtcBnd)
   {
      std::string queryString = "INSERT INTO "+ mPsqlWarapper.getDbName()+".STATE (ID,IName,Min_Latitude,Max_Latitude,Min_Longitude,Max_Longitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +",'" + itrRtcBnd->second.getRegionName() +"','"+
               itrRtcBnd->second.getMinLatitude()+"','"+itrRtcBnd->second.getMaxLatitude()+"','"+
               itrRtcBnd->second.getMinLongitude()+"','"+itrRtcBnd->second.getMaxLongitude()+ "') on conflict (id) do nothing;";
      if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK )
      {
         queryProcessingFailed = true;
         std::cerr << "Failed to insert State:" << itrRtcBnd->second.to_string();
         std::cerr << mPsqlWarapper.getQueryErrorMessage() << std::endl;
      }
      else
      {
         std::cout << "Inserted State->" << itrRtcBnd->second.to_string();
      }
      
   }

   for(itrRtcBnd = mCountyBndMap.begin(); itrRtcBnd != mCountyBndMap.end(); ++itrRtcBnd)
   {
      std::string queryString = "INSERT INTO "+ mPsqlWarapper.getDbName()+".COUNTY (ID,IName,Min_Latitude,Max_Latitude,Min_Longitude,Max_Longitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +",'" + itrRtcBnd->second.getRegionName() +"','"+
               itrRtcBnd->second.getMinLatitude()+"','"+itrRtcBnd->second.getMaxLatitude()+"','"+
               itrRtcBnd->second.getMinLongitude()+"','"+itrRtcBnd->second.getMaxLongitude()+ "') on conflict (id) do nothing;";
      if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK )
      {
         queryProcessingFailed = true;
         std::cerr << "Failed to insert County:" << itrRtcBnd->second.to_string();
         std::cerr << mPsqlWarapper.getQueryErrorMessage() << std::endl;
      }
      else
      {
         std::cout << "Inserted County ->" << itrRtcBnd->second.to_string();
      }
   }
   for(itrRtcBnd = mSubCountyBndMap.begin(); itrRtcBnd != mSubCountyBndMap.end(); ++itrRtcBnd)
   {
      std::string queryString = "INSERT INTO "+ mPsqlWarapper.getDbName()+".SUBCOUNTY (ID,IName,Min_Latitude,Max_Latitude,Min_Longitude,Max_Longitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +",'" + itrRtcBnd->second.getRegionName() +"','"+
               itrRtcBnd->second.getMinLatitude()+"','"+itrRtcBnd->second.getMaxLatitude()+"','"+
               itrRtcBnd->second.getMinLongitude()+"','"+itrRtcBnd->second.getMaxLongitude()+ "') on conflict (id) do nothing;";
      if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK )
      {
         queryProcessingFailed = true;
         std::cerr << "Failed to insert sub County:" << itrRtcBnd->second.to_string();
         std::cerr << mPsqlWarapper.getQueryErrorMessage() << std::endl;
      }
      else
      {
         std::cout << "Inserted Sub County ->" << itrRtcBnd->second.to_string();
      }
   }

   for(itrRtcBnd = mPlaceBndMap.begin(); itrRtcBnd != mPlaceBndMap.end(); ++itrRtcBnd)
   {
      std::string  queryString = "INSERT INTO "+mPsqlWarapper.getDbName()+".PLACE (ID,IName,Min_Latitude,Max_Latitude,Min_Longitude,Max_Longitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +",'" + itrRtcBnd->second.getRegionName() +"','"+
               itrRtcBnd->second.getMinLatitude()+"','"+itrRtcBnd->second.getMaxLatitude()+"','"+
               itrRtcBnd->second.getMinLongitude()+"','"+itrRtcBnd->second.getMaxLongitude()+ "') on conflict (id) do nothing;";
      if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK )
      {
         queryProcessingFailed = true;
         std::cerr << "Failed to insert sub County:" << itrRtcBnd->second.to_string();
         std::cerr << mPsqlWarapper.getQueryErrorMessage() << std::endl;
      }
      else
      {
         std::cout << "Inserted Place ->" << itrRtcBnd->second.to_string();
      }
   }
   
   if(mPsqlWarapper.closeConnection() != 0)
   {
      return -1;
   }
   
   if(queryProcessingFailed)
   {
      return -2;
   }
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
