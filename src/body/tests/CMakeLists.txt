target_sources(orbital_tests PRIVATE
	BodyTests.cpp
	support/TestBodyCreator.cpp
)

target_link_libraries(orbital_tests PRIVATE
	body
	body_types
	math
	physics
)
