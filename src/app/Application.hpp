#pragma once
#include "localization/core/TextId.hpp"

namespace app
{
	class Application
	{
	public:
		void eventLoop();
	private:
		static void buildScenario();
		static void enterModule(const localization::TextId titleId);
		static void exitModule();
		static void loadScenario();
		static void selectLanguage();
		bool m_continue{ true };
	};
} // namespace app
