cmake_minimum_required(VERSION 3.0)
project(movingAverage CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
add_executable(${PROJECT_NAME}.out ${PROJECT_NAME}.cc)
