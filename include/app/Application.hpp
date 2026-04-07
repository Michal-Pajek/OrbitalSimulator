#pragma once
#include "localization/TextId.hpp"

class Application
{
public:
	void eventLoop();
	static void testScenario();
	static void options();
private:
	static void enterModule(const TextId titleId);
	static void exitModule();
	bool m_continue{ true };
};