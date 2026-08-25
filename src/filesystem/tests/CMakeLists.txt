target_sources(orbital_tests PRIVATE
	FileNameValidationTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	filesystem
)
