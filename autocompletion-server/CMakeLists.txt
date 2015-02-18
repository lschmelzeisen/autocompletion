cmake_minimum_required(VERSION 3.1)

# ------------------------------------------------------------------------------
# Subproject

project(autocompletion-server CXX)
set(${PROJECT_NAME}_VERSION "0.0.1")

include_directories(${AUTOCOMPLETION_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Dependencies

# --- Boost
find_package(Boost 1.57 COMPONENTS system filesystem program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# --- ZeroMq
find_package(ZeroMQ REQUIRED)
include_directories(${ZeroMQ_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Source Files

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/" "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS "src/" "*.h")

# ------------------------------------------------------------------------------
# Build Process

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    )
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
    ${ZeroMQ_LIBRARIES}
    autocompletion-lib
    )