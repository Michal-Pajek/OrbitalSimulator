add_library(input_core
    Console.cpp
    Keyboard.cpp
)

target_include_directories(input_core PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(input_core
    PRIVATE runtime_checks
)
