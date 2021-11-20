cmake_minimum_required(
  VERSION 3.8
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  hashtable_c
  LANGUAGES C
)

add_library(
  ${PROJECT_NAME}
  src/hashtable.c
)

include_directories(include)

add_subdirectory(test)
