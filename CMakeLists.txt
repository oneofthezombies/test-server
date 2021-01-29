cmake_minimum_required(VERSION 3.17)

project(test-server)
message(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

add_subdirectory(base)
add_subdirectory(test)
add_subdirectory(tcp-server)
add_subdirectory(tcp-client)
add_subdirectory(http-server)
add_subdirectory(http-client)
