cmake_minimum_required(VERSION 3.10)

project(TigerBoundaryMapper VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# Include directories
include_directories(include ${PostgreSQL_INCLUDE_DIRS})

# Library: psql_wrapper
add_library(psql_wrapper STATIC
    src/lib/psql_wrapper/psql_wrapper.cpp
)
target_link_libraries(psql_wrapper PRIVATE ${PostgreSQL_LIBRARIES})

# Library: tiger_shape_mapper
add_library(tiger_shape_mapper STATIC
    src/lib/tiger_shape_mapper/rtc_bnd_wrapper.cpp
    src/lib/tiger_shape_mapper/tiger_shape_file_parser.cpp
)
target_link_libraries(tiger_shape_mapper PRIVATE psql_wrapper)

# Executable: shape_data_app
add_executable(shape_data_app
    src/app/shape_data_app/shape_data_app.cpp
)

target_link_libraries(shape_data_app PRIVATE tiger_shape_mapper psql_wrapper)
