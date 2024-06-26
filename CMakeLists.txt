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
set(${PROJECT_NAME}_DESCRIPTION "C++ Application development toolbox")

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
    src/log.cpp                 src/log.h
    src/base_window.cpp         src/base_window.h
    src/base_application.cpp    src/base_application.h
)

set(GFX_SOURCE
    src/index_buffer.cpp src/index_buffer.h
    src/renderer.cpp src/renderer.h 
    src/shader.cpp src/shader.h 
    src/texture.cpp src/texture.h 
    src/vertex_array.cpp src/vertex_array.h 
    src/vertex_buffer.cpp src/vertex_buffer.h 
)

# Generate the shared library from the specified source files
add_library(${PROJECT_NAME} SHARED
    ${CORE_SOURCE}
    ${GFX_SOURCE}
)


target_precompile_headers(${PROJECT_NAME} PUBLIC
  <string>
  <cassert>
)

# Specify include directories for the KIJIN library
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${3RDPARTY_DIR}/glew/include>
    $<BUILD_INTERFACE:${3RDPARTY_DIR}/stb_image>
    $<BUILD_INTERFACE:${glm_SOURCE_DIR}>    
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>    
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>    
    $<INSTALL_INTERFACE:include>
)

# Don't forget to link against OpenGL as GLEW depends on it
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    ${GLEW_LIB_ARCH_DIR}/glew32s.lib 
    OpenGL::GL
    imgui
)

add_compile_definitions(GLEW_STATIC)
# Define KIJIN_EXPORTS when compiling this library
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    KIJIN_EXPORTS
    STB_IMAGE_IMPLEMENTATION
    $<$<CONFIG:Debug>:OGL_DEBUG=1>
    $<$<CONFIG:Release>:OGL_RELEASE=1>
)

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

