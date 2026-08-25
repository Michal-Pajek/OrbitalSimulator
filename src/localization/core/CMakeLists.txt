add_library(localization_core INTERFACE)

target_sources(localization_core INTERFACE
    LocalizationTypes.hpp
    TextId.hpp
    TextIdEntries.hpp
)

target_include_directories(localization_core INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)
