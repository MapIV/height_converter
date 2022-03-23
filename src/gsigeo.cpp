#include <height_converter/gsigeo.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include <boost/algorithm/string.hpp>

namespace height_converter
{

std::vector<std::string> split(std::string input, char delimiter)
{
  std::istringstream stream(input);
  std::string field;
  std::vector<std::string> result;

  while (std::getline(stream, field, delimiter))
  {
    if (field != std::string(" ") && !field.empty() && field != "\n" && field != "\r")
      result.push_back(field);
  }
  return result;
}

GSIGEO2011::GSIGEO2011()
{
}

GSIGEO2011::~GSIGEO2011()
{
}

void GSIGEO2011::loadGeoidMap(const std::string& geoid_file)
{
  std::ifstream ifs(geoid_file);
  if (!ifs)
  {
    std::cerr << "Error: Cannot open Geoid data file: " << geoid_file << std::endl;
    exit(2);
  }

  geoid_map_.reserve(row_size_);
  for (int i = 0; i < row_size_; i++)
  {
    geoid_map_[i].reserve(column_size_);
  }

  std::string curr_line;
  // Skip header line
  std::getline(ifs, curr_line);

  int i = 0, j = 0;

  while (std::getline(ifs, curr_line))
  {
    std::vector<std::string> str_vec = split(curr_line, ' ');

    for (int k = 0; k < str_vec.size(); k++)
    {
      geoid_map_[i][j] = std::stod(str_vec[k]);
      j++;
      
    }
    if (j == column_size_) 
    {
      j = 0;
      i++;
    }
  }
  is_geoid_loaded_ = true;
}

double GSIGEO2011::getGeoid(const double& lat, const double& lon)
{
  if (!is_geoid_loaded_)
  {
    std::cerr << "Error: Geoid map is not loaded" << std::endl;
    exit(1);
  }
  const double lat_min = 20;
  const double lon_min = 120;
  const double d_lat = 1.0 / 60.0;
  const double d_lon = 1.5 / 60.0;

  const int i_lat = std::floor((lat - lat_min) / d_lat);
  const int i_lon = std::floor((lon - lon_min) / d_lon);
  const int j_lat = i_lat + 1;
  const int j_lon = i_lon + 1;

  const double t = (((lat - lat_min) / d_lat) - i_lat) / d_lat;
  const double u = (((lon - lon_min) / d_lon) - i_lon) / d_lon;

  if (i_lat < 0 || i_lat >= row_size_ - 1 || i_lon < 0 || i_lon >= column_size_ - 1)
  {
    std::cerr << "Error: latitude/longitude is out of range (20~50, 120~150)" << std::endl;
    std::cerr << (lat, lon) << std::endl;
    exit(1);
  }

  if (geoid_map_[i_lat][i_lon] == 999 || geoid_map_[i_lat][j_lon] == 999 || geoid_map_[j_lat][i_lon] == 999 || geoid_map_[j_lat][j_lon] == 999)
  {
    std::cerr << "Error: Not supported area" << std::endl;
    exit(1);
  }

  double geoid = (1-t)*(1-u)*geoid_map_[i_lat][i_lon] + (1-t)*u*geoid_map_[i_lat][j_lon] + t*(1-u)*geoid_map_[j_lat][i_lon] + t*u*geoid_map_[j_lat][j_lon];

  return geoid;
  // if (xx < 1e-5) iadx = 0;
  // else if ((1 - xx) < 1e-5) iadx = 1;

  // if (yy < 1e-5) iady = 0;
  // else if ((1 - yy) < 1e-5) iady = 1;

  // if (iady >= 0)
  // {
  //   if (iadx >= 0)
  //   {
  //     return geoid_map_[i_lat + iady][i_lon + iadx];
  //   }
  //   else if (geoid_map_[i_lat + iady][i_lon] == 999.000 || geoid_map_[i_lat + iady][j_lon] == 999.000)
  //   {
  //     return 999.000;
  //   }
  //   else
  //   {
  //     return (1 - x) * geoid_map_[i_lat + iady][i_lon] + x * geoid_map_[i_lat + iady][j_lon];
  //   }
  // }
  // else
  // {
  //   if (iadx >= 0)
  //   {
  //     if (geoid_map_[i_lat][i_lon + iadx] == 999.000 || geoid_map_[j_lat][i_lon + iadx] == 999.000)
  //     {
  //       return 999.000;
  //     }
  //     else
  //     {
  //       return (1 - y) * geoid_map_[i_lat][i_lon + iadx] + y * geoid_map_[j_lat][i_lon + iadx];
  //     }
  //   }
  // }

  // if (geoid_map_[j_lat][i_lon] == 999.000 || geoid_map_[j_lat][j_lon] == 999.000 || geoid_map_[i_lat][i_lon] == 999.000 || geoid_map_[i_lat][j_lon] == 999.000)
  // {
  //   return 999.000;
  // }
  // else
  // {
  //   return (1 - x) * (1 - y) * geoid_map_[i_lat][i_lon] + y * (1 - x) * geoid_map_[j_lat][i_lon] + x * (1 - y) * geoid_map_[i_lat][j_lon] + x * y * geoid_map_[j_lat][j_lon];
  // }
}
}   // namespace height_converter
