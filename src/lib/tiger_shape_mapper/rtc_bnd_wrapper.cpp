#include <rtc_bnd_wrapper.h>

#include <sstream>
#include <cmath>

CRtcBndWrapper::CRtcBndWrapper(std::string regionID, std::string regionName,std::string minLatitude, std::string minLongitude, std::string maxLatitude, std::string maxLongitude)
{
   mRegionID = 0;
   std::stringstream stringToint;
   stringToint.str(regionID);
   stringToint >> mRegionID;
   mRegionName = regionName;
   mMinLatitude = minLatitude;
   mMinLongitude = minLongitude;
   mMaxLatitude = maxLatitude;
   mMaxLongitude = maxLongitude;
}

CRtcBndWrapper::CRtcBndWrapper(uint_least32_t regionID, std::string regionName,std::string minLatitude, std::string minLongitude, std::string maxLatitude, std::string maxLongitude)
{
   mRegionID = regionID;
   mRegionName = regionName;
   mMinLatitude = minLatitude;
   mMinLongitude = minLongitude;
   mMaxLatitude = maxLatitude;
   mMaxLongitude = maxLongitude;
}


CRtcBndWrapper::CRtcBndWrapper(std::string regionID, std::string regionName)
{
   mRegionID = 0;
   std::stringstream stringToint;
   stringToint.str(regionID);
   stringToint >> mRegionID;
   mRegionName = regionName;
   mMinLatitude = "";
   mMinLongitude = "";
   mMaxLatitude = "";
   mMaxLongitude = "";
}


std::string CRtcBndWrapper::to_string() const
{
   std::string templateString = std::string("Region ID: ") + std::to_string(mRegionID) + std::string("\tRegion Name: ") + mRegionName + std::string("\t Bounds: ");
   templateString = templateString + std::string ("Min Latitude: ") + GetDecimalLatitude(mMinLatitude) + std::string (",Max Latitude: ") + GetDecimalLatitude(mMaxLatitude) + 
   std::string ("; Min Longitude: ") + GetDecimalLongitude(mMinLongitude) + std::string (",Max Longitude: ") + GetDecimalLongitude(mMaxLongitude) + std::string("\n");
   return templateString;
}

uint_least32_t CRtcBndWrapper::getRegionID()
{
   return mRegionID;
}
std::string CRtcBndWrapper::getRegionName() 
{
   return mRegionName;
}
std::string CRtcBndWrapper::getMinLongitude() const
{
   return mMinLongitude;
}
std::string CRtcBndWrapper::getMinLatitude() const
{
   return mMinLatitude;
}
std::string CRtcBndWrapper::getMaxLatitude() const
{
   return mMaxLatitude;
}
std::string CRtcBndWrapper::getMaxLongitude() const
{
   return mMaxLongitude;
}

void CRtcBndWrapper::setMinLongitude(std::string minLongitude)
{
   mMinLongitude = minLongitude;
}
void CRtcBndWrapper::setMinLatitude(std::string minLatitude)
{
   mMinLatitude = minLatitude;
}
void CRtcBndWrapper::setMaxLatitude(std::string maxLatitude)
{
   mMaxLatitude = maxLatitude;
}
void CRtcBndWrapper::setMaxLongitude(std::string maxLongitude)
{
   mMaxLongitude = maxLongitude;
}

std::string CRtcBndWrapper::GetDecimalLatitude(std::string degreeDecimal) const 
{
   std::string degMinSec;
      
   if(degreeDecimal.length() == 0)
   {
      return degMinSec;
   }
   std::stringstream degreeSring;
   /*Convert string into appropriate integer and float values*/
   unsigned int degrees; 
   degreeSring.str(degreeDecimal.substr(1,2));
   degreeSring >> degrees;
   /* extract and calculate minutes */
   float  minutes = (stof(degreeDecimal.substr(3,degreeDecimal.length()))*60/1000000);
   double minutes_double;
   float secondFractions= modf(minutes, &minutes_double);
   float seconds = secondFractions * 60;
   degMinSec = std::to_string(degrees) + "° " + std::to_string(minutes_double) + "\' " + std::to_string(seconds) + "\"";
   if(degreeDecimal.at(0) == '-')
   {
      degMinSec+= " South";
   }
   else if(degreeDecimal.at(0) == '+')
   {
      degMinSec += " North";
   }

   return degMinSec;

}

std::string CRtcBndWrapper::GetDecimalLongitude(std::string degreeDecimal) const 
{
   std::string degMinSec;
   
   if(degreeDecimal.length() == 0)
   {
      return degMinSec;
   }
   std::stringstream degreeSring;
   /*Convert string into appropriate integer and float values*/
   unsigned int degrees; 
   degreeSring.str(degreeDecimal.substr(1,2));
   degreeSring >> degrees;
   /* extract and calculate minutes */
   float  minutes = (stof(degreeDecimal.substr(4,degreeDecimal.length()))*60/1000000);
   double minutes_double;
   float secondFractions= modf(minutes, &minutes_double);
   float seconds = secondFractions * 60;
   degMinSec = std::to_string(degrees) + "° " + std::to_string(minutes_double) + "\' " + std::to_string(seconds) + "\"";
   
   /*Set east or west direct based on sign.*/
   if(degreeDecimal.at(0) == '-')
   {
      degMinSec += " West";
   }
   else if(degreeDecimal.at(0) == '+')
   {
     degMinSec += " East";
   }

   return degMinSec;
}
