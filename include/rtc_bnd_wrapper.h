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
#include <string_view>
#include <cstdint>

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
      std::string mRegionName;
      std::string mMinLatitude;
      std::string mMinLongitude;
      std::string mMaxLatitude;
      std::string mMaxLongitude;

   public:
      CRtcBndWrapper(std::string_view regionID, std::string_view regionName, std::string_view minLatitude, std::string_view minLongitude, std::string_view maxLatitude, std::string_view maxLongitude);
      CRtcBndWrapper(uint_least32_t regionID, std::string_view regionName, std::string_view minLatitude, std::string_view minLongitude, std::string_view maxLatitude, std::string_view maxLongitude);
      CRtcBndWrapper(std::string_view regionID, std::string_view regionName);
      CRtcBndWrapper() = default;
      ~CRtcBndWrapper() = default;

      [[nodiscard]] std::string to_string() const;
      [[nodiscard]] uint_least32_t getRegionID() const;
      [[nodiscard]] std::string_view getRegionName() const;
      [[nodiscard]] std::string_view getMinLatitude() const;
      [[nodiscard]] std::string_view getMinLongitude() const;
      [[nodiscard]] std::string_view getMaxLatitude() const;
      [[nodiscard]] std::string_view getMaxLongitude() const;
      
      void setMinLatitude(std::string_view minLatitude);
      void setMinLongitude(std::string_view minLongitude);
      void setMaxLatitude(std::string_view maxLatitude);
      void setMaxLongitude(std::string_view maxLongitude);
      
      [[nodiscard]] std::string GetDecimalLatitude(std::string_view degreeDecimal) const;
      [[nodiscard]] std::string GetDecimalLongitude(std::string_view degreeDecimal) const;
};
#endif