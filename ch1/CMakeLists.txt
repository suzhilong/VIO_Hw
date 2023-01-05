cmake_minimum_required(VERSION 3.0)
project(check_update)

set(CMAKE_BUILD_TYPE "Debug")

include_directories("/usr/include/eigen3")
add_executable(check_update check_quaterniond_so3_update.cpp)

find_package(FMT REQUIRED)
target_link_libraries(check_update fmt::fmt)