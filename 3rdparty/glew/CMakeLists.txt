

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_compile_definitions(GLEW_STATIC)


# Determine the correct library path based on the architecture
set(GLEW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/Release)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  # 64-bit architecture
  set(GLEW_LIB_ARCH_DIR ${GLEW_LIB_DIR}/x64 CACHE INTERNAL "GLEW library directory")
else()
  # 32-bit architecture
  set(GLEW_LIB_ARCH_DIR ${GLEW_LIB_DIR}/Win32 CACHE INTERNAL "GLEW library directory")
endif()

link_directories(${GLEW_LIB_ARCH_DIR})

add_library(glew32s STATIC IMPORTED)
set_target_properties(glew32s PROPERTIES
IMPORTED_LOCATION ${GLEW_LIB_ARCH_DIR}/glew32s.lib
INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)