#pragma once
#include <array>
#include <cstddef>
#include <string_view>
#include "TextId.hpp"

namespace TextIdEntries
{
    struct TextIdEntry
    {
        TextId id;
        std::string_view key;
    };

    inline constexpr std::array<TextIdEntry, TEXT_ID_COUNT> textIdEntries{ {
        TextIdEntry{ TextId::Accept,                                        "accept" },
        TextIdEntry{ TextId::AddBody,                                       "add_body" },
        TextIdEntry{ TextId::ApplicationFinished,                           "application_finished" },
        TextIdEntry{ TextId::Asteroid,                                      "asteroid" },
        TextIdEntry{ TextId::AstronomicalUnit,                              "astronomical_unit" },
        TextIdEntry{ TextId::AverageEarthToMoonDistance,                    "average_earth_to_moon_distance" },
        TextIdEntry{ TextId::Back,                                          "back" },
        TextIdEntry{ TextId::Bodies,                                        "bodies" },
        TextIdEntry{ TextId::BodyDeleted,                                   "body_deleted" },
        TextIdEntry{ TextId::BodyMass,                                      "body_mass" },
        TextIdEntry{ TextId::BodyMassOutOfInterval,                         "body_mass_out_of_interval" },
        TextIdEntry{ TextId::BodyName,                                      "body_name" },
        TextIdEntry{ TextId::BodyNameAlreadyUsedEnterAnother,               "body_name_already_used_enter_another" },
        TextIdEntry{ TextId::BodyPosition,                                  "body_position" },
        TextIdEntry{ TextId::BodyPositionAlreadyOccupiedEnterAnother,       "body_position_already_occupied_enter_another" },
        TextIdEntry{ TextId::BodyType,                                      "body_type" },
        TextIdEntry{ TextId::BodyVelocity,                                  "body_velocity" },
        TextIdEntry{ TextId::BrownDwarf,                                    "brown_dwarf" },
        TextIdEntry{ TextId::Cancel,                                        "cancel" },
        TextIdEntry{ TextId::Comet,                                         "comet" },
        TextIdEntry{ TextId::ConfirmBody,                                   "confirm_body" },
        TextIdEntry{ TextId::CurrentBodiesList,                             "current_bodies_list" },
        TextIdEntry{ TextId::CurrentBodyMassIsWithinTheRangeForThisType,    "current_body_mass_is_within_the_range_for_this_type" },
        TextIdEntry{ TextId::CurrentScenarioSummary,                        "current_scenario_summary" },
        TextIdEntry{ TextId::Day,                                           "day" },
        TextIdEntry{ TextId::DeleteBody,                                    "delete_body" },
        TextIdEntry{ TextId::DwarfPlanet,                                   "dwarf_planet" },
        TextIdEntry{ TextId::EarthMass,                                     "earth_mass" },
        TextIdEntry{ TextId::EditBody,                                      "edit_body" },
        TextIdEntry{ TextId::English,                                       "english" },
        TextIdEntry{ TextId::EnterBodyMass,                                 "enter_body_mass" },
        TextIdEntry{ TextId::EnterBodyNumber,                               "enter_body_number" },
        TextIdEntry{ TextId::EnterDifferentValue,                           "enter_different_value" },
        TextIdEntry{ TextId::EnterNewBodyData,                              "enter_new_body_data" },
        TextIdEntry{ TextId::EnterObjectCountNotGreaterThan,                "enter_object_count_not_greater_than" },
        TextIdEntry{ TextId::EnterOneWordName,                              "enter_one_word_name" },
        TextIdEntry{ TextId::EnterPositionVector,                           "enter_position_vector" },
        TextIdEntry{ TextId::EnterScenarioName,                             "enter_scenario_name" },
        TextIdEntry{ TextId::EnterStepCount,                                "enter_step_count" },
        TextIdEntry{ TextId::EnterTimeStep,                                 "enter_time_step" },
        TextIdEntry{ TextId::EnterVelocityVector,                           "enter_velocity_vector" },
        TextIdEntry{ TextId::Exit,                                          "exit" },
        TextIdEntry{ TextId::Hour,                                          "hour" },
        TextIdEntry{ TextId::Interval,                                      "interval" },
        TextIdEntry{ TextId::JupiterMass,                                   "jupiter_mass" },
        TextIdEntry{ TextId::Kilogram,                                      "kilogram" },
        TextIdEntry{ TextId::Kilometre,                                     "kilometre" },
        TextIdEntry{ TextId::KilometrePerSecond,                            "kilometre_per_second" },
        TextIdEntry{ TextId::Kiloton,                                       "kiloton" },
        TextIdEntry{ TextId::MainMenu,                                      "main_menu" },
        TextIdEntry{ TextId::Mass,                                          "mass" },
        TextIdEntry{ TextId::Megaton,                                       "megaton" },
        TextIdEntry{ TextId::Meteor,                                        "meteor" },
        TextIdEntry{ TextId::Metre,                                         "metre" },
        TextIdEntry{ TextId::MetrePerSecond,                                "metre_per_second" },
        TextIdEntry{ TextId::MillionKilometre,                              "million_kilometre" },
        TextIdEntry{ TextId::Minute,                                        "minute" },
        TextIdEntry{ TextId::Moon,                                          "moon" },
        TextIdEntry{ TextId::MoonMass,                                      "moon_mass" },
        TextIdEntry{ TextId::NotImplemented,                                "not_implemented" },
        TextIdEntry{ TextId::ObjectCount,                                   "object_count" },
        TextIdEntry{ TextId::Planet,                                        "planet" },
        TextIdEntry{ TextId::Polish,                                        "polish" },
        TextIdEntry{ TextId::Position,                                      "position" },
        TextIdEntry{ TextId::PositiveNumber,                                "positive_number" },
        TextIdEntry{ TextId::PressAnyKeyToContinue,                         "press_any_key_to_continue" },
        TextIdEntry{ TextId::PressAnyKeyToReturnToMainMenu,                 "press_any_key_to_return_to_main_menu" },
        TextIdEntry{ TextId::QuestionDoYouStillWantToEnterNewValue,         "question_do_you_still_want_to_enter_new_value" },
        TextIdEntry{ TextId::QuestionDoYouWantToAccept,                     "question_do_you_want_to_accept" },
        TextIdEntry{ TextId::QuestionDoYouWantToFinish,                     "question_do_you_want_to_finish" },
        TextIdEntry{ TextId::QuestionDoYouWantToRunTheSimulationNow,        "question_do_you_want_to_run_the_simulation_now" },
        TextIdEntry{ TextId::QuestionDoYouWantToSaveThisScenario,           "question_do_you_want_to_save_this_scenario" },
        TextIdEntry{ TextId::QuestionWhatDoYouWantToChange,                 "question_what_do_you_want_to_change" },
        TextIdEntry{ TextId::QuestionWhatDoYouWantToChangeInBody,           "question_what_do_you_want_to_change_in_body" },
        TextIdEntry{ TextId::QuestionWhatDoYouWantToDo,                     "question_what_do_you_want_to_do" },
        TextIdEntry{ TextId::QuestionWhatDoYouWantToDoWithBodies,           "question_what_do_you_want_to_do_with_bodies" },
        TextIdEntry{ TextId::Revise,                                        "revise" },
        TextIdEntry{ TextId::RunTestScenario,                               "run_test_scenario" },
        TextIdEntry{ TextId::ScenarioBuilder,                               "scenario_builder" },
        TextIdEntry{ TextId::ScenarioCreatedSuccessfully,                   "scenario_created_successfully" },
        TextIdEntry{ TextId::ScenarioCreationCanceled,                      "scenario_creation_canceled" },
        TextIdEntry{ TextId::ScenarioMustHaveAtLeastOneBody,                "scenario_must_have_at_least_one_body" },
        TextIdEntry{ TextId::ScenarioName,                                  "scenario_name" },
        TextIdEntry{ TextId::Second,                                        "second" },
        TextIdEntry{ TextId::SelectBodyType,                                "select_body_type" },
        TextIdEntry{ TextId::SelectDistanceUnit,                            "select_distance_unit" },
        TextIdEntry{ TextId::SelectedBodyType,                              "selected_body_type" },
        TextIdEntry{ TextId::SelectedLanguage,                              "selected_language" },
        TextIdEntry{ TextId::SelectedUnit,                                  "selected_unit" },
        TextIdEntry{ TextId::SelectLanguage,                                "select_language" },
        TextIdEntry{ TextId::SelectMassUnit,                                "select_mass_unit" },
        TextIdEntry{ TextId::SelectSpeedUnit,                               "select_speed_unit" },
        TextIdEntry{ TextId::SelectTimeUnitForTimeStep,                     "select_time_unit_for_time_step" },
        TextIdEntry{ TextId::SolarMass,                                     "solar_mass" },
        TextIdEntry{ TextId::SpeedOfLight,                                  "speed_of_light" },
        TextIdEntry{ TextId::Star,                                          "star" },
        TextIdEntry{ TextId::StepCount,                                     "step_count" },
        TextIdEntry{ TextId::ThousandKilometre,                             "thousand_kilometre" },
        TextIdEntry{ TextId::ThousandKilometrePerHour,                      "thousand_kilometre_per_hour" },
        TextIdEntry{ TextId::TimeStep,                                      "time_step" },
        TextIdEntry{ TextId::Ton,                                           "ton" },
        TextIdEntry{ TextId::ValueOutOfRange,                               "value_out_of_range" },
        TextIdEntry{ TextId::Velocity,                                      "velocity" },
        TextIdEntry{ TextId::YouAreEditingBody,                             "you_are_editing_body" },
        TextIdEntry{ TextId::YouEnteredIncorrectValue,                      "you_entered_incorrect_value" },
    } };

    constexpr std::string_view toLocalizationKey(const TextId id) noexcept
    {
        const auto idx{ static_cast<std::size_t>(id) };
        if (idx < TEXT_ID_COUNT) {
            return textIdEntries[idx].key;
        }

        return "invalid_text_id";
    }

} // TextIdEntries
