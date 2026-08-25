add_library(scenario_file_format INTERFACE)

target_sources(scenario_file_format INTERFACE
    ScenarioFileFormat.hpp
)

target_include_directories(scenario_file_format INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)
