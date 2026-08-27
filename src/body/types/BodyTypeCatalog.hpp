#pragma once
#include <array>
#include <optional>
#include <span>
#include <string_view>

#include "body/types/BodyType.hpp"

namespace body
{
	class BodyTypeCatalog
	{
	public:
		static const BodyType& getType(const BodyTypeId id);
		static bool isMassInRange(const BodyTypeId id, const double mass);
		static std::span<const BodyType> getAvailableTypes() { return bodyTypesArray; }
		static std::string_view getSerializationKey(const BodyTypeId id) { return getType(id).getSerializationKey(); }
		static std::optional<BodyTypeId> deserializeKey(std::string_view serializationKey);
	private:
		static const std::array<BodyType, BODY_TYPE_COUNT> bodyTypesArray;
	};
} // namespace body
