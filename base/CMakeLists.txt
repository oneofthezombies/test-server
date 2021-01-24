project(base)
message(${PROJECT_NAME})

add_library(${PROJECT_NAME} SHARED
        Error.cpp
        FileDescriptor.cpp)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Precompile.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
