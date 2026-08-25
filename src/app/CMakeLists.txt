add_library(app
    Application.cpp
    ExceptionHandler.cpp
)

target_include_directories(app PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(app
    PUBLIC localization_core
    PRIVATE input_core
    PRIVATE localization
    PRIVATE scenario_handler
    PRIVATE ui
    PRIVATE ui_menu
)

add_subdirectory(tests)
