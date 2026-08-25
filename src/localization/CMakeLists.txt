add_library(localization
    LocalizationManager.cpp
)

target_include_directories(localization PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(localization
    PUBLIC localization_core
    PRIVATE localization_json
)
