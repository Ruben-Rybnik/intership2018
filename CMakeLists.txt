# ----------------------
# This file sets only configuration options
# ----------------------
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

# This project will become the "visual studio solution"
project(Schuelerpraktikum_SS18)

# this prints a message during cmake configuration
message(STATUS "Building ${PROJECT_NAME}")

# one way to organize third party libraries under windows is a folder hierarchy like
# root/x86
#     /x86/release/
#     /x86/debug/
#     /x64
#     /x64/release/
#     /x64/release/library1
#     /x64/release/library2
#     /x64/release/etc
# in our case SDK_BASEPATH should be #root/x64/release/
# this makes it easier to automatically search for the dependencies of the project
set(SDK_BASEPATH CACHE PATH "specifies the sdk base path")
if (SDK_BASEPATH STREQUAL "")
  message(FATAL_ERROR "Set SDK_BASEPATH to the directory containing the 3rd party libraries")
endif()

# we want to use the open source library "Visualization Toolkit" (VTK)
SET(VTK_Required_Version "7.1.1")
SET(VTK_Required_SHORT_Version "7.1")
# CMake searches for certain ".cmake"-files like "VTKConfig.cmake" to detect a library
# If the variable "VTK_DIR" is set to the folder containing such a file, cmake can find the library
set(VTK_DIR "${SDK_BASEPATH}/VTK-${VTK_Required_Version}/lib/cmake/vtk-${VTK_Required_SHORT_Version}/" CACHE PATH "specifies the VTK build directory")
# let cmake find the library VTK
find_package(VTK ${VTK_Required_SHORT_Version} REQUIRED)

# Use folders in the explorer of the visual studio solution.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# add more directories to the "include directories" the compiler can use
include_directories(
	${CMAKE_SOURCE_DIR}/src/
	)

# here lies the CMakeLists.txt that contains our project/application
add_subdirectory(src)
