cmake_minimum_required(VERSION 3.2)

project(TinyAPI VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(TinyApi
    tinyapi.cpp
)

target_include_directories(TinyApi PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
