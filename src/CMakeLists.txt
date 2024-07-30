cmake_minimum_required(VERSION 3.28)
project(netutil LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if(WIN32)
  message(STATUS "netutil for windows")
  set(PLATFORM_SOURCES platform/windows/fetch.cpp)
  set(PLATFORM_LIBS wininet)
elseif(UNIX)
  message(STATUS "netutil for unix based systems")
  set(PLATFORM_SOURCES platform/linux/fetch.cpp)
  find_package(Threads REQUIRED)
  set(PLATFORM_LIBS Threads::Threads)
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

set(SOURCES ${PLATFORM_SOURCES}
    platform/non-specific/fetch.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include/private)

option(NETUTIL_BUILD_SHARED "Build the library as a shared library instead of a static library" OFF)

if(NETUTIL_BUILD_SHARED)
  message(STATUS "Netutil will build as a shared library")
  add_library(netutil SHARED ${SOURCES})
else()
  message(STATUS "Netutil will build as a static library")
  add_library(netutil STATIC ${SOURCES})
endif()

target_include_directories(netutil PUBLIC ${CMAKE_SOURCE_DIR}/include/public)
target_link_libraries(netutil PRIVATE ${PLATFORM_LIBS})
