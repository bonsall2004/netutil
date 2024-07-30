project(netutil-examples-fetch LANGUAGES CXX)

add_executable(example_fetch fetch.cpp)
target_link_libraries(example_fetch PRIVATE netutil)