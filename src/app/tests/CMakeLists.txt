target_sources(orbital_tests PRIVATE
	ExceptionHandlerTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
	app
)
