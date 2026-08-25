add_library(simulation_run_config_builder
    SimulationRunConfigBuilder.cpp
)

target_include_directories(simulation_run_config_builder PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(simulation_run_config_builder
    PUBLIC simulation_run_config
    PRIVATE input_data
    PRIVATE input_selection
    PRIVATE localization_core
    PRIVATE ui
)
