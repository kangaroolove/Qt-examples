cmake_minimum_required(VERSION 3.5)

project(SerialPort LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

add_executable(SerialPort
  main.cpp
  widget.cpp
  widget.h
  SerialPortWorker.cpp
  SerialPortWorker.h
  Classes.h
)

target_link_libraries(SerialPort PRIVATE Qt5::Widgets Qt5::SerialPort)
