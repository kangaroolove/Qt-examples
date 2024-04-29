cmake_minimum_required(VERSION 3.5)

project(UnitTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Avoid DartConfiguration.tcl cannot be found
include (CTest)

find_package(Qt5 COMPONENTS Test REQUIRED)

add_executable(${PROJECT_NAME}
  Functions.cpp
  Functions.h
  TestFunctions.cpp
  TestFunctions.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Test)

add_test(NAME TestUnitTest COMMAND ${PROJECT_NAME})