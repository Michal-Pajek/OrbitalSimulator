add_library(body_input
    BodyBuilder.cpp
    BodyEditor.cpp
    BodyInputBase.cpp
    BodyMassUnitSelector.cpp
)

target_include_directories(body_input PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body_input
    PUBLIC body
    PUBLIC body_types
    PUBLIC input_selection
    PUBLIC math
    PRIVATE input_core
    PRIVATE input_data
    PRIVATE localization_core
    PRIVATE physics
    PRIVATE ui
    PRIVATE ui_menu
)
