#ifndef M4_GSIGEO_HPP
#define M4_GSIGEO_HPP

#include <string>
#include <vector>

namespace height_converter
{
class GSIGEO2011
{
public:
  GSIGEO2011();
  ~GSIGEO2011();
  void loadGeoidMap(const std::string& geoid_file);
  double getGeoid(const double& lat, const double& lon);

private:
  // Geoid data
  std::vector<std::vector<double>> geoid_map_;  // geoid_map_[lat][lon]
  int column_size_ = 1201;
  int row_size_ = 1801;

  // Flag
  bool is_geoid_loaded_ = false;
};
}

#endif
