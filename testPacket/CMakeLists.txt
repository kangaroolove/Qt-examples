cmake_minimum_required(VERSION 3.5)

project(testPackets LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
  packets
)

add_executable(${PROJECT_NAME}
  main.cpp
  Widget.cpp
  Widget.h
  packets/Packet.cpp
  packets/Packet.h
  packets/RequestUpdatePacket.cpp
  packets/RequestUpdatePacket.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
