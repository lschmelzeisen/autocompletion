cmake_minimum_required(VERSION 3.1)

# ------------------------------------------------------------------------------
# Subproject

project(autocompletion-lib CXX)
set(${PROJECT_NAME}_VERSION "0.0.1")

include_directories(${AUTOCOMPLETION_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Source Files

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/" "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS "src/" "*.h")

# ------------------------------------------------------------------------------
# Build Process

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    )
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "autocompletion")