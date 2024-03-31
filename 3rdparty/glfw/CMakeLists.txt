include(FetchContent)

# Force GLFW to build as static library
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY    https://github.com/glfw/glfw.git
    GIT_TAG           ${GLFW_VERSION}
)

FetchContent_MakeAvailable(glfw)
if(NOT glfw_POPULATED)
    message(STATUS "Populating ${PROJECT_NAME}/glfw dependency if needed")
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()