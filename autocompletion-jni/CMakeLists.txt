cmake_minimum_required(VERSION 3.1)

# ------------------------------------------------------------------------------
# Subproject

project(autocompletion-jni CXX)
set(${PROJECT_NAME}_VERSION "0.0.1")

include_directories(${AUTOCOMPLETION_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Dependencies

# --- Java
find_package(Java 1.7 REQUIRED)
include(UseJava)
include_directories(${JAVA_INCLUDE_PATH})

# --- JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Build Jar

# --- compile java files to jar
file(GLOB_RECURSE ${PROJECT_NAME}_JAVA_SOURCES "java/" "*.java")
set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.7" "-target" "1.7")
add_jar(autocompletion-jar
    SOURCES ${${PROJECT_NAME}_JAVA_SOURCES}
    OUTPUT_NAME autocompletion 
    )
get_target_property(${PROJECT_NAME}_CLASS_DIR autocompletion-jar CLASSDIR)

# --- generate jni header files
set(${PROJECT_NAME}_JNI_HEADER_DIR "${CMAKE_CURRENT_BINARY_DIR}/jni-headers")
set_directory_properties(PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES "${${PROJECT_NAME}_JNI_HEADER_DIR}"
    )
    
add_custom_target(${PROJECT_NAME}_JNI_HEADERS)

foreach(file IN LISTS ${PROJECT_NAME}_JAVA_SOURCES)
    # make relative to java/ directory and remove .java extension
    string(REPLACE "${PROJECT_SOURCE_DIR}/java/" "" base ${file})
    string(REPLACE ".java" "" base ${base}) 
    
    # make fully qualified class name
    string(REPLACE "/" "." fqcn ${base})
    
    set(target "${PROJECT_NAME}_JNI_HEADER_${fqcn}") 
    add_custom_target(${target}
        ${Java_JAVAH_EXECUTABLE}
        -classpath ${${PROJECT_NAME}_CLASS_DIR} 
        -d ${${PROJECT_NAME}_JNI_HEADER_DIR}
        -jni
        ${fqcn})
    add_dependencies(${PROJECT_NAME}_JNI_HEADERS ${target})
endforeach()

include_directories(
    ${${PROJECT_NAME}_CLASS_DIR}
    ${${PROJECT_NAME}_JNI_HEADER_DIR}
    )

# ------------------------------------------------------------------------------
# Source Files

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/" "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS "src/" "*.h") 

# ------------------------------------------------------------------------------
# Build Process

add_library(${PROJECT_NAME} MODULE
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    )
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_JNI_HEADERS)
target_link_libraries(${PROJECT_NAME}
    ${Java_LIBRARIES}
    ${JAVA_JVM_LIBRARY}
    # dont include ${JNI_LIBRARIES} because it includes unnecessary awt library
    autocompletion-lib
    )
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "autocompletion.jni"
    ) 