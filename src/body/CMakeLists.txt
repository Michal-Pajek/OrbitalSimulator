add_subdirectory(types)

add_library(body
    Body.cpp
)

target_include_directories(body PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body
    PUBLIC body_types
    PUBLIC math
    PRIVATE localization_core
    PRIVATE physics
    PRIVATE runtime_checks
    PRIVATE ui
)

add_subdirectory(input)
add_subdirectory(tests)
