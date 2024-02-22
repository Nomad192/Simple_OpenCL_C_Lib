cmake_minimum_required(VERSION 3.7)
project(Simple_OpenCL_C_Lib C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_EXTENSIONS OFF)

find_package(OpenCL REQUIRED)

include_directories(include)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(LIB_SRC
        ${SRC_DIR}/init.c
)

set(LIB_INC
        ${INC_DIR}/SCL.h
)

add_library(${PROJECT_NAME} ${LIB_INC} ${LIB_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC OpenCL::OpenCL)
