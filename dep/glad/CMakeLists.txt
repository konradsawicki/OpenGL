cmake_minimum_required(VERSION 3.22)

## project name and language
project(glad LANGUAGES CXX)

add_library(glad STATIC src/glad.c)

target_include_directories(glad PRIVATE include)