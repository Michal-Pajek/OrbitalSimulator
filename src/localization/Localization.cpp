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
			case TextId::BackToMainMenu:
				return "\nPress any key to back to main menu...";
			case TextId::Exit:
				return "Exit";
			case TextId::FinishQuestion:
				return "Do you want to finish?";
			case TextId::FinishRunning:
				return "Yes\nThe program has finished running. Press any key...";
			case TextId::MainMenu:
				return "Main Menu";
			case TextId::NotImplemented:
				return "Not implemented yet";
			case TextId::Options:
				return "Options";
			case TextId::RunTestScenario:
				return "Run test scenario";
			}
			break;

		case Language::Polish:
			switch (id) {
			case TextId::BackToMainMenu:
				return "\nWcisnij dowolny klawisz, aby wrocic do menu glownego...";
			case TextId::Exit:
				return "Wyjscie";
			case TextId::FinishQuestion:
				return "Na pewno chcesz wyjsc?";
			case TextId::FinishRunning:
				return "Tak\nProgram zakonczyl prace. Wcisnij dowolny klawisz...";
			case TextId::MainMenu:
				return "Menu Glowne";
			case TextId::NotImplemented:
				return "Jeszcze nie zaimplementowano";
			case TextId::Options:
				return "Opcje";
			case TextId::RunTestScenario:
				return "Uruchom scenariusz testowy";
			}
			break;
		}

		throw std::runtime_error("Missing translation.");
	}
}