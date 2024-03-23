cmake_minimum_required(VERSION 3.5)

project(LocalClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_NAME daqc_client)

find_package(Qt5 COMPONENTS Core Gui network REQUIRED)

include_directories(
	../common/packets
	../common
)

list(APPEND EXTRA_LIBS 
)

set(PROJECT_SOURCES
	Client.cpp
	Client.h
	DaqcClient.cpp
	DaqcClient.h
	Worker.cpp
	Worker.h
	../common/packets/Packet.cpp
	../common/packets/Packet.h
	../common/packets/FramePacket.cpp
	../common/packets/FramePacket.h
	../common/packets/RequestUpdatePacket.cpp
	../common/packets/RequestUpdatePacket.h
	../common/packets/RequestGetPacket.cpp
	../common/packets/RequestGetPacket.h
	../common/packets/ReplyPacket.cpp
	../common/packets/ReplyPacket.h
	../common/StringDef.h
)

set(PROJECT_UIS
)

set(PROJECT_RESOURCES
)

add_library(${LIB_NAME} STATIC
	${PROJECT_SOURCES}
	${PROJECT_UIS}
	${PROJECT_RESOURCES}
)

target_link_libraries(${LIB_NAME} PRIVATE Qt5::Gui Qt5::Core Qt5::Network ${EXTRA_LIBS})