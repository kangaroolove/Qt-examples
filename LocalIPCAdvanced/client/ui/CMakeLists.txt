cmake_minimum_required(VERSION 3.5)

project(LocalClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

include_directories(
	../
)

set(PROJECT_SOURCES
	main.cpp
	ClientWidget.cpp
	ClientWidget.h
)

set(PROJECT_UIS
)

set(PROJECT_RESOURCES
)

message(${PROJECT_SOURCE_DIR})

list(APPEND EXTRA_LIBS debug ${PROJECT_SOURCE_DIR}/../lib/Log4Qt/lib/log4qt_d.lib)
list(APPEND EXTRA_LIBS optimized ${PROJECT_SOURCE_DIR}/../lib/Log4Qt/lib/log4qt.lib)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/../lib/Log4Qt/include")

add_executable(${PROJECT_NAME}
	${PROJECT_SOURCES}
	${PROJECT_UIS}
	${PROJECT_RESOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE daqc Qt5::Widgets Qt5::Network ${EXTRA_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES})