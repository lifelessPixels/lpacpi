cmake_minimum_required(VERSION 3.31)
project(lpacpi CXX)

set(SOURCES
    src/main.cpp
    src/byte_stream.cpp
    src/defblock.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(lpacpi ${SOURCES})
set_target_properties(
  lpacpi
  PROPERTIES CXX_STANDARD 23
             CXX_EXTENSIONS OFF
             EXPORT_COMPILE_COMMANDS YES)
target_include_directories(lpacpi PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(lpacpi PRIVATE -ggdb -Wall -Wextra -Werror)
