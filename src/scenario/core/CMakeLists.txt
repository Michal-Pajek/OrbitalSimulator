add_library(scenario_core INTERFACE)

target_sources(scenario_core INTERFACE
    Scenario.hpp
)

target_include_directories(scenario_core INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_core INTERFACE
    body
    runtime_checks
)
