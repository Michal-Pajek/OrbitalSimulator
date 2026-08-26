add_library(body_test_support
	TestBodyCreator.cpp
)

target_include_directories(body_test_support PUBLIC
	${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body_test_support PUBLIC
	body
	body_types
	math
)
