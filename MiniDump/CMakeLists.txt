cmake_minimum_required(VERSION 3.5)

project(MiniDump LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Way1: Use RelWithDebInfo
set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  Widget.cpp
  Widget.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

# Way2: Use Release mode(MSVC)
# target_compile_options(${PROJECT_NAME} PRIVATE
#     $<$<CONFIG:Release>:
#         /Zi          # Program Database debug info
#         /O2          # Optimize
#         /Ob2         # Inline expansion
#     >
# )

# target_link_options(${PROJECT_NAME} PRIVATE
#     $<$<CONFIG:Release>:
#         /DEBUG             # Generate debug info
#         /OPT:REF           # Eliminate unused functions (keep with /DEBUG)
#         /OPT:ICF           # Identical COMDAT folding
#     >
# )

# # Copy PDB to output directory
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     COMPILE_PDB_NAME "${PROJECT_NAME}"
#     COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb"
# )
