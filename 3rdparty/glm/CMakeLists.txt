include(FetchContent)

set(GLM_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	${GLM_VERSION}
)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    message(STATUS "Populating ${PROJECT_NAME}/glm dependency if needed")
    FetchContent_Populate(glm)
  # Note: No need to add_subdirectory since GLM is header-only
endif()
set(glm_SOURCE_DIR ${glm_SOURCE_DIR} CACHE INTERNAL "Path to GLM include directory")