cmake_minimum_required(VERSION 3.4...3.20)
project(opengl)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
elseif (APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif ()

include_directories(include)
aux_source_directory(src SRC_LIST)

add_subdirectory(lib/glfw)

add_executable(${PROJECT_NAME}
        lib/glad/glad.c
        ${SRC_LIST}
)

target_link_libraries(${PROJECT_NAME} glfw)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory ${PROJECT_SOURCE_DIR}/res/shader ${EXECUTABLE_OUTPUT_PATH}/res/shader
)
