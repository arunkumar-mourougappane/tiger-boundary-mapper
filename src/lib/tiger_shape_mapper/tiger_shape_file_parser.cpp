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
                  mStateBndMap.emplace(rtcData.getRegionID(),rtcData);
                  break;
               case 'P':
                  idString = regionIDNameString.substr(5, 2) + regionIDNameString.substr(14, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mPlaceBndMap.emplace (rtcData.getRegionID(),rtcData);
                  break;
               case 'C':
                  idString = regionIDNameString.substr(5, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mCountyBndMap.emplace (rtcData.getRegionID(),rtcData);
                  break;
               case 'M':
                  idString =  regionIDNameString.substr(5, 2) + regionIDNameString.substr(14, 5);
                  rtcData = CRtcBndWrapper(idString, regionName);
                  mSubCountyBndMap.emplace (rtcData.getRegionID(),rtcData);
                  break;
            }
         }
      }
      regionIdNameFileStream.close();
   }
   else
   {
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

         stringToint.str(regionID);
         stringToint >> regionIDInt;
      }
      iteratorBndRRC = mStateBndMap.find(regionIDInt);
      if(iteratorBndRRC != mStateBndMap.end() )
      {
         iteratorBndRRC->second.setMinLongitude(minLongitude);
         iteratorBndRRC->second.setMinLatitude(minLatitude);
         iteratorBndRRC->second.setMaxLatitude(maxLatitude);
         iteratorBndRRC->second.setMaxLongitude(maxLongitude);
      }
      iteratorBndRRC = mCountyBndMap.find(regionIDInt);
      {
         iteratorBndRRC->second.setMinLongitude(minLongitude);
         iteratorBndRRC->second.setMinLatitude(minLatitude);
         iteratorBndRRC->second.setMaxLatitude(maxLatitude);
         iteratorBndRRC->second.setMaxLongitude(maxLongitude);
      }
      iteratorBndRRC = mCountyBndMap.find(regionIDInt);
      {
         iteratorBndRRC->second.setMinLongitude(minLongitude);
         iteratorBndRRC->second.setMinLatitude(minLatitude);
         iteratorBndRRC->second.setMaxLatitude(maxLatitude);
         iteratorBndRRC->second.setMaxLongitude(maxLongitude);
      }
      iteratorBndRRC = mPlaceBndMap.find(regionIDInt);
      {
         iteratorBndRRC->second.setMinLongitude(minLongitude);
         iteratorBndRRC->second.setMinLatitude(minLatitude);
         iteratorBndRRC->second.setMaxLatitude(maxLatitude);
         iteratorBndRRC->second.setMaxLongitude(maxLongitude);
      }
      iteratorBndRRC = mSubCountyBndMap.find(regionIDInt);
      {
         iteratorBndRRC->second.setMinLongitude(minLongitude);
         iteratorBndRRC->second.setMinLatitude(minLatitude);
         iteratorBndRRC->second.setMaxLatitude(maxLatitude);
         iteratorBndRRC->second.setMaxLongitude(maxLongitude);
      }
      /* Clear all parsed data for loading next line. */
      minLatitude.clear();
      minLongitude.clear();
      maxLatitude.clear();
      maxLongitude.clear();
      regionID.clear();
      readBoundsFileStream.close();
      std::cout << iteratorBndRRC->second.to_string();
   }
   else
   {
      return -1;
   }
   return 0;
}

int_least32_t CTigerShapeFileParser::parseBndRTCFiles()
{
   if(parseRTCData() == 0)
   {
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
      return -1;
   }
   for(itrRtcBnd = mStateBndMap.begin(); itrRtcBnd != mStateBndMap.end(); ++itrRtcBnd)
   {
      std::string queryString = "INSERT INTO "+ mPsqlWarapper.getDbName()+".STATE (id,iname,minlatitude,maxlatitude,minlongitude,maxlongitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +"," + itrRtcBnd->second.getRegionName() +","+
               itrRtcBnd->second.getMinLatitude()+","+itrRtcBnd->second.getMaxLatitude()+","+
               itrRtcBnd->second.getMinLongitude()+","+itrRtcBnd->second.getMaxLongitude()+ ") on conflict (id) do nothing;";
      if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK)
      {
         queryProcessingFailed = true;
      }
      else
      {
         std::cerr << "Failed to insert :" << itrRtcBnd->second.to_string();
      }
      
   }

   for(itrRtcBnd = mCountyBndMap.begin(); itrRtcBnd != mCountyBndMap.end(); ++itrRtcBnd)
   {
      std::string queryString = "INSERT INTO "+ mPsqlWarapper.getDbName()+".COUNTY (id,iname,minlatitude,maxlatitude,minlongitude,maxlongitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +"," + itrRtcBnd->second.getRegionName() +","+
               itrRtcBnd->second.getMinLatitude()+","+itrRtcBnd->second.getMaxLatitude()+","+
               itrRtcBnd->second.getMinLongitude()+","+itrRtcBnd->second.getMaxLongitude()+ ") on conflict (id) do nothing;";
     if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK)
      {
         queryProcessingFailed = true;
      }
      else
      {
         std::cerr << "Failed to insert :" << itrRtcBnd->second.to_string();
      }
   }
   for(itrRtcBnd = mSubCountyBndMap.begin(); itrRtcBnd != mSubCountyBndMap.end(); ++itrRtcBnd)
   {
      std::string queryString = "INSERT INTO "+ mPsqlWarapper.getDbName()+".SUBCOUNTY (id,iname,minlatitude,maxlatitude,minlongitude,maxlongitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +"," + itrRtcBnd->second.getRegionName() +","+
               itrRtcBnd->second.getMinLatitude()+","+itrRtcBnd->second.getMaxLatitude()+","+
               itrRtcBnd->second.getMinLongitude()+","+itrRtcBnd->second.getMaxLongitude()+ ") on conflict (id) do nothing;";
      if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK)
      {
         queryProcessingFailed = true;
      }
      else
      {
         std::cerr << "Failed to insert :" << itrRtcBnd->second.to_string();
      }
   }

   for(itrRtcBnd = mSubCountyBndMap.begin(); itrRtcBnd != mSubCountyBndMap.end(); ++itrRtcBnd)
   {
      std::string  queryString = "INSERT INTO "+mPsqlWarapper.getDbName()+".PLACE (id,iname,minlatitude,maxlatitude,minlongitude,maxlongitude) values (" +
               std::to_string(itrRtcBnd->second.getRegionID()) +"," + itrRtcBnd->second.getRegionName() +","+
               itrRtcBnd->second.getMinLatitude()+","+itrRtcBnd->second.getMaxLatitude()+","+
               itrRtcBnd->second.getMinLongitude()+","+itrRtcBnd->second.getMaxLongitude()+ ") on conflict (id) do nothing;";
      if( mPsqlWarapper.processQuery(queryString) != PGRES_COMMAND_OK)
      {
         queryProcessingFailed = true;
      }
      else
      {
         std::cerr << "Failed to insert :" << itrRtcBnd->second.to_string();
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
