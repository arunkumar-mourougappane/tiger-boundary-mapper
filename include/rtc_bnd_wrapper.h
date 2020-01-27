/**
 * @file rtc_bnd_wrapper.h
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief A wrapper API /bean that can be used to instantize, the RTC and
         BND file information to an object instance.
 * @version 1.0
 * @date 01-23-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef RTC_BND_WRAPPER_H
#define RTC_BND_WRAPPER_H
#include <string>

/**
 * @brief A class to save RTC and BND information based on
 *        the region ID. The class instance can take in the 
 *        bounds of the regions and create instance. Also,
 *        the data from instance can be serialized into string.
 */
class CRtcBndWrapper
{
   private:
      uint_least32_t mRegionID = 0;
      std::string mRegionName = "";
      std::string  mMinLatitude = "";
      std::string  mMinLongitude = "";
      std::string  mMaxLatitude = "";
      std::string  mMaxLongitude = "";

   public:
      CRtcBndWrapper(std::string  regionID, std::string  regionName,std::string  minLatitude, std::string  minLongitude, std::string  maxLatitude, std::string  maxLongitude);
      CRtcBndWrapper(uint_least32_t regionID, std::string  regionName,std::string  minLatitude, std::string  minLongitude, std::string  maxLatitude, std::string  maxLongitude);
      CRtcBndWrapper(std::string  regionID, std::string  regionName);
      CRtcBndWrapper(){};
      ~CRtcBndWrapper(){};
      std::string to_string() const;
      uint_least32_t getRegionID();
      std::string  getRegionName();
      std::string  getMinLatitude() const;
      std::string  getMinLongitude() const;
      std::string  getMaxLatitude() const;
      std::string  getMaxLongitude() const;
      void setMinLatitude(std::string  minLatitude);
      void setMinLongitude(std::string  minLongitude);
      void setMaxLatitude(std::string  maxLatitude);
      void setMaxLongitude(std::string  maxLongitude);
      std::string  GetDecimalLatitude(std::string degreeDecimal) const;
      std::string  GetDecimalLongitude(std::string degreeDecimal) const;
};
#endif