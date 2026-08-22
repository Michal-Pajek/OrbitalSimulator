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

add_executable(orbital_simulator
    src/app/Application.cpp
    src/app/ExceptionHandler.cpp
    src/app/main.cpp
    src/app/Menu.cpp
    src/filesystem/ApplicationPaths.cpp
    src/filesystem/FileNameValidation.cpp
    src/input/BodyMassUnitSelector.cpp
    src/input/Console.cpp
    src/input/DataGetter.cpp
    src/input/Keyboard.cpp
    src/localization/LocalizationManager.cpp
    src/platform/ConsoleEncoding.cpp
    src/recording/Recorder.cpp
    src/runner/SimulationRunner.cpp
    src/scenario/ScenarioBuilder.cpp
    src/scenario/ScenarioEditor.cpp
    src/scenario/ScenarioHandler.cpp
    src/scenario/ScenarioInput.cpp
    src/scenario/ScenarioLoader.cpp
    src/scenario/ScenarioSaver.cpp
    src/scenario/ScenarioSummary.cpp
    src/simulation/bodies/Body.cpp
    src/simulation/bodies/BodyBuilder.cpp
    src/simulation/bodies/BodyInputBase.cpp
    src/simulation/bodies/BodyEditor.cpp
    src/simulation/bodies/BodyStepState.cpp
    src/simulation/bodies/types/BodyTypeCatalog.cpp
    src/simulation/Simulation.cpp
    src/simulation/SimulationRunConfigBuilder.cpp
    src/ui/ConsoleWriter.cpp
)

target_include_directories(orbital_simulator PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(orbital_simulator PRIVATE
    localization_json
    math
    physics
    runtime_checks
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
    src/filesystem/FileNameValidation.cpp
    src/input/Keyboard.cpp
    src/localization/LocalizationManager.cpp
    src/simulation/bodies/Body.cpp
    src/simulation/bodies/BodyStepState.cpp
    src/simulation/bodies/types/BodyTypeCatalog.cpp
    src/simulation/Simulation.cpp
    src/ui/ConsoleWriter.cpp

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
    src/simulation/tests/SimulationsTests.cpp
    src/math/tests/Vector3DTests.cpp
    src/simulation/bodies/tests/support/TestBodyCreator.cpp
)

target_include_directories(orbital_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(orbital_tests PRIVATE
    localization_json
    math
    physics
    runtime_checks
    GTest::gtest_main
)

copy_resources_to_target(orbital_tests)

include(GoogleTest)

gtest_discover_tests(orbital_tests
    WORKING_DIRECTORY $<TARGET_FILE_DIR:orbital_tests>
)
