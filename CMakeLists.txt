cmake_minimum_required(VERSION 3.18)

# Set the project name and version
project(CATCHER)

# Project detail that can be used in ressource files (e.g. manifest, rc, plist).
set(${PROJECT_NAME}_AUTHOR "Samuel Dagesse")
set(${PROJECT_NAME}_NAME "catcher")
set(${PROJECT_NAME}_DESCRIPTION "Library supporting my applications' development core needs")
set(${PROJECT_NAME}_COPYRIGHT "(C) Moveck Solution inc., ${${PROJECT_NAME}_CURRENT_YEAR}")
set(${PROJECT_NAME}_LOGO_PATH "${PROJECT_SOURCE_DIR}/doc/images/kaleido-logo.png")

# Project version number.
# using sementic versioning https://semver.org
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")

# set(${PROJECT_NAME}_VERSION_STRING "")
if(NOT ${PROJECT_NAME}_VERSION_STRING)
    set(${PROJECT_NAME}_VERSION_STRING ${${PROJECT_NAME}_VERSION})
endif()

# By default, the project name is lowered.
string(TOLOWER ${PROJECT_NAME} PROJECT_TITLE)


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)



set( CORE_SOURCE
    src/core/Test.cpp src/core/Test.h
)

# Generate the shared library from the specified source file
add_library(CATCHER SHARED
    ${CORE_SOURCE}
)

add_subdirectory(examples)
