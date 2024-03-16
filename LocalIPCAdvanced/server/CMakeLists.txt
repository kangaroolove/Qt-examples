cmake_minimum_required(VERSION 3.5)

project(LocalServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Network AxContainer)

include_directories(
	tasks
	../common/packets
	../common
	ui
	lib
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
	tasks/HandleReceiveMessageTask.cpp
	tasks/HandleReceiveMessageTask.h
	tasks/SendTask.cpp
	tasks/SendTask.h
	tasks/UpdateValueTask.cpp
	tasks/UpdateValueTask.h
	tasks/GetValueTask.cpp
	tasks/GetValueTask.h
	tasks/DaqcServerHandleReceiveMessageTask.cpp
	tasks/DaqcServerHandleReceiveMessageTask.h
	../common/packets/Packet.cpp
	../common/packets/Packet.h
	../common/packets/FramePacket.cpp
	../common/packets/FramePacket.h
	../common/packets/ReplyPacket.cpp
	../common/packets/ReplyPacket.h
	lib/daqclib.cpp
	lib/daqclib.h
	../common/StringDef.h
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

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::AxContainer Qt5::Widgets Qt5::Network ${EXTRA_LIBS})