# CovidVisualizer
Functional programming implementation of a COVID-19 dataset visualizer with Prolog utilization for APLC assignment.

# Building
## Requirements
* [CMake 3.0.0 or newer](https://cmake.org/)
* Any C++ compiler

## Dependencies
Dependencies will be automatically pulled from github using CMake
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)

Tested version set:
* SFML - branch 2.5.x, commit 2f11710abc5aa478503a7ff3f9e654bd2078ebab
* fast-cpp-scv-parser - branch master, commit 5a417973b4cea674a5e4a3b88a23098a2ab75479
* Dear ImGui - branch master, commit e99c4fc6688e218a0e5da50f56638aebab45da9b
* ImGui-SFML - branch master, commit a80d9547832c57a149cda452ed9456def5bb6328

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


