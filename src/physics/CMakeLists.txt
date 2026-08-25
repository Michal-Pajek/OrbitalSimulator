add_library(physics
    Validation.cpp
)

target_include_directories(physics PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(physics
    PUBLIC math
)
