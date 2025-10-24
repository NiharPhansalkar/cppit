cmake_minimum_required(VERSION 3.16)
project(cppit LANGUAGES CXX)

# Use the latest available C++ version (C++23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable compile_commands.json for better VSCode IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include header files
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(cppit
    cppit.cpp
    ${SOURCES}
    ${HEADERS}
)

# Link required libraries
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

target_link_libraries(cppit PRIVATE OpenSSL::SSL OpenSSL::Crypto ZLIB::ZLIB)

# Optional: warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cppit PRIVATE -Wall -Wextra -Wpedantic)
endif()