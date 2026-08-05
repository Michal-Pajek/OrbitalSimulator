#pragma once
#include "localization/TextId.hpp"

class Application
{
public:
	void eventLoop();
private:
	static void buildScenario();
	static void enterModule(const TextId titleId);
	static void exitModule();
	static void loadScenario();
	static void selectLanguage();
	bool m_continue{ true };
};
