cmake_minimum_required(VERSION 3.1)

# ------------------------------------------------------------------------------
# Subproject

project(autocompletion-jni C CXX)
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
get_target_property(_jarFile autocompletion-jar JAR_FILE)
get_target_property(_classDir autocompletion-jar CLASSDIR)

# --- generate jni header files
set(_headerDir "${CMAKE_CURRENT_BINARY_DIR}")
foreach(file IN LISTS ${PROJECT_NAME}_JAVA_SOURCES)
    # make relative to java/ directory and remove .java extension
    string(REPLACE "${PROJECT_SOURCE_DIR}/java/" "" base ${file})
    string(REPLACE ".java" "" base ${base})
    
    # make fully qualified class name
    string(REPLACE "/" "." fqcn ${base})
    
    string(REPLACE "." "_" header ${fqcn})
    set(header "${header}.h")
    list(APPEND ${PROJECT_NAME}_JNI_HEADERS "${header}")
    
    add_custom_command( 
        OUTPUT "${header}"
        COMMAND ${Java_JAVAH_EXECUTABLE}
            -verbose
            -classpath ${_classDir}
            -d ${_headerDir}
            -jni
            ${fqcn}
        )
endforeach()

include_directories(${_classDir} ${_headerDir})

# ------------------------------------------------------------------------------
# Source Files

file(GLOB_RECURSE ${PROJECT_NAME}_C_SOURCES "src/" "*.c")
file(GLOB_RECURSE ${PROJECT_NAME}_CPP_SOURCES "src/" "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS "src/" "*.h") 

# ------------------------------------------------------------------------------
# Build Process

add_library(${PROJECT_NAME} MODULE
    ${${PROJECT_NAME}_C_SOURCES}
    ${${PROJECT_NAME}_CPP_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_JNI_HEADERS}
    )
target_link_libraries(${PROJECT_NAME}
    ${Java_LIBRARIES}
    ${JAVA_JVM_LIBRARY}
    # dont include ${JNI_LIBRARIES} because it includes awt library
    autocompletion-lib
    )
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "autocompletion.jni") 