cmake_minimum_required(VERSION 3.14)
project(cppit LANGUAGES CXX)

# Use the latest available C++ version (C++23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compile_commands.json for better VSCode IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include directory for headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Gather all .cpp files (including cppit.cpp at root)
file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/cppit.cpp
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Define the executable
add_executable(cppit ${SOURCES})