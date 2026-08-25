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
    src/bodies/types/BodyTypeCatalog.cpp
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
    src/bodies/Body.cpp
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

add_library(scenario_core INTERFACE)

target_sources(scenario_core INTERFACE
    src/scenario/core/Scenario.hpp
)

target_include_directories(scenario_core INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_core INTERFACE
    body
    runtime_checks
)

add_library(simulation_run_config INTERFACE)

target_sources(simulation_run_config INTERFACE
    src/simulation/run_config/SimulationRunConfig.hpp
)

target_include_directories(simulation_run_config INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(simulation_run_config INTERFACE
    runtime_checks
)

add_library(runner
    src/runner/SimulationRunner.cpp
)

target_include_directories(runner PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(runner PRIVATE
    recording
    runtime_checks
    scenario_core
    simulation_core
    simulation_run_config
)

add_library(scenario_summary
    src/scenario/summary/ScenarioSummary.cpp
)

target_include_directories(scenario_summary PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_summary
    PUBLIC body
    PRIVATE localization_core
    PRIVATE scenario_core
    PRIVATE ui
)

add_library(scenario_file_format INTERFACE)

target_sources(scenario_file_format INTERFACE
    src/scenario/file_format/ScenarioFileFormat.hpp
)

target_include_directories(scenario_file_format INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

add_library(scenario_saver
    src/scenario/saver/ScenarioSaver.cpp
)

target_include_directories(scenario_saver PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_saver PRIVATE
    body
    body_types
    filesystem
    runtime_checks
    scenario_core
    scenario_file_format
)

add_library(ui_menu
    src/ui/menu/Menu.cpp
)

target_include_directories(ui_menu PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(ui_menu
    PUBLIC localization_core
    PRIVATE input_core
    PRIVATE localization
    PRIVATE runtime_checks
    PRIVATE ui
)

add_library(scenario_loader
    src/scenario/loader/ScenarioLoader.cpp
)

target_include_directories(scenario_loader PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_loader
    PUBLIC scenario_core
    PRIVATE body
    PRIVATE body_types
    PRIVATE filesystem
    PRIVATE input_data
    PRIVATE localization_core
    PRIVATE math
    PRIVATE scenario_file_format
    PRIVATE ui
    PRIVATE ui_menu
)

add_library(input_selection
    src/input/selection/BodyMassUnitSelector.cpp
)

target_include_directories(input_selection PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(input_selection
    PUBLIC body_types
    PUBLIC localization_core
    PUBLIC runtime_checks
    PUBLIC ui
    PUBLIC ui_menu
    PRIVATE physics
)

add_library(simulation_run_config_builder
    src/simulation/run_config/builder/SimulationRunConfigBuilder.cpp
)

target_include_directories(simulation_run_config_builder PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(simulation_run_config_builder
    PUBLIC simulation_run_config
    PRIVATE input_data
    PRIVATE input_selection
    PRIVATE localization_core
    PRIVATE ui
)

add_library(body_input
    src/bodies/input/BodyBuilder.cpp
    src/bodies/input/BodyEditor.cpp
    src/bodies/input/BodyInputBase.cpp
)

target_include_directories(body_input PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(body_input
    PUBLIC body
    PUBLIC body_types
    PUBLIC math
    PRIVATE input_core
    PRIVATE input_data
    PRIVATE input_selection
    PRIVATE localization_core
    PRIVATE physics
    PRIVATE ui
    PRIVATE ui_menu
)

add_library(scenario_input
    src/scenario/input/ScenarioInput.cpp
)

target_include_directories(scenario_input PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_input
    PUBLIC body
    PRIVATE body_input
    PRIVATE input_data
    PRIVATE localization_core
    PRIVATE scenario_core
    PRIVATE ui
)

add_library(scenario_editor
    src/scenario/editor/ScenarioEditor.cpp
)

target_include_directories(scenario_editor PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_editor
    PUBLIC scenario_core
    PRIVATE body_input
    PRIVATE input_core
    PRIVATE input_data
    PRIVATE localization_core
    PRIVATE runtime_checks
    PRIVATE scenario_input
    PRIVATE scenario_summary
    PRIVATE ui
    PRIVATE ui_menu
)

add_library(scenario_builder
    src/scenario/builder/ScenarioBuilder.cpp
)

target_include_directories(scenario_builder PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_builder
    PUBLIC scenario_core
    PRIVATE scenario_editor
    PRIVATE scenario_input
)

add_library(scenario_handler
    src/scenario/handler/ScenarioHandler.cpp
)

target_include_directories(scenario_handler PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(scenario_handler PRIVATE
    input_data
    localization_core
    scenario_builder
    scenario_core
    scenario_loader
    scenario_saver
    scenario_summary
    simulation_run_config_builder
    recording
    runner
    runtime_checks
    ui
    ui_menu
)

add_library(app
    src/app/Application.cpp
    src/app/ExceptionHandler.cpp
)

target_include_directories(app PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(app
    PUBLIC localization_core
    PRIVATE input_core
    PRIVATE localization
    PRIVATE scenario_handler
    PRIVATE ui
    PRIVATE ui_menu
)

add_executable(orbital_simulator
    src/app/main.cpp
)

target_include_directories(orbital_simulator PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(orbital_simulator PRIVATE
    app
    body
    body_input
    body_types
    platform
    filesystem
    input_core
    input_data
    input_selection
    localization
    math
    physics
    recording
    runner
    runtime_checks
    scenario_builder
    scenario_core
    scenario_editor
    scenario_handler
    scenario_input
    scenario_loader
    scenario_saver
    scenario_summary
    simulation_core
    simulation_run_config
    simulation_run_config_builder
    ui
    ui_menu
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
    src/bodies/tests/BodyTests.cpp
    src/bodies/tests/support/TestBodyCreator.cpp
    src/bodies/types/tests/BodyTypeCatalogTests.cpp
    src/bodies/types/tests/BodyTypesTests.cpp
    src/common/tests/RuntimeChecksTests.cpp
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

target_include_directories(orbital_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src
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
