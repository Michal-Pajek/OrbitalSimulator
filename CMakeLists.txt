cmake_minimum_required(VERSION 3.20)

project(OrbitalSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(orbital_simulator
    app/main.cpp
    src/app/Application.cpp
    src/simulation/Simulation.cpp
    src/simulation/Body.cpp
    src/math/Vector2D.cpp)

target_include_directories(orbital_simulator PRIVATE
    include   
)