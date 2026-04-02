#pragma once
#include <string>

class Application
{
public:
	void eventLoop();
	static void testScenario();
	static void options();
private:
	static void enterModule(const std::string& text);
	static void exitModule();
	bool m_continue{ true };
};