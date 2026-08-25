add_library(simulation_run_config INTERFACE)

target_sources(simulation_run_config INTERFACE
    SimulationRunConfig.hpp
)

target_include_directories(simulation_run_config INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(simulation_run_config INTERFACE
    runtime_checks
)
