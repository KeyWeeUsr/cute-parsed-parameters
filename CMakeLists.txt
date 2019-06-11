cmake_minimum_required(VERSION 3.10)
project(CuteParsedParameters)

file(STRINGS "${PROJECT_SOURCE_DIR}/warnings.txt" CXX_WARNINGS_RAW)
set(string(REPLACE "\n" " " CXX_WARNINGS ${CXX_WARNINGS_RAW}))

set(CMAKE_GENERATOR "Unix Makefiles")
message("Creating Unix Makefile build")

include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(
    cutepp SHARED
    "${PROJECT_SOURCE_DIR}/src/parser.cpp"
)
add_library(
    cutepp_static STATIC
    "${PROJECT_SOURCE_DIR}/src/parser.cpp"
)
