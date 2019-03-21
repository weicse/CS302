cmake_minimum_required(VERSION 3.2.2)
project(PA06)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(PA06 ${SOURCES})