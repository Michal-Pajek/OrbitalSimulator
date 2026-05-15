#pragma once
#include <array>
#include <vector>
#include "input/UnitSelector.hpp"
#include "localization/TextId.hpp"

struct MassInterval
{
	double min;
	double max;
};

class BodyType
{
public:
	BodyType(const BodyType&) = delete;
	BodyType& operator=(const BodyType&) = delete;
	const MassInterval& getMassInterval() const { return m_massInterval; }
	const TextId& getTextId() const { return m_textId; }
	const std::vector<UnitSelector::UnitOption>& getMassUnitVector() const { return m_massUnitVector; }
	static const BodyType* getType(const TextId textId);
private:
	BodyType(const TextId textId, const MassInterval& massInterval) : m_textId{ textId }, m_massInterval{ massInterval }, m_massUnitVector{ generateMassUnitVector() } {}
	std::vector<UnitSelector::UnitOption> generateMassUnitVector();
	TextId m_textId;
	MassInterval m_massInterval;
	std::vector<UnitSelector::UnitOption> m_massUnitVector;
	static const std::array<BodyType, 7> bodyTypeList;
};