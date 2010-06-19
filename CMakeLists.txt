cmake_minimum_required(VERSION 2.6)
project(ATHENA_GRAPHICS)

# Settings
if (NOT DEFINED ATHENA_GRAPHICS_SCRIPTING)
    set(ATHENA_GRAPHICS_SCRIPTING OFF CACHE BOOL "Enable scripting support (needs Athena-Scripting)")
endif()

if (NOT DEFINED ATHENA_GRAPHICS_STATIC)
    set(ATHENA_GRAPHICS_STATIC OFF CACHE BOOL "Build Athena-Graphics as a static library")
endif()

# Set the output paths
if (NOT DEFINED ATHENA_BINARY_DIR)
    set(ATHENA_BINARY_DIR "${ATHENA_GRAPHICS_BINARY_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ATHENA_GRAPHICS_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ATHENA_GRAPHICS_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ATHENA_GRAPHICS_BINARY_DIR}/bin")
endif()

# Set the dependencies path
if (NOT DEFINED ATHENA_DEPENDENCIES_DIR)
    set(ATHENA_DEPENDENCIES_DIR "${ATHENA_GRAPHICS_SOURCE_DIR}/dependencies")
endif()

# We only support Intel 32bits builds
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "i386" CACHE INTERNAL "" FORCE)
    set(CMAKE_OSX_ARCHITECTURES_DEFAULT "ppc" CACHE INTERNAL "" FORCE)
endif()

# Setup the dependencies
if (NOT DEFINED ATHENA_MATH_STATIC)
    set(ATHENA_MATH_STATIC ON)
endif()

if (NOT DEFINED ATHENA_CORE_STATIC)
    set(ATHENA_CORE_STATIC ON)
endif()

if (NOT DEFINED ATHENA_ENTITIES_STATIC)
    set(ATHENA_ENTITIES_STATIC ON)
endif()

# Import XMake
if (NOT EXISTS "${ATHENA_DEPENDENCIES_DIR}/xmake/XMake.cmake")
    message(FATAL_ERROR
"Missing dependency: XMake
Athena-Graphics requires the following dependencies:
   - XMake
   - Athena-Math
   - Athena-Core
   - Athena-Entities
   - UnitTest++
   - Ogre
   - FreeImage
   - FreeType
   - ZLib
   - zziplib
They are provided as GIT submodules of this repository.
Did you forgot to execute the following commands?
   git submodule init
   git submodule update")
endif()

include("${ATHENA_DEPENDENCIES_DIR}/xmake/XMake.cmake")

# Process the dependencies
add_subdirectory(dependencies)

# XMake settings
if (ATHENA_GRAPHICS_STATIC)
    xmake_init_static(ATHENA_GRAPHICS)
    xmake_add_link_paths(ATHENA_GRAPHICS "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    xmake_add_link_targets(ATHENA_GRAPHICS Athena-Graphics "${XMAKE_ATHENA_ENTITIES_LINK_TARGETS}")
else()
    xmake_init_dynamic(ATHENA_GRAPHICS)
    xmake_add_link_paths(ATHENA_GRAPHICS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    xmake_add_link_targets(ATHENA_GRAPHICS Athena-Graphics)
endif()

xmake_add_include_paths(ATHENA_GRAPHICS ${ATHENA_GRAPHICS_SOURCE_DIR}/include
                                        ${XMAKE_ATHENA_ENTITIES_INCLUDE_PATHS}
                                        ${XMAKE_OGRE_INCLUDE_PATHS})

if (XMAKE_OGRE_FRAMEWORK)
    xmake_add_link_flags(ATHENA_GRAPHICS ${XMAKE_OGRE_LINK_FLAGS})
else()
    xmake_add_link_paths(ATHENA_GRAPHICS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    xmake_add_link_targets(ATHENA_GRAPHICS Ogre)
endif()

# Subdirectories to process
add_subdirectory(include)
add_subdirectory(src)
