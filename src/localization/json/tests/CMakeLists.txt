target_sources(orbital_tests PRIVATE
	JsonLanguageSettingsParserTests.cpp
	JsonLocalizationParserTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	localization_json
)
