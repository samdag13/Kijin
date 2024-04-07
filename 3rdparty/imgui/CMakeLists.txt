include(FetchContent)
FetchContent_Declare(
	imgui
	GIT_REPOSITORY	https://github.com/ocornut/imgui.git
	GIT_TAG 	    ${IMGUI_VERSION}
)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    message(STATUS "Populating ${PROJECT_NAME}/imgui dependency if needed")
    FetchContent_Populate(imgui)
endif()

message(STATUS "imgui src ${imgui_SOURCE_DIR}")
file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_link_libraries(imgui glfw)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends  ${glfw_SOURCE_DIR}/include)
set(imgui_SOURCE_DIR ${imgui_SOURCE_DIR} CACHE INTERNAL "Source directories for imgui")