add_subdirectory(support)

target_sources(orbital_tests PRIVATE
	BodyTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	body
	body_test_support
	body_types
	math
	physics
)
