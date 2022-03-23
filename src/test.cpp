#include "height_converter/height_converter.hpp"

#include <iostream>

int main(int argc, char** argv)
{
  height_converter::HeightConverter hc;
  hc.setGeoidType(height_converter::GeoidType::GSIGEO2011);
  hc.setGSIGEOGeoidFile(argv[1]);
  std::cout << hc.getGeoid(35, 135) << std::endl;
  std::cout << hc.getGeoid(35.5, 135.5) << std::endl;

  return 0;
}
