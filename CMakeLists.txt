cmake_minimum_required(VERSION 3.16)

project(SceneRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tests are off by default: cmake -S . -B build -DBUILD_TESTING=ON
option(BUILD_TESTING "Build unit tests" OFF)
include(CTest)

find_package(raylib REQUIRED)
find_package(Curses REQUIRED)

# Shared code: used by both the app and the tests
add_library(core STATIC
    src/vector.cpp
    src/geometry.cpp
    src/renderer.cpp
)

target_include_directories(core PUBLIC
    include
    ${CURSES_INCLUDE_DIRS}
)

target_link_libraries(core PUBLIC
    raylib
    ${CURSES_LIBRARIES}
)

# The application
add_executable(renderer
    src/main.cpp
    src/command.cpp
    src/terminal.cpp
)

target_link_libraries(renderer PRIVATE core)

if(NOT MSVC)
    target_compile_options(core PRIVATE -Wall -Wextra)
    target_compile_options(renderer PRIVATE -Wall -Wextra)
endif()

# Unit tests
if(BUILD_TESTING)

    if(POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
    endif()

    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(unit_tests
        tests/vector_tests.cpp
        tests/geometry_tests.cpp
        tests/renderer_tests.cpp
    )

    target_link_libraries(unit_tests PRIVATE
        core
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(unit_tests)

endif()