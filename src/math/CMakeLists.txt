add_library(math
    Vector3D.cpp
)

target_include_directories(math PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(math
    PRIVATE runtime_checks
)

add_subdirectory(tests)
