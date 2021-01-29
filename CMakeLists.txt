cmake_minimum_required(VERSION 3.17)

project(test-server)
message(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(source)
