target_sources(orbital_tests PRIVATE
    SimulationsTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
    body
    math
    simulation_core
)
