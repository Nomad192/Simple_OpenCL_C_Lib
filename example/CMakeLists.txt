cmake_minimum_required(VERSION 3.7)
project(OpenCL_HelloWorld C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_EXTENSIONS OFF)

add_subdirectory(../ Simple_OpenCL_C_Lib)
add_executable(test test.c)
target_link_libraries(test PRIVATE Simple_OpenCL_C_Lib)
target_include_directories(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")
file(COPY cl-src/main.cl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenCL REQUIRED)
add_executable(get_info get_info.c)
target_link_libraries(get_info PRIVATE OpenCL::OpenCL)
