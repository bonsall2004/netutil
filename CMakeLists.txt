cmake_minimum_required(VERSION 3.10)
add_subdirectory(src)

option(NETUTIL_BUILD_EXAMPLES "Build the examples" OFF)
if(NETUTIL_BUILD_EXAMPLES)
message(STATUS "${PROJECT_NAME} examples are enabled")
  add_subdirectory(examples)
endif()
