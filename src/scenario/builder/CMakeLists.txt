add_library(scenario_builder
    ScenarioBuilder.cpp
)

target_include_directories(scenario_builder PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_builder
    PUBLIC scenario_core
    PRIVATE scenario_editor
    PRIVATE scenario_input
)
