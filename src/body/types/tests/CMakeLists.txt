target_sources(orbital_tests PRIVATE
	BodyTypeCatalogTests.cpp
	BodyTypesTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	body_types
)
