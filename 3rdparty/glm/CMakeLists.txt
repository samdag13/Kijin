include(FetchContent)

set(GLM_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	${GLM_VERSION}
)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  # Note: No need to add_subdirectory since GLM is header-only
endif()
message(STATUS " GLM include dir: ${glm_SOURCE_DIR}/src")
set(GLM_INCLUDE_DIR ${glm_SOURCE_DIR}/src CACHE INTERNAL "Path to GLM include directory")