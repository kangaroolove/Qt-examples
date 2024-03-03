cmake_minimum_required(VERSION 3.5)

project(LocalServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets network REQUIRED)

include_directories(
	tasks
	packets
	ui
)

list(APPEND EXTRA_LIBS 
)

set(PROJECT_SOURCES
    main.cpp
	ui/ServerWidget.cpp
	ui/ServerWidget.h
	Server.cpp
	Server.h
	DaqcServer.cpp
	DaqcServer.h
	tasks/HandleRequestTask.cpp
	tasks/HandleRequestTask.h
	tasks/SendReplyTask.cpp
	tasks/SendReplyTask.h
	tasks/SendTask.cpp
	tasks/SendTask.h
	tasks/SendFrameTask.cpp
	tasks/SendFrameTask.h
	tasks/GetValueTask.cpp
	tasks/GetValueTask.h
	tasks/SetValueTask.cpp
	tasks/SetValueTask.h
	tasks/DaqcHandleRequestTask.cpp
	tasks/DaqcHandleRequestTask.h
	packets/Packet.cpp
	packets/Packet.h
	packets/FramePacket.cpp
	packets/FramePacket.h
	packets/ReplyPacket.cpp
	packets/ReplyPacket.h
	packets/RequestPacket.cpp
	packets/RequestPacket.h
)

set(PROJECT_UIS
)

set(PROJECT_RESOURCES
)

add_executable(${PROJECT_NAME} 
	${PROJECT_SOURCES}
	${PROJECT_UIS}
	${PROJECT_RESOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network ${EXTRA_LIBS})