cmake_minimum_required(VERSION 3.0)
project(CovidVisualizer VERSION 1.0.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option for static linking
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "TRUE to statically link SFML, FALSE to dynamically link SFML." FORCE)



# Setup for sfml build type (static/dynamic)
if(${SFML_STATIC_LIBRARIES})
    set(BUILD_SHARED_LIBS FALSE)
else()
    set(BUILD_SHARED_LIBS TRUE)
endif()

# Get sfml library from GitHub
include(ExternalProject)
ExternalProject_Add(sfml
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.5.x"
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/sfml -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
)

# Prevent build for sfml on all targets build
set_target_properties(sfml PROPERTIES EXCLUDE_FROM_ALL TRUE)



# Get csv library from GitHub
include(ExternalProject)
ExternalProject_Add(csv-external
        URL https://raw.githubusercontent.com/ben-strasser/fast-cpp-csv-parser/master/csv.h
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/csv"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/csv"
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        CONFIGURE_COMMAND ""
        DOWNLOAD_NO_EXTRACT TRUE
        DOWNLOAD_NAME "csv.h"

)

add_library(csv INTERFACE)



# Define ${CMAKE_INSTALL_...} variables
include(GNUInstallDirs)



# Specify where third-party libraries are located
link_directories(${CMAKE_BINARY_DIR}/lib/sfml/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/sfml/${CMAKE_INSTALL_INCLUDEDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/csv/${CMAKE_INSTALL_INCLUDEDIR})

# This is required for fast-cpp-csv-parser
find_package(Threads REQUIRED)

# This is required for sfml
find_package(OpenGL REQUIRED)



# Set up csv library
add_dependencies(csv csv-external)
target_include_directories(csv SYSTEM INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/lib/csv)



# Create main target
file(GLOB_RECURSE sources src/*.cpp)
add_executable(CovidVisualizer ${sources})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(${SFML_STATIC_LIBRARIES})
        target_link_libraries(CovidVisualizer csv sfml-audio-s-d sfml-graphics-s-d sfml-window-s-d sfml-network-s-d sfml-system-s-d opengl32 winmm gdi32 opengl32 freetype openal32 flac vorbisenc vorbisfile vorbis ogg ws2_32 Threads::Threads)
    else()
        target_link_libraries(CovidVisualizer csv sfml-audio-d sfml-graphics-d sfml-window-d sfml-network-d sfml-system-d Threads::Threads)
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        target_link_options(CovidVisualizer PRIVATE -mwindows)
    endif()
    if(${SFML_STATIC_LIBRARIES})
        target_link_libraries(CovidVisualizer csv sfml-audio-s sfml-graphics-s sfml-window-s sfml-network-s sfml-system-s opengl32 winmm gdi32 opengl32 freetype openal32 flac vorbisenc vorbisfile vorbis ogg ws2_32 Threads::Threads)
    else()
        target_link_libraries(CovidVisualizer csv sfml-audio sfml-graphics sfml-window sfml-network sfml-system Threads::Threads)
    endif()
endif()



# Make sure third-party libraries are built before executable
add_dependencies(CovidVisualizer sfml)
set_target_properties(CovidVisualizer PROPERTIES EXCLUDE_FROM_ALL TRUE)



# Add define for sfml if static (required by sfml)
if(${SFML_STATIC_LIBRARIES})
    add_compile_definitions(SFML_STATIC)
endif()



# Move dlls
if(NOT ${SFML_STATIC_LIBRARIES})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/openal32.dll"
                ${CMAKE_BINARY_DIR})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-audio-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-graphics-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-network-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-system-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-window-d-2.dll"
                ${CMAKE_BINARY_DIR})
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-audio-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-graphics-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-network-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-system-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET CovidVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-window-2.dll"
                ${CMAKE_BINARY_DIR})
    endif()
endif()


