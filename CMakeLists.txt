
cmake_minimum_required(VERSION 3.21)

## project name and language
project(Tachyon LANGUAGES C CXX)

## C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dep)

add_subdirectory(dep)
add_subdirectory(src)
