#include "localization/Localization.hpp"
#include <stdexcept>

namespace
{
	Language g_language{ Language::English };
}

namespace Localization
{
	void setCurrentLanguage(const Language language)
	{
		g_language = language;
	}

	Language getCurrentLanguage()
	{
		return g_language;
	}

	YesAndNo getYn()
	{
		switch (g_language) {
		case Language::English:
			return YesAndNo{ .yes = 'Y', .no = 'N' };
		case Language::Polish:
			return YesAndNo{ .yes = 'T', .no = 'N' };
		default:
			throw std::runtime_error("Unsupported language");
		}
	}

	std::string_view translate(const TextId id)
	{
		switch (g_language) {
		case Language::English:
			switch (id) {
			case TextId::Accept:
				return "Accept";
			case TextId::AddBody:
				return "Add body";
			case TextId::ApplicationFinished:
				return "The program has finished running";
			case TextId::Asteroid:
				return "Asteroid";
			case TextId::AstronomicalUnit:
				return "Astronomical unit";
			case TextId::AverageEarthToMoonDistance:
				return "Average Earth-Moon distance";
			case TextId::Back:
				return "Back";
			case TextId::Bodies:
				return "Bodies";
			case TextId::BodyDeleted:
				return "Body deleted";
			case TextId::BodyMass:
				return "Body mass";
			case TextId::BodyName:
				return "Body name";
			case TextId::BodyNameAlreadyUsedEnterAnother:
				return "This body name is already used. Enter another";
			case TextId::BodyPosition:
				return "Body position";
			case TextId::BodyPositionAlreadyOccupiedEnterAnother:
				return "This body position is already occupied. Enter another";
			case TextId::BodyVelocity:
				return "Body velocity";
			case TextId::BrownDwarf:
				return "Brown dwarf";
			case TextId::Cancel:
				return "Cancel";
			case TextId::Comet:
				return "Comet";
			case TextId::ConfirmBody:
				return "Confirm body";
			case TextId::CurrentBodiesList:
				return "Current bodies list";
			case TextId::CurrentScenarioSummary:
				return "Current scenario summary";
			case TextId::Custom:
				return "Custom";
			case TextId::Day:
				return "Day";
			case TextId::DeleteBody:
				return "Delete body";
			case TextId::DwarfPlanet:
				return "Dwarf planet / moon";
			case TextId::EarthMass:
				return "Earth mass";
			case TextId::EditBody:
				return "Edit body";
			case TextId::EnterBodyMass:
				return "Enter body mass";
			case TextId::EnterBodyNumber:
				return "Enter body number";
			case TextId::EnterDifferentValue:
				return "Enter a different value";
			case TextId::EnterNewBodyData:
				return "Enter new body data";
			case TextId::EnterObjectCountNotGreaterThan:
				return "Enter number of objects not greater than";
			case TextId::EnterOneWordName:
				return "Enter one-word name";
			case TextId::EnterPositionVector:
				return "Enter position vector";
			case TextId::EnterScenarioName:
				return "Enter scenario name";
			case TextId::EnterStepCount:
				return "Enter step count";
			case TextId::EnterTimeStep:
				return "Enter time step";
			case TextId::EnterVelocityVector:
				return "Enter velocity vector";
			case TextId::Exit:
				return "Exit";
			case TextId::Hour:
				return "Hour";
			case TextId::Kilogram:
				return "Kilogram";
			case TextId::Kilometre:
				return "Kilometre";
			case TextId::KilometrePerSecond:
				return "Kilometre per second";
			case TextId::Kiloton:
				return "Kiloton";
			case TextId::MainMenu:
				return "Main menu";
			case TextId::Mass:
				return "Mass";
			case TextId::Megaton:
				return "Megaton";
			case TextId::Meteor:
				return "Meteor";
			case TextId::Metre:
				return "Metre";
			case TextId::MetrePerSecond:
				return "Metre per second";
			case TextId::MillionKilometre:
				return "Million kilometre";
			case TextId::Minute:
				return "Minute";
			case TextId::NotImplemented:
				return "Not implemented yet";
			case TextId::ObjectCount:
				return "Object count";
			case TextId::Options:
				return "Options";
			case TextId::Planet:
				return "Planet";
			case TextId::Position:
				return "Position";
			case TextId::PositiveNumber:
				return "positive number";
			case TextId::PressAnyKeyToContinue:
				return "Press any key to continue...";
			case TextId::PressAnyKeyToReturnToMainMenu:
				return "Press any key to return to main menu...";
			case TextId::QuestionDoYouWantToAccept:
				return "Do you want to accept?";
			case TextId::QuestionDoYouWantToFinish:
				return "Do you want to finish?";
			case TextId::QuestionWhatDoYouWantToChange:
				return "What do you want to change?";
			case TextId::QuestionWhatDoYouWantToChangeInBody:
				return "What do you want to change in body?";
			case TextId::QuestionWhatDoYouWantToDo:
				return "What do you want to do?";
			case TextId::QuestionWhatDoYouWantToDoWithBodies:
				return "What do you want to do with bodies?";
			case TextId::Revise:
				return "Revise";
			case TextId::RunTestScenario:
				return "Run test scenario";
			case TextId::ScenarioBuilder:
				return "Scenario builder";
			case TextId::ScenarioCreatedSuccessfully:
				return "Scenario created successfully";
			case TextId::ScenarioCreationCanceled:
				return "Scenario creation canceled";
			case TextId::ScenarioMustHaveAtLeastOneBody:
				return "Scenario must have at least one body";
			case TextId::ScenarioName:
				return "Scenario name";
			case TextId::Second:
				return "Second";
			case TextId::SelectBodyType:
				return "Select body type";
			case TextId::SelectDistanceUnit:
				return "Select distance unit";
			case TextId::SelectedUnit:
				return "Selected unit";
			case TextId::SelectMassUnit:
				return "Select mass unit";
			case TextId::SelectSpeedUnit:
				return "Select speed unit";
			case TextId::SelectTimeUnitForTimeStep:
				return "Select time unit for time step";
			case TextId::SolarMass:
				return "Solar mass";
			case TextId::SpeedOfLight:
				return "Speed of light";
			case TextId::Star:
				return "Star";
			case TextId::StepCount:
				return "Step count";
			case TextId::ThousandKilometre:
				return "Thousand kilometre";
			case TextId::ThousandKilometrePerHour:
				return "Thousand kilometre per hour";
			case TextId::TimeStep:
				return "Time step";
			case TextId::Ton:
				return "Ton";
			case TextId::ValueOutOfRange:
				return "Value out of range";
			case TextId::Velocity:
				return "Velocity";
			case TextId::Yes:
				return "Yes";
			case TextId::YouAreEditingBody:
				return "You are editing body";
			case TextId::YouEnteredIncorrectValue:
				return "You entered incorrect value";
			}
			break;

		case Language::Polish:
			switch (id) {
			case TextId::Accept:
				return "Akceptuj";
			case TextId::AddBody:
				return "Dodaj obiekt";
			case TextId::ApplicationFinished:
				return "Program zakonczyl prace";
			case TextId::Asteroid:
				return "Asteroida";
			case TextId::AstronomicalUnit:
				return "Jednostka astronomiczna";
			case TextId::AverageEarthToMoonDistance:
				return "Srednia odleglosc Ziemia-Ksiezyc";
			case TextId::Back:
				return "Wstecz";
			case TextId::Bodies:
				return "Obiekty";
			case TextId::BodyDeleted:
				return "Usunieto obiekt";
			case TextId::BodyMass:
				return "Masa obiektu";
			case TextId::BodyName:
				return "Nazwa obiektu";
			case TextId::BodyNameAlreadyUsedEnterAnother:
				return "Ta nazwa obiektu jest juz uzywana. Wprowadz inna";
			case TextId::BodyPosition:
				return "Polozenie obiektu";
			case TextId::BodyPositionAlreadyOccupiedEnterAnother:
				return "Ta pozycja obiektu jest juz zajeta. Wprowadz inna";
			case TextId::BodyVelocity:
				return "Predkosc obiektu";
			case TextId::BrownDwarf:
				return "Brazowy karzel";
			case TextId::Cancel:
				return "Anuluj";
			case TextId::Comet:
				return "Kometa";
			case TextId::ConfirmBody:
				return "Potwierdz obiekt";
			case TextId::CurrentBodiesList:
				return "Aktualna lista obiektow";
			case TextId::CurrentScenarioSummary:
				return "Aktualne podsumowanie scenariusza";
			case TextId::Custom:
				return "Dowolny";
			case TextId::Day:
				return "Dzien";
			case TextId::DeleteBody:
				return "Usun obiekt";
			case TextId::DwarfPlanet:
				return "Planeta karlowata / ksiezyc";
			case TextId::EarthMass:
				return "Masa Ziemi";
			case TextId::EditBody:
				return "Edytuj obiekt";
			case TextId::EnterBodyMass:
				return "Wprowadz mase obiektu";
			case TextId::EnterBodyNumber:
				return "Wprowadz numer obiektu";
			case TextId::EnterDifferentValue:
				return "Wprowadz inna wartosc";
			case TextId::EnterNewBodyData:
				return "Wprowadz dane nowego obiektu";
			case TextId::EnterObjectCountNotGreaterThan:
				return "Wprowadz liczbe obiektow nie wieksza niz";
			case TextId::EnterOneWordName:
				return "Wprowadz jednowyrazowa nazwe";
			case TextId::EnterPositionVector:
				return "Wprowadz wektor polozenia";
			case TextId::EnterStepCount:
				return "Wprowadz liczbe krokow";
			case TextId::EnterScenarioName:
				return "Wprowadz nazwe scenariusza";
			case TextId::EnterTimeStep:
				return "Wprowadz dlugosc pojedynczego kroku";
			case TextId::EnterVelocityVector:
				return "Wprowadz wektor predkosci";
			case TextId::Exit:
				return "Wyjscie";
			case TextId::Hour:
				return "Godzina";
			case TextId::Kilogram:
				return "Kilogram";
			case TextId::Kilometre:
				return "Kilometr";
			case TextId::KilometrePerSecond:
				return "Kilometr na sekunde";
			case TextId::Kiloton:
				return "Kilotona";
			case TextId::MainMenu:
				return "Menu glowne";
			case TextId::Mass:
				return "Masa";
			case TextId::Megaton:
				return "Megatona";
			case TextId::Meteor:
				return "Meteoryt";
			case TextId::Metre:
				return "Metr";
			case TextId::MetrePerSecond:
				return "Metr na sekunde";
			case TextId::MillionKilometre:
				return "Milion kilometrow";
			case TextId::Minute:
				return "Minuta";
			case TextId::NotImplemented:
				return "Jeszcze nie zaimplementowano";
			case TextId::ObjectCount:
				return "Liczba obiektow";
			case TextId::Options:
				return "Opcje";
			case TextId::Planet:
				return "Planeta";
			case TextId::Position:
				return "Polozenie";
			case TextId::PositiveNumber:
				return "dodatnia liczba";
			case TextId::PressAnyKeyToContinue:
				return "Wcisnij dowolny klawisz, aby kontynuowac...";
			case TextId::PressAnyKeyToReturnToMainMenu:
				return "Wcisnij dowolny klawisz, aby wrocic do menu glownego...";
			case TextId::QuestionDoYouWantToAccept:
				return "Czy chcesz zaakceptowac?";
			case TextId::QuestionDoYouWantToFinish:
				return "Czy chcesz zakonczyc?";
			case TextId::QuestionWhatDoYouWantToChange:
				return "Co chcesz zmienic?";
			case TextId::QuestionWhatDoYouWantToChangeInBody:
				return "Co chcesz zmienic w obiekcie?";
			case TextId::QuestionWhatDoYouWantToDo:
				return "Co chcesz zrobic?";
			case TextId::QuestionWhatDoYouWantToDoWithBodies:
				return "Co chcesz zrobic z obiektami?";
			case TextId::Revise:
				return "Popraw";
			case TextId::RunTestScenario:
				return "Uruchom scenariusz testowy";
			case TextId::ScenarioBuilder:
				return "Utworz scenariusz";
			case TextId::ScenarioCreatedSuccessfully:
				return "Scenariusz poprawnie utworzony";
			case TextId::ScenarioCreationCanceled:
				return "Anulowano tworzenie scenariusza";
			case TextId::ScenarioMustHaveAtLeastOneBody:
				return "Scenariusz musi zawierac co najmniej jeden obiekt";
			case TextId::ScenarioName:
				return "Nazwa scenariusza";
			case TextId::Second:
				return "Sekunda";
			case TextId::SelectBodyType:
				return "Wybierz rodzaj obiektu";
			case TextId::SelectDistanceUnit:
				return "Wybierz jednostke odleglosci";
			case TextId::SelectedUnit:
				return "Wybrana jednostka";
			case TextId::SelectMassUnit:
				return "Wybierz jednostke masy";
			case TextId::SelectSpeedUnit:
				return "Wybierz jednostke predkosci";
			case TextId::SelectTimeUnitForTimeStep:
				return "Wybierz jednostke czasu dla pojedynczego kroku";
			case TextId::SolarMass:
				return "Masa Slonca";
			case TextId::SpeedOfLight:
				return "Predkosc swiatla";
			case TextId::Star:
				return "Gwiazda";
			case TextId::StepCount:
				return "Liczba krokow";
			case TextId::ThousandKilometre:
				return "Tysiac kilometrow";
			case TextId::ThousandKilometrePerHour:
				return "Tysiac kilometrow na godzine";
			case TextId::TimeStep:
				return "Krok czasowy";
			case TextId::Ton:
				return "Tona";
			case TextId::ValueOutOfRange:
				return "Wartosc poza zakresem";
			case TextId::Velocity:
				return "Predkosc";
			case TextId::Yes:
				return "Tak";
			case TextId::YouAreEditingBody:
				return "Edytujesz obiekt";
			case TextId::YouEnteredIncorrectValue:
				return "Wprowadziles niepoprawna wartosc";
			}
			break;
		}

		throw std::runtime_error("Missing translation.");
	}
}