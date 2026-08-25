add_library(platform
    ConsoleEncoding.cpp
)

target_include_directories(platform PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)
