
cmake_minimum_required(VERSION 3.21)

## project name and language
project(Tachyon LANGUAGES C CXX)

## C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dep)

add_subdirectory(dep)
add_subdirectory(src)
