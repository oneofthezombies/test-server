project(tcp-client)
message(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
  TcpClient.cpp
)

add_dependencies(${PROJECT_NAME}
  base
)

target_precompile_headers(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/base/Precompile.h
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_BINARY_DIR}/base/libbase.dylib
)
