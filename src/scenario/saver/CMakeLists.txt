add_library(scenario_saver
    ScenarioSaver.cpp
)

target_include_directories(scenario_saver PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_saver PRIVATE
    body
    body_types
    filesystem
    runtime_checks
    scenario_core
    scenario_file_format
)
