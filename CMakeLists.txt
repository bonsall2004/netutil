cmake_minimum_required(VERSION 3.10)
project(netutil VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src)

option(NETUTIL_BUILD_EXAMPLES "Build the examples" OFF)
if(NETUTIL_BUILD_EXAMPLES)
message(STATUS "${PROJECT_NAME} examples are enabled")
  add_subdirectory(examples)
endif()
