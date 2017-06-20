#
# Builds Voronoi Engine.
# Based on the auto-generated CGAL CMakeLists file.
#
# Alex Striff.
#

cmake_minimum_required(VERSION 3.4.0 FATAL_ERROR)

project("Voronoi Engine")
add_definitions(-DVERSION="0.0.1")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/sanitizers-cmake/cmake"
	${CMAKE_MODULE_PATH})

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

set (CMAKE_CXX_STANDARD 11)

if (COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif()

# CGAL and its components
find_package(CGAL QUIET COMPONENTS)

if (NOT CGAL_FOUND)
	message(STATUS "This project requires the CGAL library and will not be compiled.")
	return()
endif()

# include helper file
# include(${CGAL_USE_FILE})

# Boost and its components
find_package(Boost REQUIRED)

if (NOT Boost_FOUND)
	message(STATUS "This project requires the Boost library and will not be compiled.")
	return()
endif()

# SDL2 and its extensions.
find_package(SDL2 REQUIRED)

if ( NOT SDL2_FOUND )
	message(STATUS "This project requires the SDL2 library and will not be compiled.")
	return()
endif()

find_package(SDL2_image REQUIRED)

if ( NOT SDL2_IMAGE_FOUND )
	message(STATUS "This project requires the SDL2 Image library and will not be compiled.")
	return()
endif()

find_package(SDL2TTF REQUIRED)

if ( NOT SDL2TTF_FOUND )
	message(STATUS "This project requires the SDL2 TTF library and will not be compiled.")
	return()
endif()

find_package(SDL2GFX REQUIRED)

if ( NOT SDL2GFX_FOUND )
	message(STATUS "This project requires the SDL2 GFX library and will not be compiled.")
	return()
endif()

# Executables should not be nested within the build tree.
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Use Address Sanitizer.
find_package(Sanitizers)

# Add the definition for the media directory.
add_definitions(-DMEDIA_PATH="${CMAKE_SOURCE_DIR}/media/")

# include for local directory
add_subdirectory(src)

# include for local package

