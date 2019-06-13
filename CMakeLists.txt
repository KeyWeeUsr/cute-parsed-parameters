cmake_minimum_required(VERSION 3.10)
project(CuteParsedParameters)

file(STRINGS "${PROJECT_SOURCE_DIR}/warnings.txt" CXX_WARNINGS_RAW)
set(string(REPLACE "\n" " " CXX_WARNINGS ${CXX_WARNINGS_RAW}))

set(CMAKE_GENERATOR "Unix Makefiles")
message("Creating Unix Makefile build")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/output")

include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(
    cutepp SHARED
    "${PROJECT_SOURCE_DIR}/src/parser.cpp"
)
add_library(
    cutepp_static STATIC
    "${PROJECT_SOURCE_DIR}/src/parser.cpp"
)

enable_testing()

macro(test EXECUTABLE)
# compile test
add_executable(
    ${EXECUTABLE}
    "${PROJECT_SOURCE_DIR}/tests/${EXECUTABLE}.cpp"
)

# link against archive built above in ./lib
target_link_libraries(${EXECUTABLE} cutepp_static)

# add to CTest
add_test(
    NAME test${EXECUTABLE}
    COMMAND ${EXECUTABLE}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/output"
)
endmacro()

# tests
test(setparametersempty)
test(setparameters)
test(setnamedparameters)
