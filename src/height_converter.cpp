#include "height_converter/height_converter.hpp"

#include <iostream>

namespace height_converter
{
HeightConverter::HeightConverter()
{
}

HeightConverter::~HeightConverter()
{
}

double HeightConverter::convertHeight(const double& lat, const double& lon, const double& h, const ConvertType& type)
{
  double geoid_height = getGeoid(lat, lon);
  
  return h + geoid_height * type;
}

void HeightConverter::setGeoidType(const GeoidType& geoid_type)
{
  geoid_type_ = geoid_type;
}

double HeightConverter::getGeoid(const double& lat, const double& lon)
{
  switch (geoid_type_)
  {
    case GeoidType::EGM2008:
      return getGeoidEGM2008(lat, lon);
    case GeoidType::GSIGEO2011:
      return getGeoidGSIGEO2011(lat, lon);
  }
}

void HeightConverter::setGSIGEOGeoidFile(const std::string& geoid_file)
{
  gsigeo2011_.loadGeoidMap(geoid_file);
}

void HeightConverter::setGSIGEOGeoidFile()
{
  gsigeo2011_.loadGeoidMap("/usr/share/GSIGEO/gsigeo2011_ver2_1.asc");
}

double HeightConverter::getGeoidEGM2008(const double& lat, const double& lon)
{
  try
  {
    return egm2008_(lat, lon);
  }
  catch (const GeographicLib::GeographicErr& e)
  {
    std::cerr << "GeographicLib Error: " << e.what() << std::endl;
    exit(1);
  }
}

double HeightConverter::getGeoidGSIGEO2011(const double& lat, const double& lon)
{
  return gsigeo2011_.getGeoid(lat, lon);  
}
}   // namespace height_converter
