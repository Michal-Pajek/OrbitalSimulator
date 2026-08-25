add_library(runner
    SimulationRunner.cpp
)

target_include_directories(runner PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(runner PRIVATE
    recording
    runtime_checks
    scenario_core
    simulation_core
    simulation_run_config
)
