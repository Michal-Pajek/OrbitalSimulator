add_library(filesystem
    ApplicationPaths.cpp
    FileNameValidation.cpp
)

target_include_directories(filesystem PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(filesystem
    PRIVATE runtime_checks
)
