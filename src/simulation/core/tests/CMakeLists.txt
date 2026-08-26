target_sources(orbital_tests PRIVATE
    SimulationsTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
    body
    body_test_support
    math
    simulation_core
)
