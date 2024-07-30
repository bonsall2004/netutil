@mainpage Getting Started

# Installation

## Download

```bash
git clone https://github.com/bonsall2004/netutil.git 
```

## CMake 
```cmake
cmake_minimum_required(VERSION 3.10)
project(my-project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE main.cpp)

add_executable(my-application ${SOURCES})

target_link_libraries(my-application PRIVATE netutil)
```

to your build command, it will build shared

## Build for Visual Studio
```bash
cd ./netutils
```
Create a directory for the build cache and enter into it
```bash
mkdir build
cd ./build
```
Change the string to whichever version you're generating for, if you don't know: you can find out with a quick google search.
```bash
cmake -G "Visual Studio 16 2019" <Build Options> ../
```

Then you can add it to your visual studio solution.

# Build Options

## Shared Library (Dynamic Library)
```
-DNETUTIL_BUILD_SHARED=ON
```

## Examples
```
-DNETUTIL_BUILD_EXAMPLES=ON
```
