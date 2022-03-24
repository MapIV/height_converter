#ifndef M4_HEIGHT_CONVERTER_HPP
#define M4_HEIGHT_CONVERTER_HPP

#include <string>

#include <GeographicLib/Geoid.hpp>

#include "height_converter/gsigeo.hpp"

namespace height_converter
{
enum class GeoidType
{
  EGM2008 = 0,
  GSIGEO2011 = 1,
};

enum ConvertType
{
  ELLIPS2ORTHO = -1,
  ORTHO2ELLIPS = 1,
};

class HeightConverter
{
public:
  HeightConverter();
  ~HeightConverter();
  double convertHeight(const double& lat, const double& lon, const double& h, const ConvertType& type);
  void setGeoidType(const GeoidType& geoid_type);
  double getGeoid(const double& lat, const double& lon);
  void setGSIGEOGeoidFile(const std::string& geoid_file);
  void setGSIGEOGeoidFile();

private:
  // Geoid type
  GeoidType geoid_type_ = GeoidType::EGM2008;
  // Flag
  bool is_gsigeo_loaded_ = false;

  // Geoid maps
  GeographicLib::Geoid egm2008_{"egm2008-1"};
  GSIGEO2011 gsigeo2011_;

  double getGeoidEGM2008(const double& lat, const double& lon);
  double getGeoidGSIGEO2011(const double& lat, const double& lon);
};
}   // namespace height_converter

#endif
