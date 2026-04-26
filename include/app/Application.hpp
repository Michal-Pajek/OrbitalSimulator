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
	static void options();
	static void testScenario();
	bool m_continue{ true };
};