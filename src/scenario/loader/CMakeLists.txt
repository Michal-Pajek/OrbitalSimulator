add_library(scenario_loader
    ScenarioLoader.cpp
)

target_include_directories(scenario_loader PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_loader
    PUBLIC scenario_core
    PRIVATE body
    PRIVATE body_types
    PRIVATE filesystem
    PRIVATE input_data
    PRIVATE localization_core
    PRIVATE math
    PRIVATE scenario_file_format
    PRIVATE ui
    PRIVATE ui_menu
)
