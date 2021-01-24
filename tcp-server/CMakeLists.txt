project(tcp-server)
message(${PROJECT_NAME})

add_executable(${PROJECT_NAME} tcp-server.cpp)

add_dependencies(${PROJECT_NAME} Base)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/precompile.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/Base/libBase.dylib)
