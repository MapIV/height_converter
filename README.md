# height_converter

(Updated 2022/03/24)

Convert height between ellipsoid and orthometric library

## Supported Geoid Models

* EGM2008-1
* GSIGEO2011 Ver2.1

## Usage

```
height_converter::HeightConverter hc;

hc.setGeoidType(height_converter::GeoidType::GSIGEO2011); // Select Geoid Model
// hc.setGeoidType(height_converter::GeoidType::EGM2008);

hc.setGSIGEOGeoidFile(path_to_gsigeo_asc_file);   // Load geoid data file when you select GSIGEO
// hc.setGSIGEOGeoidFile();  // If called with void, it try to read /usr/share/GSIGEO/gsigeo2011_ver2_1.asc

double geoid_heith = hc.getGeoid(lat, lon);   // Get geoid heigth with latitude/longitude in decimal degree

// Convert height between ellipsoid and orthometric
double converted_height = hc.convertHeight(lat, lon, h, height_converter::ConvertType::ORTHO2ELLIPS);
double converted_height = hc.convertHeight(lat, lon, h, height_converter::ConvertType::ELLIPS2ORTHO);
```

## Install

```
sudo apt update
sudo apt install libgeographic-dev geographiclib-tools geographiclib-doc

sudo geographiclib-get-geoids best

mkdir -p test_ws/src
cd test_ws/src/
git clone https://github.com/MapIV/height_converter.git
sudo mkdir /usr/share/GSIGEO
sudo cp height_converter/data/gsigeo2011_ver2_1.asc /usr/share/GSIGEO/
cd ../../
catkin_make -DCMAKE_BUILD_TYPE=Release
```

## Geoid model data

This package contains GSIGEO2011 geoid data file which is provided by Geospatial Information Authority of Japan.

[Official Website of Geospatial Information Authority of Japan](https://fgd.gsi.go.jp/download/geoid.php)

