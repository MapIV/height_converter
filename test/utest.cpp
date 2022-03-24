#include "height_converter/height_converter.hpp"

#include <iostream>
#include <iomanip>

void test(const double& result, const double& answer)
{
  int i_result = std::round(result * 10000);
  int i_answer = std::round(answer * 10000);
  if (i_result == i_answer)
  {
    std::cout << "\033[32;1mTEST SUCCESS: " << result << " == " << answer << "\033[m" << std::endl;
  }
  else
  {
    std::cout << "\033[31;1mTEST FAILED : " << result << " != " << answer << "\033[m" << std::endl;
  }
}

int main(int argc, char** argv)
{
  height_converter::HeightConverter hc;

  // GSIGEO Test
  hc.setGeoidType(height_converter::GeoidType::GSIGEO2011);
  hc.setGSIGEOGeoidFile();

  std::cout << "Testing (" << std::setw(6) << 35 << ", " << std::setw(6) << 135 << ") ... ";
  test(hc.getGeoid(35, 135), 37.0557);

  std::cout << "Testing (" << std::setw(6) << 35.01 << ", " << std::setw(6) << 135.01 << ") ... ";
  test(hc.getGeoid(35.01, 135.01), 37.0925);

  std::cout << "Testing (" << std::setw(6) << 35.5 << ", " << std::setw(6) << 135.5 << ") ... ";
  test(hc.getGeoid(35.5, 135.5), 36.8691);

  std::cout << "Testing (" << std::setw(6) << 35 << ", " << std::setw(6) << 137 << ") ... ";
  test(hc.getGeoid(35, 137), 38.4267);

  std::cout << "Testing (" << std::setw(6) << 39.2 << ", " << std::setw(6) << 140.9 << ") ... ";
  test(hc.getGeoid(39.2, 140.9), 41.7035);

  std::cout << "Testing (" << std::setw(6) << 43.3 << ", " << std::setw(6) << 141.8 << ") ... ";
  test(hc.getGeoid(43.3, 141.8), 31.3455);

  std::cout << "Testing (" << std::setw(6) << 43 << ", " << std::setw(6) << 141 << ") ... ";
  test(hc.getGeoid(43, 141), 33.5306);

  std::cout << "Testing (" << std::setw(6) << 33.1 << ", " << std::setw(6) << 131.1 << ") ... ";
  test(hc.getGeoid(33.1, 131.1), 33.0331);

  std::cout << "Testing (" << std::setw(6) << 26.6 << ", " << std::setw(6) << 128.1 << ") ... ";
  test(hc.getGeoid(26.6, 128.1), 32.2696);

  // convertHeight Test
  test(hc.convertHeight(35, 135, 0, height_converter::ConvertType::ORTHO2ELLIPS), 37.0557);
  test(hc.convertHeight(35, 135, 0, height_converter::ConvertType::ELLIPS2ORTHO), -37.0557);

  return 0;
}
