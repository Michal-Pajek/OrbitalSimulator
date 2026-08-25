add_library(scenario_input
    ScenarioInput.cpp
)

target_include_directories(scenario_input PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_input
    PUBLIC body
    PRIVATE body_input
    PRIVATE input_data
    PRIVATE localization_core
    PRIVATE scenario_core
    PRIVATE ui
)
