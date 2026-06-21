#pragma once
#include <vector>
#include "input/OptionSelector.hpp"
#include "localization/TextId.hpp"

enum class BodyTypeId
{
	Meteor,
	Asteroid,
	Comet,
	DwarfPlanet,
	Planet,
	BrownDwarf,
	Star
};

struct MassInterval
{
	double min;
	double max;
};

class BodyType
{
	friend class BodyTypeCatalog;
public:
	BodyType(const BodyType&) = delete;
	BodyType& operator=(const BodyType&) = delete;
	BodyTypeId getId() const { return m_id; }
	const MassInterval& getMassInterval() const { return m_massInterval; }
	const std::vector<UnitSelector::UnitOption>& getMassUnitVector() const { return m_massUnitVector; }
	TextId getTextId() const { return m_textId; }
private:
	BodyType(const TextId textId, const BodyTypeId id, const MassInterval& massInterval) : m_textId{ textId }, m_id{ id }, m_massInterval{ massInterval }, m_massUnitVector{ generateMassUnitVector() } {}
	std::vector<UnitSelector::UnitOption> generateMassUnitVector();
	TextId m_textId;
	const BodyTypeId m_id;
	MassInterval m_massInterval;
	std::vector<UnitSelector::UnitOption> m_massUnitVector;
};