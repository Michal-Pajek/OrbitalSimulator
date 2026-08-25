add_library(localization_json
    JsonDataStorage.cpp
    JsonLanguageSettingsParser.cpp
    JsonLocalizationParser.cpp
    JsonParserBase.cpp
)

target_include_directories(localization_json PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(localization_json
    PUBLIC localization_core
    PRIVATE runtime_checks
)

add_subdirectory(tests)
