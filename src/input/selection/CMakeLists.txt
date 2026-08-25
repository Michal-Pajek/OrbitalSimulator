add_library(input_selection INTERFACE)

target_sources(input_selection INTERFACE
    OptionSelector.hpp
)

target_include_directories(input_selection INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(input_selection INTERFACE
    localization_core
    runtime_checks
    ui
    ui_menu
)
