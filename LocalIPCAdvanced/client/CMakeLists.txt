cmake_minimum_required(VERSION 3.5)

project(DaqcClientLib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_DEBUG_POSTFIX "d")

set(LIB_NAME daqc)

find_package(Qt5 COMPONENTS Core Gui Network REQUIRED)

include_directories(
	../common/packets
	../common
)

list(APPEND EXTRA_LIBS 
)

set(PROJECT_SOURCES
	Client.cpp
	DaqcClient.cpp
	ClientWorker.cpp
	../common/packets/Packet.cpp
	../common/packets/FramePacket.cpp
	../common/packets/RequestUpdatePacket.cpp
	../common/packets/RequestGetPacket.cpp
	../common/packets/ReplyPacket.cpp
)

set(PROJECT_HEADERS
	Client.h
	DaqcClient.h
	ClientWorker.h
	../common/packets/Packet.h
	../common/packets/FramePacket.h
	../common/packets/RequestUpdatePacket.h
	../common/packets/RequestGetPacket.h
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
	${PROJECT_HEADERS}
)

target_link_libraries(${LIB_NAME} PRIVATE Qt5::Gui Qt5::Core Qt5::Network ${EXTRA_LIBS})

install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib)
install(FILES ${PROJECT_HEADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include)

add_subdirectory(ui)