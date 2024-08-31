cmake_minimum_required(VERSION 3.2)

project(TinyAPI VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        b514bdc898e2951020cbdca1304b75f5950d1f59 # v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(test)

add_library(TinyApi
    src/tinyapi.cpp
)
