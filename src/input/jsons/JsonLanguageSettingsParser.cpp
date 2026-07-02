#include "input/jsons/JsonLanguageSettingsParser.hpp"

void JsonLanguageSettingsParser::parse()
{
	require(expectChar('{'));
	require(expectString("language"));
	require(expectChar(':'));
	m_languageCode = getString();
	require(expectChar('}'));
	skipWhiteMarks();
	require(m_pos == m_size);
}
