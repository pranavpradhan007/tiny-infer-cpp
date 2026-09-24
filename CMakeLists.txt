cmake_minimum_required(VERSION 3.30)
project(tiny-infer-cpp)
set(CMAKE_CXX_STANDARD 17)# Requests C++17.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Tells CMake not to silently fall back to an older standard if C++17 is unavailable.
add_executable(tinyinfer src/main.cpp)