cmake_minimum_required(VERSION 3.18)

if(MSVC)  
  # Suppress LNK4098 warnings: specify the conflicting library
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt.lib")
endif()

# Set the project name and version
project(kijin)

# Project detail that can be used in resource files (e.g., manifest, rc, plist).
set(${PROJECT_NAME}_AUTHOR "Samuel Dagesse")
set(${PROJECT_NAME}_NAME "kijin")
set(${PROJECT_NAME}_DESCRIPTION "Library supporting my applications' development core needs")

# Project version number.
# Using semantic versioning https://semver.org
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")

# By default, the project name is lowered.
string(TOLOWER ${PROJECT_NAME} PROJECT_TITLE)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(examples)
add_subdirectory(3rdparty)

# Core library sources
set(CORE_SOURCE
    src/log.cpp       src/log.h
    src/window.cpp    src/window.h
)

# Generate the shared library from the specified source files
add_library(${PROJECT_NAME} SHARED
    ${CORE_SOURCE}
)

message(STATUS ${CMAKE_SOURCE_DIR}/3rdparty/glew/include)
# Specify include directories for the KIJIN library
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${3RDPARTY_DIR}/glew/include>
    $<BUILD_INTERFACE:${3RDPARTY_DIR}/stb_image>
    $<INSTALL_INTERFACE:include>
)

# Don't forget to link against OpenGL as GLEW depends on it
find_package(OpenGL REQUIRED)

message(STATUS ${GLEW_LIB_ARCH_DIR}/glew32s.lib)
target_link_libraries(${PROJECT_NAME}
    glfw
    ${GLEW_LIB_ARCH_DIR}/glew32s.lib 
    OpenGL::GL
)

add_compile_definitions(GLEW_STATIC)
# Define KIJIN_EXPORTS when compiling this library
target_compile_definitions(${PROJECT_NAME} PRIVATE KIJIN_EXPORTS)

# Install the library
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    INCLUDES DESTINATION include
)

# Install the headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    DESTINATION include/
    FILES_MATCHING PATTERN "*.h"
)

# Export the targets
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)
