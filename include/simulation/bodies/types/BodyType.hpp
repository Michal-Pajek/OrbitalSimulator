#pragma once
#include <cstddef>
#include "localization/TextId.hpp"

enum class BodyTypeId
{
	Meteor,
	Asteroid,
	Comet,
	Moon,
	DwarfPlanet,
	Planet,
	BrownDwarf,
	Star,
	// ----------
	COUNT
};

constexpr auto BODY_TYPE_COUNT{ static_cast<std::size_t>(BodyTypeId::COUNT) };

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
	TextId getTextId() const { return m_textId; }
private:
	BodyType(const TextId textId, const BodyTypeId id, const MassInterval& massInterval) : m_textId{ textId }, m_id{ id }, m_massInterval{ massInterval } {}
	TextId m_textId;
	const BodyTypeId m_id;
	MassInterval m_massInterval;
};
