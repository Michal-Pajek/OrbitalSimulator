add_library(scenario_handler
    ScenarioHandler.cpp
)

target_include_directories(scenario_handler PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_handler PRIVATE
    input_data
    localization_core
    scenario_builder
    scenario_core
    scenario_loader
    scenario_saver
    scenario_summary
    simulation_run_config_builder
    recording
    runner
    runtime_checks
    ui
    ui_menu
)
