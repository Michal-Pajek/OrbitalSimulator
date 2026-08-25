target_sources(orbital_tests PRIVATE
	Vector3DTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	math
)
