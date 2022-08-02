# CovidVisualizer
Functional programming implementation of a COVID-19 dataset visualizer with Prolog utilization for APLC assignment.

# Dependencies
The following dependencies will be automatically pulled from github using CMake
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)

The following dependencies must be **manually installed**
* [SWI-Prolog 8.4.3-1](https://www.swi-prolog.org/download/stable)

This repository is tested with the following set:
* Windows 10 (64 bit)
* GCC 12.1.0 x86_64-w64-mingw32
* SFML - branch 2.5.x, commit 2f11710abc5aa478503a7ff3f9e654bd2078ebab
* fast-cpp-scv-parser - branch master, commit 5a417973b4cea674a5e4a3b88a23098a2ab75479
* Dear ImGui - branch master, commit e99c4fc6688e218a0e5da50f56638aebab45da9b
* ImGui-SFML - branch master, commit a80d9547832c57a149cda452ed9456def5bb6328
* SWI-Prolog 8.4.3-1 for Microsoft Windows (64 bit)

## Note on SWI-Prolog
SWI-Prolog is not automatically pulled and built using CMake because the swipl-devel repository itself does not recommend building from source due to dependency issues (and I did try but I gave up). Hence, it is recommended to use the installer.


# Building
## Requirements
* [CMake 3.0.0 or newer](https://cmake.org/)
* Any C++17 compiler
* [SWI-Prolog 8.4.3-1](https://www.swi-prolog.org/download/stable)

## Prerequisites
Download and install CMake, a C++ Compiler, and SWI-Prolog.

## CMake
The following options are available to be set:
| Options                     | Description                                                    |
|:---------------------------:| -------------------------------------------------------------- |
| SWI_PROLOG_BIN_DIR          | The bin/ folder of SWI-Prolog                                  |
| SWI_PROLOG_INCLUDE_DIR      | The include/ folder of SWI-Prolog                              |
| SWI_PROLOG_LIBRARY          | The lib/ folder of SWI-Prolog                                  |
| SFML_STATIC_LIBRARIES=FALSE | (Optional) Statically link SFML libraries with the executable? |

The options not marked Optional **must be set**.

Example for CMake CLI targeting Unix Makefiles:
```
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=../install -DSWI_PROLOG_LIBRARY=lib/swipl/bin -DSWI_PROLOG_INCLUDE_DIR=lib/swipl/include -DSWI_PROLOG_BIN_DIR=lib/swipl/bin
make
```


# Licenses
* This project is under the [MIT license](https://opensource.org/licenses/MIT)
* [SFML](https://github.com/SFML/SFML) is under the [zlib/libpng license](https://opensource.org/licenses/Zlib)
* [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser) is under the [BSD-3-Clause license](https://opensource.org/licenses/BSD-3-Clause)
* [Dear ImGui](https://github.com/ocornut/imgui) is under the [MIT license](https://opensource.org/licenses/MIT)
* [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) is under the [MIT license](https://opensource.org/licenses/MIT)
* [SWI-Prolog] is under the [BSD-2-Clause license](https://opensource.org/licenses/BSD-2-Clause)
