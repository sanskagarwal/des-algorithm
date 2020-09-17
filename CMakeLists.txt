cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DES-Algorithm)

# Flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Files
set(SOURCE_FILES src/des_impl.cpp include/base/des_interface.h src/main.cpp src/utils.cpp
 src/utils.h src/constants.h src/hex_maps.h)

# Include files
include_directories(./include ./src)

# Target
add_executable(des ${SOURCE_FILES})
