target_sources(orbital_tests PRIVATE
	LocalizationResourcesTests.cpp
	LocalizationTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	localization
	localization_json
)
