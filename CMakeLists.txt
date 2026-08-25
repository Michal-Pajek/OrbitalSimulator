cmake_minimum_required(VERSION 3.20)

project(OrbitalSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(copy_resources_to_target target_name)
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            $<TARGET_FILE_DIR:${target_name}>/resources
    )
endfunction()

add_subdirectory(src/common)
add_subdirectory(src/math)
add_subdirectory(src/physics)
add_subdirectory(src/localization)
add_subdirectory(src/filesystem)
add_subdirectory(src/platform)
add_subdirectory(src/ui)
add_subdirectory(src/input/core)
add_subdirectory(src/input/data)
add_subdirectory(src/ui/menu)
add_subdirectory(src/input/selection)
add_subdirectory(src/body)
add_subdirectory(src/simulation)
add_subdirectory(src/recording)
add_subdirectory(src/scenario/core)
add_subdirectory(src/runner)
add_subdirectory(src/scenario/summary)
add_subdirectory(src/scenario/file_format)
add_subdirectory(src/scenario/saver)
add_subdirectory(src/scenario/loader)
add_subdirectory(src/scenario/input)
add_subdirectory(src/scenario/editor)
add_subdirectory(src/scenario/builder)
add_subdirectory(src/scenario/handler)
add_subdirectory(src/app)

add_executable(orbital_simulator
    src/app/main.cpp
)

target_link_libraries(orbital_simulator PRIVATE
    app
    platform
)

copy_resources_to_target(orbital_simulator)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(orbital_tests
    src/app/tests/ExceptionHandlerTests.cpp
    src/body/tests/BodyTests.cpp
    src/body/tests/support/TestBodyCreator.cpp
    src/body/types/tests/BodyTypeCatalogTests.cpp
    src/body/types/tests/BodyTypesTests.cpp
    src/common/runtime_checks/tests/RuntimeChecksTests.cpp
    src/filesystem/tests/FileNameValidationTests.cpp
    src/localization/json/tests/JsonLanguageSettingsParserTests.cpp
    src/localization/json/tests/JsonLocalizationParserTests.cpp
    src/localization/tests/LocalizationResourcesTests.cpp
    src/localization/tests/LocalizationTests.cpp
    src/math/tests/Vector3DTests.cpp
    src/physics/tests/PhysicsValidationTests.cpp
    src/scenario/core/tests/ScenarioTests.cpp
    src/simulation/core/tests/SimulationsTests.cpp
    src/ui/menu/tests/MenuTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
    app
    body
    body_types
    filesystem
    localization
    localization_json
    input_core
    math
    physics
    runtime_checks
    scenario_core
    simulation_core
    ui
    ui_menu
    GTest::gtest_main
)

copy_resources_to_target(orbital_tests)

include(GoogleTest)

gtest_discover_tests(orbital_tests
    WORKING_DIRECTORY $<TARGET_FILE_DIR:orbital_tests>
)
