add_library(body_summary
	BodySummary.cpp
)

target_include_directories(body_summary PUBLIC
	${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body_summary PRIVATE
	body
	body_types
	localization_core
	ui
)
