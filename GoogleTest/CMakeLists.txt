cmake_minimum_required(VERSION 3.5)

project(GoogleTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME}
  Functions.cpp
  Functions.h
  TestFunctions.cpp
  TestFunctions.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})