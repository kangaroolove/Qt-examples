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
	lib/Daqc
)

list(APPEND EXTRA_LIBS debug ${PROJECT_SOURCE_DIR}/lib/Log4Qt/lib/log4qt_d.lib)
list(APPEND EXTRA_LIBS optimized ${PROJECT_SOURCE_DIR}/lib/Log4Qt/lib/log4qt.lib)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/lib/Log4Qt/include")

set(PROJECT_SOURCES
    main.cpp
	ui/ServerWidget.cpp
	ui/ServerWidget.h
	Server.cpp
	Server.h
	DaqcServer.cpp
	DaqcServer.h
	../common/packets/Packet.cpp
	../common/packets/Packet.h
	../common/packets/CommandPacket.cpp
	../common/packets/CommandPacket.h
	../common/packets/RequestUpdatePacket.cpp
	../common/packets/RequestUpdatePacket.h
	../common/packets/RequestPacket.cpp
	../common/packets/RequestPacket.h
	../common/packets/GetInfoPacket.cpp
	../common/packets/GetInfoPacket.h
	../common/packets/FramePacket.cpp
	../common/packets/FramePacket.h
	lib/Daqc/daqclib.cpp
	lib/Daqc/daqclib.h
	../common/DaqcClientDef.h
	ServerWorker.cpp
	ServerWorker.h
	ResourceManager.cpp
	ResourceManager.h
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
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES})