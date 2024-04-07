set(3RDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "3rdParty directory")

#==========================Dependencies versions=============================#
set(
    GLFW_VERSION 3.4 PARENT_SCOPE
    GLEW_VERSION glew-2.2.0 PARENT_SCOPE
    GLM_VERSION  1.0.1 PARENT_SCOPE
    IMGUI_VERSION v1.90.4-docking PARENT_SCOPE
)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(glew)
add_subdirectory(imgui)