include(FetchContent)
FetchContent_Declare(
    glew
    GIT_REPOSITORY    https://github.com/nigels-com/glew.git
    GIT_TAG           ${GLEW_VERSION}
)

set(GLEW_DIR "${glew_SOURCE_DIR}")
message(STATUS "${CMAKE_CURRENT_BINARY_DIR}")
FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    message(STATUS "Populating ${PROJECT_NAME}/glew dependency if needed")
    FetchContent_Populate(glew)
    add_subdirectory(${glew_SOURCE_DIR}/build/cmake ${glew_BINARY_DIR})
endif()