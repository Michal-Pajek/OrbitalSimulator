add_library(runtime_checks
    RuntimeChecks.cpp
)

target_include_directories(runtime_checks PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(tests)
