cmake_minimum_required(VERSION 3.20)

project(OrbitalSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(orbital_simulator
    app/main.cpp
    src/app/Application.cpp
    src/app/Menu.cpp
    src/input/Console.cpp
    src/input/Keyboard.cpp
    src/math/Vector2D.cpp
    src/scenario/Scenario.cpp
    src/simulation/Body.cpp
    src/simulation/BodyStepState.cpp
    src/simulation/Simulation.cpp)

target_include_directories(orbital_simulator PRIVATE
    include   
)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(orbital_tests
    src/simulation/Body.cpp
    src/simulation/BodyStepState.cpp
    src/simulation/Simulation.cpp
    src/math/Vector2D.cpp
    tests/BodyTests.cpp
    tests/SimulationsTests.cpp
    tests/Vector2DTests.cpp "src/input/Console.cpp")

target_include_directories(orbital_tests PRIVATE
    include
)

target_link_libraries(orbital_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(orbital_tests)