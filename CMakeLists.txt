cmake_minimum_required(VERSION 3.20)

project(OrbitalSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(copy_resources_to_target target_name)
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            $<TARGET_FILE_DIR:${target_name}>/resources
    )
endfunction()

add_executable(orbital_tests)

add_subdirectory(src/common)
add_subdirectory(src/math)
add_subdirectory(src/physics)
add_subdirectory(src/localization)
add_subdirectory(src/filesystem)
add_subdirectory(src/platform)
add_subdirectory(src/ui)
add_subdirectory(src/input/core)
add_subdirectory(src/input/data)
add_subdirectory(src/ui/menu)
add_subdirectory(src/input/selection)
add_subdirectory(src/body)
add_subdirectory(src/simulation)
add_subdirectory(src/recording)
add_subdirectory(src/scenario/core)
add_subdirectory(src/runner)
add_subdirectory(src/scenario/summary)
add_subdirectory(src/scenario/file_format)
add_subdirectory(src/scenario/saver)
add_subdirectory(src/scenario/loader)
add_subdirectory(src/scenario/input)
add_subdirectory(src/scenario/editor)
add_subdirectory(src/scenario/builder)
add_subdirectory(src/scenario/handler)
add_subdirectory(src/app)

add_executable(orbital_simulator
    src/app/main.cpp
)

target_link_libraries(orbital_simulator PRIVATE
    app
    platform
)

copy_resources_to_target(orbital_simulator)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

target_link_libraries(orbital_tests PRIVATE
    GTest::gtest_main
)

copy_resources_to_target(orbital_tests)

include(GoogleTest)

gtest_discover_tests(orbital_tests
    WORKING_DIRECTORY $<TARGET_FILE_DIR:orbital_tests>
)
