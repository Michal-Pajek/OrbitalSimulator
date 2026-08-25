add_library(ui
    ConsoleWriter.cpp
)

target_include_directories(ui PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(ui
    PUBLIC localization
)
