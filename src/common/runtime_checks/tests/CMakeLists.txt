target_sources(orbital_tests PRIVATE
    RuntimeChecksTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
    runtime_checks
)
