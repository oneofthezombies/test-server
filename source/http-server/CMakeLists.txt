project(http-server)
message(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
  HttpServer.cpp
)

add_dependencies(${PROJECT_NAME}
  base
)

target_precompile_headers(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/source/Precompile.h
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/source/
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_BINARY_DIR}/source/base/libbase.dylib
)
