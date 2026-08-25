add_library(input_data
    DataGetter.cpp
)

target_include_directories(input_data PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(input_data
    PUBLIC localization_core
    PUBLIC math
    PUBLIC ui
    PRIVATE filesystem
)
