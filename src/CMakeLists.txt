cmake_minimum_required(VERSION 3.1)

# ------------------------------------------------------------------------------
# Source Files

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_HEADER  "*.h")

# ------------------------------------------------------------------------------
# Build Process

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADER})
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
    ${ZeroMQ_LIBRARIES}
    )
