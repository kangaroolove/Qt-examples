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
	../common/packets
	ui
	../common/packets/replyPackets
	../common/packetFactory
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
	tasks/DaqcServerHandleReceiveMessageTask.cpp
	tasks/DaqcServerHandleReceiveMessageTask.h
	../common/packets/Packet.cpp
	../common/packets/Packet.h
	../common/packets/FramePacket.cpp
	../common/packets/FramePacket.h
	../common/packets/ReplyPackets/ReplyPacket.cpp
	../common/packets/ReplyPackets/ReplyPacket.h
	../common/packets/ReplyPackets/ReplyGetTest.cpp
	../common/packets/ReplyPackets/ReplyGetTest.h
	../common/packetFactory/PacketFactory.cpp
	../common/packetFactory/PacketFactory.h
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