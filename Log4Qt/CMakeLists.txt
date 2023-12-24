cmake_minimum_required(VERSION 3.5)

project(TestLog4Qt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

list(APPEND EXTRA_LIBS debug ${PROJECT_SOURCE_DIR}/Log4Qt/lib/log4qt_d.lib)
list(APPEND EXTRA_LIBS optimized ${PROJECT_SOURCE_DIR}/Log4Qt/lib/log4qt.lib)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Log4Qt/include")

add_executable(${PROJECT_NAME}
  main.cpp
  Widget.cpp
  Widget.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets ${EXTRA_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES})
