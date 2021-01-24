cmake_minimum_required(VERSION 3.17)

project(test-server)
message(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Base)
add_subdirectory(test)
add_subdirectory(tcp-server)
add_subdirectory(tcp-client)
add_subdirectory(http-server)
add_subdirectory(http-client)
