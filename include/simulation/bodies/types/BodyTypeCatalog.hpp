#pragma once
#include <array>
#include <span>
#include "BodyType.hpp"

class BodyTypeCatalog
{
public:
	static const BodyType& getType(const BodyTypeId id);
	static std::span<const BodyType> getAvailableTypes() { return bodyTypesArray; }
private:
	static const std::array<BodyType, 7u> bodyTypesArray;
};