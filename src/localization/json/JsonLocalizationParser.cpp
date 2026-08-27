#include "localization/json/JsonLocalizationParser.hpp"

#include <string>

#include "common/runtime_checks/RuntimeChecks.hpp"

void JsonLocalizationParser::parse()
{
	require(expectChar('{'));
	require(expectString("texts"));
	require(expectChar(':'));
	require(expectChar('{'));
	parseTexts();
	require(expectChar('}'));
	require(expectChar('}'));
	skipWhiteMarks();
	require(m_pos == m_size);
}

void JsonLocalizationParser::parseTexts()
{
	do {
		const auto key{ getString() };
		require(expectChar(':'));
		const auto value{ getString() };
		require(!(key.empty() || value.empty()));
		const auto [it, inserted]{ m_localizationData.insert({ key, value }) };
		runtime_checks::ensure(inserted, runtime_checks::Type::Runtime, std::string{ "Duplicated localization key: " + it->first }.c_str());
		skipWhiteMarks();
		ensureCanRead();
		if (m_data[m_pos] == ',') {
			++m_pos;
		}
		else {
			return;
		}
	} while (true);
}
