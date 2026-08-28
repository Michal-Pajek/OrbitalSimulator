#pragma once
#include <cstddef>
#include <string_view>

#include "localization/core/TextId.hpp"

namespace body
{
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
		localization::TextId getTextId() const { return m_textId; }
		std::string_view getSerializationKey() const { return m_serializationKey; }
	private:
		BodyType(const localization::TextId textId, std::string_view serializationKey, const BodyTypeId id, const MassInterval& massInterval)
			: m_textId{ textId }, m_serializationKey{ serializationKey }, m_id{ id }, m_massInterval{ massInterval } {
		}
		localization::TextId m_textId;
		std::string_view m_serializationKey;
		const BodyTypeId m_id;
		MassInterval m_massInterval;
	};
} // namespace body
