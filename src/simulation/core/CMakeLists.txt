add_library(simulation_core
    BodyStepState.cpp
    Simulation.cpp
)

target_include_directories(simulation_core PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(simulation_core
    PUBLIC body
    PUBLIC math
    PRIVATE physics
    PRIVATE physics_gravity
    PRIVATE runtime_checks
)

add_subdirectory(tests)
