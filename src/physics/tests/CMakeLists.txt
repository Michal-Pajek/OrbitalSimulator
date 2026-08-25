target_sources(orbital_tests PRIVATE
    PhysicsValidationTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
    math
    physics
)
