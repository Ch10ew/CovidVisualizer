# CovidVisualizer
Functional programming implementation of a COVID-19 dataset visualizer with Prolog utilization for APLC assignment.

# Building
## Requirements
* [CMake 3.0.0 or newer](https://cmake.org/)
* Any C++17 compiler

## Dependencies
Dependencies will be automatically pulled from github using CMake
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)

Tested with the following set:
* GCC 12.1.0 x86_64-w64-mingw32
* SFML - branch 2.5.x, commit 2f11710abc5aa478503a7ff3f9e654bd2078ebab
* fast-cpp-scv-parser - branch master, commit 5a417973b4cea674a5e4a3b88a23098a2ab75479
* Dear ImGui - branch master, commit e99c4fc6688e218a0e5da50f56638aebab45da9b
* ImGui-SFML - branch master, commit a80d9547832c57a149cda452ed9456def5bb6328
* 

## CMake
Example:
```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install
make
```

Example for Unix Makefiles:
```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install -G "Unix Makefiles"
make
```

# Licenses
* This project is under the [MIT license](https://opensource.org/licenses/MIT)
* [SFML](https://github.com/SFML/SFML) is under the [zlib/libpng license](https://opensource.org/licenses/Zlib)
* [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser) is under the [BSD-3-Clause license](https://opensource.org/licenses/BSD-3-Clause)
* [Dear ImGui](https://github.com/ocornut/imgui) is under the [MIT license](https://opensource.org/licenses/MIT)
* [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) is under the [MIT license](https://opensource.org/licenses/MIT)
