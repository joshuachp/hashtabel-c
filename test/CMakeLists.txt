cmake_minimum_required(VERSION 3.8)
project(hashtable_test)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(../include)

add_executable(
  hashtable_test
  src/main.cc
)
target_link_libraries(
  hashtable_test
  gtest_main
  hashtable_c
)

include(GoogleTest)
gtest_discover_tests(hashtable_test)
