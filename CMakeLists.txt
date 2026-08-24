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

add_library(runtime_checks
    src/common/RuntimeChecks.cpp
)

target_include_directories(runtime_checks PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

add_library(localization_core INTERFACE)

target_sources(localization_core INTERFACE
    src/localization/core/LocalizationTypes.hpp
    src/localization/core/TextId.hpp
    src/localization/core/TextIdEntries.hpp
)

target_include_directories(localization_core INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

add_library(localization_json
    src/localization/json/JsonDataStorage.cpp
    src/localization/json/JsonLanguageSettingsParser.cpp
    src/localization/json/JsonLocalizationParser.cpp
    src/localization/json/JsonParserBase.cpp
)

target_include_directories(localization_json PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(localization_json
    PUBLIC localization_core
    PRIVATE runtime_checks
)

add_library(math
    src/math/Vector3D.cpp
)

target_include_directories(math PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(math
    PRIVATE runtime_checks
)

add_library(physics
    src/physics/Validation.cpp
)

target_include_directories(physics PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(physics
    PUBLIC math
)

add_library(localization
    src/localization/LocalizationManager.cpp
)

target_include_directories(localization PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(localization
    PUBLIC localization_core
    PRIVATE localization_json
)

add_library(filesystem
    src/filesystem/ApplicationPaths.cpp
    src/filesystem/FileNameValidation.cpp
)

target_include_directories(filesystem PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(filesystem
    PRIVATE runtime_checks
)

add_library(platform
    src/platform/ConsoleEncoding.cpp
)

target_include_directories(platform PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

add_library(ui
    src/ui/ConsoleWriter.cpp
)

target_include_directories(ui PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(ui
    PUBLIC localization
)

add_library(body_types
    src/simulation/bodies/types/BodyTypeCatalog.cpp
)

target_include_directories(body_types PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body_types
    PUBLIC localization_core
    PRIVATE physics
    PRIVATE runtime_checks
)

add_library(body
    src/simulation/bodies/Body.cpp
)

target_include_directories(body PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body
    PUBLIC body_types
    PUBLIC math
    PRIVATE localization_core
    PRIVATE physics
    PRIVATE runtime_checks
    PRIVATE ui
)

add_library(input_core
    src/input/core/Console.cpp
    src/input/core/Keyboard.cpp
)

target_include_directories(input_core PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(input_core
    PRIVATE runtime_checks
)

add_library(simulation_core
    src/simulation/core/BodyStepState.cpp
    src/simulation/core/Simulation.cpp
)

target_include_directories(simulation_core PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(simulation_core
    PUBLIC body
    PUBLIC math
    PRIVATE physics
    PRIVATE runtime_checks
)

add_library(recording
    src/recording/Recorder.cpp
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

add_library(input_data
    src/input/data/DataGetter.cpp
)

target_include_directories(input_data PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(input_data
    PUBLIC localization_core
    PUBLIC math
    PUBLIC ui
    PRIVATE filesystem
)

add_executable(orbital_simulator
    src/app/Application.cpp
    src/app/ExceptionHandler.cpp
    src/app/main.cpp
    src/app/Menu.cpp
    src/input/BodyMassUnitSelector.cpp
    src/runner/SimulationRunner.cpp
    src/scenario/ScenarioBuilder.cpp
    src/scenario/ScenarioEditor.cpp
    src/scenario/ScenarioHandler.cpp
    src/scenario/ScenarioInput.cpp
    src/scenario/ScenarioLoader.cpp
    src/scenario/ScenarioSaver.cpp
    src/scenario/ScenarioSummary.cpp
    src/simulation/bodies/BodyBuilder.cpp
    src/simulation/bodies/BodyInputBase.cpp
    src/simulation/bodies/BodyEditor.cpp
    src/simulation/SimulationRunConfigBuilder.cpp
)

target_include_directories(orbital_simulator PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(orbital_simulator PRIVATE
    body
    body_types
    platform
    filesystem
    input_core
    input_data
    localization
    math
    physics
    recording
    runtime_checks
    simulation_core
    ui
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
    src/app/ExceptionHandler.cpp
    src/app/Menu.cpp

    src/simulation/bodies/tests/BodyTests.cpp
    src/simulation/bodies/types/tests/BodyTypeCatalogTests.cpp
    src/simulation/bodies/types/tests/BodyTypesTests.cpp
    src/app/tests/ExceptionHandlerTests.cpp
    src/filesystem/tests/FileNameValidationTests.cpp
    src/localization/json/tests/JsonLanguageSettingsParserTests.cpp
    src/localization/json/tests/JsonLocalizationParserTests.cpp
    src/localization/tests/LocalizationResourcesTests.cpp
    src/localization/tests/LocalizationTests.cpp
    src/app/tests/MenuTests.cpp
    src/physics/tests/PhysicsValidationTests.cpp
    src/common/tests/RuntimeChecksTests.cpp
    src/scenario/tests/ScenarioTests.cpp
    src/simulation/core/tests/SimulationsTests.cpp
    src/math/tests/Vector3DTests.cpp
    src/simulation/bodies/tests/support/TestBodyCreator.cpp
)

target_include_directories(orbital_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(orbital_tests PRIVATE
    body
    body_types
    filesystem
    localization
    localization_json
    input_core
    math
    physics
    runtime_checks
    simulation_core
    ui
    GTest::gtest_main
)

copy_resources_to_target(orbital_tests)

include(GoogleTest)

gtest_discover_tests(orbital_tests
    WORKING_DIRECTORY $<TARGET_FILE_DIR:orbital_tests>
)
