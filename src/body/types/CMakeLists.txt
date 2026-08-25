add_library(body_types
    BodyTypeCatalog.cpp
)

target_include_directories(body_types PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body_types
    PUBLIC localization_core
    PRIVATE physics
    PRIVATE runtime_checks
)

add_subdirectory(tests)
