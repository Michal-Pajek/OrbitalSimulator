add_library(physics_gravity
	Gravity.cpp
)

target_include_directories(physics_gravity PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(physics_gravity
    PUBLIC math
    PRIVATE body
    PRIVATE physics
    PRIVATE runtime_checks
)

add_subdirectory(tests)
