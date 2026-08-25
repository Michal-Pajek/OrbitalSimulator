target_sources(orbital_tests PRIVATE
    ScenarioTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
    body
    scenario_core
)
