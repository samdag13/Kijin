include(FetchContent)
include(GitUtils)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY    https://github.com/glfw/glfw.git
    GIT_TAG           ${GLFW_VERSION}
)

FetchContent_GetProperties
if(NOT glfw_POPULATED)
    message(STATUS "Populating ${PROJECT_NAME}/glfw dependency if needed")
    FetchContent_Populate(glfw)
endif()


set(GLFW_BUILD_DOCS FALSE CACHE BOOL "GLFW default value overwritten" FORCE)
set(GLFW_BUILD_TESTS FALSE CACHE BOOL "GLFW default value overwritten" FORCE)
set(GLFW_BUILD_EXAMPLES FALSE CACHE BOOL "GLFW default value overwritten" FORCE)
set(GLFW_INSTALL FALSE CACHE BOOL "GLFW default value overwritten" FORCE)

add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
set_target_properties(glfw PROPERTIES DEBUG_POSTFIX debug)

string(TOLOWER ${PROJECT_NAME} _project_title)
set(_install_dst_path include/${_project_title}/3rdparty)
install(TARGETS glfw EXPORT ${PROJECT_TITLE}Targets
    LIBRARY_DESTINATION lib NAMELINK_SKIP)

set_target_properties(glfw PROPERTIES
VERSION          "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
SOVERSION        "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
PREFIX           "${${PROJECT_NAME}_LIBRARY_PREFIX}"
INSTALL_NAME_DIR "@rpath"
DEBUG_POSTFIX _debug)

function(target_dependency_glfw _target_name)
    target_link_libraries(${_target_name} PUBLIC glfw)
endfunction()