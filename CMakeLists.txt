cmake_minimum_required(VERSION 3.16)

project(SceneRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)
find_package(Curses REQUIRED)

add_executable(renderer
    src/main.cpp
    src/command.cpp
    src/geometry.cpp
    src/renderer.cpp
    src/vector.cpp
    src/terminal.cpp
)

target_include_directories(renderer PRIVATE include ${CURSES_INCLUDE_DIR})
target_link_libraries(renderer PRIVATE raylib ${CURSES_LIBRARIES})