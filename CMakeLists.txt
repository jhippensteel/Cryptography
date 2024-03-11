cmake_minimum_required(VERSION 3.26)
project(crypto)

set(CMAKE_CXX_STANDARD 23)

add_executable(crypto main.cpp)

add_subdirectory(clip)
target_link_libraries(crypto clip)
