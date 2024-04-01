set(3RDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "3rdParty directory")

#==========================Dependencies versions=============================#
set(
    GLFW_VERSION 3.4 PARENT_SCOPE
    GLEW_VERSION glew-2.2.0 PARENT_SCOPE
)
add_subdirectory(glfw)
add_subdirectory(glew)