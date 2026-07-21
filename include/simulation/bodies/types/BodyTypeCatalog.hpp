#pragma once
#include <array>
#include <span>
#include <string_view>
#include "BodyType.hpp"

class BodyTypeCatalog
{
public:
	static const BodyType& getType(const BodyTypeId id);
	static std::span<const BodyType> getAvailableTypes() { return bodyTypesArray; }
	static std::string_view getSerializationKey(const BodyTypeId id) { return getType(id).getSerializationKey(); }
private:
	static const std::array<BodyType, BODY_TYPE_COUNT> bodyTypesArray;
};
