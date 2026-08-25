add_library(recording
    Recorder.cpp
)

target_include_directories(recording PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(recording
    PUBLIC body
    PUBLIC simulation_core
    PRIVATE filesystem
    PRIVATE runtime_checks
)
