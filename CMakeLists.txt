cmake_minimum_required(VERSION 3.20)

project(OrbitalSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(orbital_simulator
    app/main.cpp
    src/app/Application.cpp
    src/app/Menu.cpp
    src/input/BodyMassUnitSelector.cpp
    src/input/Console.cpp
    src/input/DataGetter.cpp
    src/input/jsons/JsonLocalizationLoader.cpp
    src/input/jsons/JsonLocalizationParser.cpp
    src/input/jsons/JsonParserBase.cpp
    src/input/jsons/JsonSettingsParser.cpp
    src/input/Keyboard.cpp
    src/localization/LocalizationManager.cpp
    src/math/Vector3D.cpp
    src/platform/ConsoleEncoding.cpp
    src/recording/Recorder.cpp
    src/runner/SimulationRunner.cpp
    src/scenario/ScenarioBuilder.cpp
    src/simulation/bodies/Body.cpp
    src/simulation/bodies/BodyBuilder.cpp
    src/simulation/bodies/BodyInputBase.cpp
    src/simulation/bodies/BodyEditor.cpp
    src/simulation/bodies/BodyStepState.cpp
    src/simulation/bodies/types/BodyTypeCatalog.cpp
    src/simulation/Simulation.cpp
    src/ui/ConsoleWriter.cpp
)

add_custom_command(TARGET orbital_simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:orbital_simulator>/resources
)

target_include_directories(orbital_simulator PRIVATE
    include
)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(orbital_tests
    src/input/jsons/JsonLocalizationLoader.cpp
    src/input/jsons/JsonLocalizationParser.cpp
    src/input/jsons/JsonParserBase.cpp
    src/localization/LocalizationManager.cpp
    src/math/Vector3D.cpp
    src/simulation/bodies/Body.cpp
    src/simulation/bodies/BodyStepState.cpp
    src/simulation/bodies/types/BodyTypeCatalog.cpp
    src/simulation/Simulation.cpp
    src/ui/ConsoleWriter.cpp
    tests/BodyTests.cpp
    tests/BodyTypesTests.cpp
    tests/JsonLocalizationParserTests.cpp
    tests/LocalizationResourcesTests.cpp
    tests/LocalizationTests.cpp
    tests/SimulationsTests.cpp
)

add_custom_command(TARGET orbital_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:orbital_tests>/resources
)

target_include_directories(orbital_tests PRIVATE
    include
)

target_link_libraries(orbital_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(orbital_tests)
