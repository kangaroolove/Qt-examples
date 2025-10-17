# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build System

This project uses CMake with Qt5 and generates Visual Studio project files on Windows.

### Build Commands
```bash
# Configure and generate build files
mkdir build
cd build
cmake ..

# Build the project (Visual Studio)
cmake --build . --config Debug
cmake --build . --config Release

# Alternative: Use Visual Studio directly
# Open build/GenericQtProject.sln in Visual Studio
```

### Run Application
```bash
# From build directory
Debug/GenericQtProject.exe
# or
Release/GenericQtProject.exe
```

## Project Architecture

### Core Structure
- **main.cpp**: Application entry point, creates QApplication and shows main Widget
- **Widget.h/cpp**: Main widget class inheriting from QWidget with Q_OBJECT macro for Qt's meta-object system
- **CMakeLists.txt**: Build configuration targeting Qt5::Widgets with auto-generation features enabled

### Qt Configuration
- Uses Qt5.12.10 with MSVC 2015 64-bit toolchain
- Auto-generation enabled: AUTOUIC, AUTOMOC, AUTORCC
- C++11 standard required
- Single executable linking against Qt5::Widgets

### Historical Context
Based on git history, this project previously included PDF generation and printing functionality with paint event handling. The current codebase appears to be a simplified version that may serve as a template or starting point for Qt applications.

## Development Notes

### Qt Dependencies
- Qt5 installation required at: D:/Qt/Qt5.12.10/5.12.10/msvc2015_64/
- CMake 3.5+ required
- Visual Studio 2015+ toolchain for Windows builds

### Build Output
- Executable and Qt runtime dependencies are automatically copied to build/Debug/ or build/Release/
- Qt plugins (platforms, imageformats, etc.) are included for distribution