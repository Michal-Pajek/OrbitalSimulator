target_sources(orbital_tests PRIVATE
	GravityTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	body_test_support
	physics
	physics_gravity
)
