project(http-server)
message(${PROJECT_NAME})

add_executable(${PROJECT_NAME} http-server.cpp)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/precompile.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
