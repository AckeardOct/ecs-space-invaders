cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(systems)

set(sources
    basic.cpp
    render.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME}
    SDL2
    SDL2_image
    common
)
