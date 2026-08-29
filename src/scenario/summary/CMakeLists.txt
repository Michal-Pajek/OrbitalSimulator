add_library(scenario_summary
    ScenarioSummary.cpp
)

target_include_directories(scenario_summary PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_summary
    PUBLIC body
    PRIVATE body_summary
    PRIVATE localization_core
    PRIVATE scenario_core
    PRIVATE ui
)
