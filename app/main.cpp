#include "app/Application.hpp"
#include "localization/Localization.hpp"

int main()
{
	Localization::setCurrentLanguage(Language::English);
	Application app{};
	app.eventLoop();
}
