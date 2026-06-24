cmake_minimum_required(VERSION 3.5)

project(MiniDump LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # Define your centralized PDB directory (e.g., build/Release/AllSymbols)
    set(CENTRAL_PDB_DIR "${CMAKE_BINARY_DIR}/Symbols")

    # Force all Executables and DLLs to output their (linker-generated) PDBs here.
    set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE "${CENTRAL_PDB_DIR}")

    # Do NOT set CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY globally.
    # That global applies to SHARED and EXECUTABLE targets too, and the VS
    # generator writes the path as a relative ../Symbols (no trailing slash),
    # which MSVC interprets as a filename instead of a directory — causing
    # "Forcing recompile of all source files due to missing PDB" on every build.
    # STATIC library compiler PDbs are centralised per-target by
    # centralize_static_lib_pdbs() at the bottom of this file, which writes the
    # correct COMPILE_PDB_NAME + COMPILE_PDB_OUTPUT_DIRECTORY properties.

    # 1. Force compiler to generate debug symbols for Release config (/Zi).
    #    /FS is still needed because STATIC lib per-target PDbs share
    #    the centralised dir and multiple cl.exe processes run in parallel.
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /FS")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Zi /FS")

    # 2. Force linker to generate PDBs and optimize the output (/DEBUG /OPT:REF /OPT:ICF)
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  Widget.cpp
  Widget.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

# ---------------------------------------------------------------------------
# Centralize compiler-generated PDBs for STATIC libraries into ${CENTRAL_PDB_DIR}.
# The Visual Studio generator only honours the *directory* from
# CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY for static libs; it does NOT append a
# per-target file name, so all static libs would otherwise collide on a single
# "Symbols.pdb". Setting COMPILE_PDB_NAME per target produces Symbols/<target>.pdb.
# Run after all targets are defined so every static lib (incl. subdirs) is covered.
if(MSVC)
  # Configurations to set the compile-PDB directory for.
  if(CMAKE_CONFIGURATION_TYPES)
    set(_pdb_configs ${CMAKE_CONFIGURATION_TYPES})
  else()
    set(_pdb_configs ${CMAKE_BUILD_TYPE})
  endif()

  function(centralize_static_lib_pdbs _dir)
    get_property(_targets DIRECTORY "${_dir}" PROPERTY BUILDSYSTEM_TARGETS)
    foreach(_t ${_targets})
      get_target_property(_type ${_t} TYPE)
      if(_type STREQUAL "STATIC_LIBRARY")
        set_target_properties(${_t} PROPERTIES COMPILE_PDB_NAME "${_t}")
        # Use the PER-CONFIG property (COMPILE_PDB_OUTPUT_DIRECTORY_<CONFIG>).
        # The config-less COMPILE_PDB_OUTPUT_DIRECTORY makes the multi-config VS
        # generator append a $(Configuration) subdir (e.g. Symbols/Release/),
        # whereas the per-config one is used verbatim -> Symbols/<target>.pdb.
        foreach(_cfg ${_pdb_configs})
          string(TOUPPER "${_cfg}" _cfg_up)
          set_target_properties(${_t} PROPERTIES
            COMPILE_PDB_OUTPUT_DIRECTORY_${_cfg_up} "${CENTRAL_PDB_DIR}")
        endforeach()
      endif()
    endforeach()
    get_property(_subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
    foreach(_s ${_subdirs})
      centralize_static_lib_pdbs("${_s}")
    endforeach()
  endfunction()

  centralize_static_lib_pdbs("${CMAKE_SOURCE_DIR}")
endif()
