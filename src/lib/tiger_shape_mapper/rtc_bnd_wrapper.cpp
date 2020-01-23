/**
 * @file rtc_bnd_wrapper.cpp
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief Implementaions of the APIs declared for CRtcBndWrapper. 
 * @version 1.0
 * @date 01-23-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <rtc_bnd_wrapper.h>

#include <sstream>
#include <cmath>

/**
 * @brief Construct a new CRtcBndWrapper object with Region and bounds information.
 * 
 * @param regionID     ID of the Region as integer
 * @param regionName   Name of the region to be converted to object.
 * @param minLatitude  Starting of the latitude bounds of the region.
 * @param minLongitude Starting of the Longitude bounds of the region.
 * @param maxLatitude  Ending of the latitude bounds of the region.
 * @param maxLongitude Ending of the Longitude bounds of the region.
 */
CRtcBndWrapper::CRtcBndWrapper(std::string regionID, std::string regionName,std::string minLatitude, std::string minLongitude, std::string maxLatitude, std::string maxLongitude)
{
   mRegionID = 0;
   // string stream to convert region ID string argument to uin_least32_t 
   std::stringstream stringToint;
   stringToint.str(regionID);
   stringToint >> mRegionID;
   mRegionName = regionName;
   mMinLatitude = minLatitude;
   mMinLongitude = minLongitude;
   mMaxLatitude = maxLatitude;
   mMaxLongitude = maxLongitude;
}

/**
 * @brief Construct a new CRtcBndWrapper object with Region and bounds information.
 * 
 * @param regionID     ID of the Region as string.
 * @param regionName   Name of the region to be converted to object.
 * @param minLatitude  Starting of the latitude bounds of the region.
 * @param minLongitude Starting of the Longitude bounds of the region.
 * @param maxLatitude  Ending of the latitude bounds of the region.
 * @param maxLongitude Ending of the Longitude bounds of the region.
 */
CRtcBndWrapper::CRtcBndWrapper(uint_least32_t regionID, std::string regionName,std::string minLatitude, std::string minLongitude, std::string maxLatitude, std::string maxLongitude)
{
   mRegionID = regionID;
   mRegionName = regionName;
   mMinLatitude = minLatitude;
   mMinLongitude = minLongitude;
   mMaxLatitude = maxLatitude;
   mMaxLongitude = maxLongitude;
}

/**
 * @brief Construct a new CRtcBndWrapper objectt with Region information.
 * 
 * @param regionID    ID of the Region as string.
 * @param regionName  Name of the region to be converted to object.
 */
CRtcBndWrapper::CRtcBndWrapper(std::string regionID, std::string regionName)
{
   // Assign region ID a default value.
   mRegionID = 0;
   // string stream to convert region ID string argument to uin_least32_t 
   std::stringstream stringToint;
   stringToint.str(regionID);
   stringToint >> mRegionID;
   mRegionName = regionName;
   // Empty bounds information are initialized if no information about them are provided.
   mMinLatitude = "";
   mMinLongitude = "";
   mMaxLatitude = "";
   mMaxLongitude = "";
}

/**
 * @brief Used serialized the RTC and BND information from instance into a formatted string.
 * 
 * @return std::string Returns a formatted string containing RTC and BND infomation.
 */
std::string CRtcBndWrapper::to_string() const
{

   // Formatted string with RTC and BND file information meshed together.
   /* Sample format:
   * Region ID: 17   Region Name: Illinois    Bounds: Min Latitude: 36° 58' 13.01" N,Max Latitude: 42° 30' 30" N; Min Longitude: 9° 30' 47.19" W, Max Longitude: 8° 1' 11.84" W
   */
   std::string templateString = std::string("Region ID: ") + std::to_string(mRegionID) + std::string("\t\tRegion Name: ") + mRegionName + std::string("\t Bounds: ");
   
   templateString = templateString + std::string ("Min Latitude: ") + GetDecimalLatitude(mMinLatitude) + std::string (",Max Latitude: ") + GetDecimalLatitude(mMaxLatitude) + 
   std::string ("; Min Longitude: ") + GetDecimalLongitude(mMinLongitude) + std::string (", Max Longitude: ") + GetDecimalLongitude(mMaxLongitude) + std::string("\n");
   return templateString;
}

/**
 * @brief Getter for region ID.
 * 
 * @return uint_least32_t Returns the region ID saved in the instance.
 */
uint_least32_t CRtcBndWrapper::getRegionID()
{
   return mRegionID;
}

/**
 * @brief Getter for the Region Name from instance
 * 
 * @return std::string Returns the string for Region Name saved in the instance.
 */
std::string CRtcBndWrapper::getRegionName() 
{
   return mRegionName;
}

/**
 * @brief Getter for the  Longitude start for the saved instance of region.
 * 
 * @return std::string Returns the immuatable string for Start Longitude for the saved instance of region.
 */
std::string CRtcBndWrapper::getMinLongitude() const
{
   return mMinLongitude;
}

/**
 * @brief Getter for the  Latitude start for the saved instance of region.
 * 
 * @return std::string Returns the immuatable string for Start Latitude for the saved instance of region.
 */
