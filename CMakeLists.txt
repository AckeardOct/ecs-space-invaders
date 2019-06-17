cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(space-invaders)

include_directories(lib3dpart)
include_directories(src)

add_subdirectory(src/common)
add_subdirectory(src/components)
add_subdirectory(src/scenes)
add_subdirectory(src/systems)

set(my-libs
    common
    components
    scenes
    systems
)

set(sources
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME}
    ${my-libs}
)
