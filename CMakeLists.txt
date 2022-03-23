cmake_minimum_required(VERSION 2.8.3)
project(height_converter)

find_package(catkin REQUIRED COMPONENTS)

find_pacakge(PkgConfig)
find_path(GeographicLib INCLUDE_DIR GeographicLib/config.h
  PATH_SUFFIXES GeographicLib
)
set(GeographicLib_LIBRARIES
  NAMES Geographic
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES height_converter
)

include_directories(
  include
  ${GeographicLib_INCLUDE_DIRS}
)
link_directories(
  /usr/local/lib
)

add_library(gnss
  src/height_converter.cpp
)