std::string CRtcBndWrapper::getMinLatitude() const
{
   return mMinLatitude;
}

/**
 * @brief Getter for the  Latitude end for the saved instance of region.
 * 
 * @return std::string Returns the immuatable string for end Latitude for the saved instance of region.
 */
std::string CRtcBndWrapper::getMaxLatitude() const
{
   return mMaxLatitude;
}

/**
 * @brief Getter for the  Longitude end for the saved instance of region.
 * 
 * @return std::string Returns the immuatable string for Ending Longitude for the saved instance of region.
 */
std::string CRtcBndWrapper::getMaxLongitude() const
{
   return mMaxLongitude;
}


/**
 * @brief Setter for the  Longitude end for the saved instance of region.
 * 
 * @param minLongitude Starting Longitude numerals in std::string.
 */
void CRtcBndWrapper::setMinLongitude(std::string minLongitude)
{
   mMinLongitude = minLongitude;
}

/**
 * @brief Setter for the  Latitude start for the saved instance of region.
 * 
 * @param minLatitude Starting Latitude numerals in std::string.
 */
void CRtcBndWrapper::setMinLatitude(std::string minLatitude)
{
   mMinLatitude = minLatitude;
}

/**
 * @brief Setter for the  Latitude end for the saved instance of region.
 * 
 * @param maxLatitude Ending Latitude numerals in std::string.
 */
void CRtcBndWrapper::setMaxLatitude(std::string maxLatitude)
{
   mMaxLatitude = maxLatitude;
}

/**
 * @brief Setter for the  Longitude end for the saved instance of region.
 * 
 * @param maxLongitude Ending Longitude numerals in std::string.
 */
void CRtcBndWrapper::setMaxLongitude(std::string maxLongitude)
{
   mMaxLongitude = maxLongitude;
}

/**
 * @brief Convert the numberal value of degress to degree, minute,seconds and direction.
 * 
 * @param degreeDecimal decimal value of latitude co-ordinates.
 *
 * @return std::string  Format string of latitude  with degrees, minutes & seconds denomination.
 */
std::string CRtcBndWrapper::GetDecimalLatitude(std::string degreeDecimal) const 
{
   std::string degMinSec;
      
   if(degreeDecimal.length() == 0)
   {
      return degMinSec;
   }
   // Need stringstring to extact precision values of the degrees, minutes and seconds.
   std::stringstream degreeString;
   std::stringstream minutesString, secondString;
   /*Convert string into appropriate integer and float values*/
   unsigned int degrees; 
   degreeString.str(degreeDecimal.substr(1,2));
   degreeString >> degrees;
   /* extract and calculate minutes */
   float  minutes = (stof(degreeDecimal.substr(3,degreeDecimal.length()))*60/1000000);
   double minutes_double;
   // Fix the precission for minutes to 2 digits after decimal.
   float secondFractions= modf(minutes, &minutes_double);
   minutesString << minutes_double;
   minutesString.precision(2);
   // Fix the precission for seconds to 2 digits after decimal.
   float seconds = ((int)(secondFractions * 60*100.00))/100.0;
   secondString << seconds;
   secondString.precision(2);
   degMinSec = std::to_string(degrees) + "° " + minutesString.str() + "\' " + secondString.str() + "\"";
   // Assign direciton base on the sign provuded in argument string.
   if(degreeDecimal.at(0) == '-')
   {
      degMinSec+= " S";
   }
   else if(degreeDecimal.at(0) == '+')
   {
      degMinSec += " N";
   }
   return degMinSec;
}

/**
 * @brief Convert the numberal value of degress to degree, minute,seconds and direction.
 * 
 * @param degreeDecimal decimal value of Longitude co-ordinates.
 *
 * @return std::string  Format string of Longitude  with degrees, minutes & seconds denomination.
 */
std::string CRtcBndWrapper::GetDecimalLongitude(std::string degreeDecimal) const 
{
   std::string degMinSec;
   if(degreeDecimal.length() == 0)
   {
      return degMinSec;
   }
   // Need stringstring to extact precision values of the degrees, minutes and seconds.
   std::stringstream degreeSring;
   std::stringstream minutesString, secondString;
   // Convert string into appropriate integer and float values
   unsigned int degrees; 
   degreeSring.str(degreeDecimal.substr(1,2));
   degreeSring >> degrees;
   // extract and calculate minutes 
   float  minutes = (stof(degreeDecimal.substr(4,degreeDecimal.length()))*60/1000000);
   double minutes_double;
   // Fix the precission for minutes to 2 digits after decimal.
   float secondFractions= modf(minutes, &minutes_double);
   minutesString << minutes_double;
   minutesString.precision(2);
   // Fix the precission for seconds to 2 digits after decimal.
   float seconds = ((int)(secondFractions * 60*100.00))/100.0;
   secondString << seconds;
   secondString.precision(2);
   degMinSec = std::to_string(degrees) + "° " + minutesString.str() + "\' " + secondString.str() + "\"";
   // Assign direciton base on the sign provuded in argument string.
   if(degreeDecimal.at(0) == '-')
   {
      degMinSec += " W";
   }
   else if(degreeDecimal.at(0) == '+')
   {
     degMinSec += " E";
   }
   return degMinSec;
}
