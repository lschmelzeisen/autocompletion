cmake_minimum_required(VERSION 3.1)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. This is bad practice.")
endif()

# ------------------------------------------------------------------------------
# Project

project(autocompletion C CXX)
set(${PROJECT_NAME}_VERSION "0.0.1")

# Select release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified: defaulting to release.")
endif()
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

list(APPEND AUTOCOMPLETION_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include/")

# ------------------------------------------------------------------------------
# Build Settings

# --- Detect Compiler
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(COMPILER_CLANG 1)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(COMPILER_GNU 1)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(COMPILER_MSVC 1)
endif()

# Shorthand for GNU compatible compilers.
if(COMPILER_CLANG OR COMPILER_GNU)
    set(COMPILER_GNU_COMPATIBLE 1)
endif()

# --- Activate Warnings
if(COMPILER_GNU_COMPATIBLE)
    add_compile_options("-Wall" "-Wextra" "-pedantic")
elseif(COMPILER_MSVC)
    if(COMPILER_OPTIONS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" COMPILE_OPTIONS "${COMPILE_OPTIONS}")
    else()
        add_compile_options("/W4")
    endif()
endif()

# --- Enable C++11
if(COMPILER_GNU_COMPATIBLE)
    if (NOT(CMAKE_CXX_FLAGS MATCHES "-std=c\\+\\+11"))
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif()

# ------------------------------------------------------------------------------
# Build subprojects

add_subdirectory("autocompletion-lib/")
add_subdirectory("autocompletion-server/")
add_subdirectory("autocompletion-jni/")
