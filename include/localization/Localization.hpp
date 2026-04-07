#pragma once
#include <string_view>
#include "Language.hpp"
#include "TextId.hpp"

namespace Localization
{
	struct YesAndNo
	{
		char yes;
		char no;
	};

	void setCurrentLanguage(const Language language);
	Language getCurrentLanguage();
	YesAndNo getYn();
	std::string_view translate(const TextId id);
}