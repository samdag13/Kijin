project(glew)
set(GLEW_SOURCE
    src/glew.c
)

set(GLEW_HEADERS
    include/GL/glew.h
    include/GL/wglew.h
    include/GL/glxew.h
)

add_library(glew STATIC ${GLEW_SOURCE} ${GLEW_HEADERS})

target_include_directories(glew PUBLIC include)

message(STATUS "GLEW cmake done")