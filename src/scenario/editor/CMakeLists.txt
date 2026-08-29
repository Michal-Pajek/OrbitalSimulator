add_library(scenario_editor
    ScenarioEditor.cpp
)

target_include_directories(scenario_editor PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_editor
    PUBLIC scenario_core
    PRIVATE body_input
    PRIVATE body_summary
    PRIVATE input_core
    PRIVATE input_data
    PRIVATE localization_core
    PRIVATE runtime_checks
    PRIVATE scenario_input
    PRIVATE scenario_summary
    PRIVATE ui
    PRIVATE ui_menu
)
