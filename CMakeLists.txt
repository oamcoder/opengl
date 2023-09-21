cmake_minimum_required(VERSION 3.4...3.20)
project(opengl)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif ()

include_directories(include)
aux_source_directory(src SRC_LIST)

add_subdirectory(lib/glfw)

add_executable(${PROJECT_NAME}
        lib/glad/glad.c
        ${SRC_LIST}
)

target_link_libraries(${PROJECT_NAME} glfw)
