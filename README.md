# CovidVisualizer
Functional programming implementation of a COVID-19 dataset visualizer with Prolog utilization for APLC assignment.

# Building
## Requirements
* [CMake 3.0.0 or newer](https://cmake.org/)
* Any C++ compiler

## Dependencies
Dependencies will be automatically pulled from github using CMake
* [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser)

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


