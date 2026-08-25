add_library(ui_menu
    Menu.cpp
)

target_include_directories(ui_menu PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(ui_menu
    PUBLIC localization_core
    PRIVATE input_core
    PRIVATE localization
    PRIVATE runtime_checks
    PRIVATE ui
)
