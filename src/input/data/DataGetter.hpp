#pragma once
#include <iostream>
#include <string>
#include <type_traits>

#include "localization/core/TextId.hpp"
#include "math/Vector3D.hpp"
#include "ui/ConsoleWriter.hpp"

namespace input::data
{
	namespace detail
	{
		bool recoverFromInputFailure();
		void discardLineRemainder();

		template <typename T, typename Predicate>
		T getValidatedInput(const Predicate& predicate)
		{
			T result{};
			while (true) {
				std::cin >> result;
				if (!recoverFromInputFailure()) {
					ConsoleWriter::write(localization::TextId::YouEnteredIncorrectValue, ". ", localization::TextId::EnterDifferentValue, ": ");
					continue;
				}
				if (predicate(result)) {
					discardLineRemainder();
					return result;
				}
				ConsoleWriter::write(localization::TextId::ValueOutOfRange, ". ", localization::TextId::EnterDifferentValue, ": ");
			}
		}
	} // namespace detail

	template <typename T, typename Predicate>
	T getValue(const Predicate& predicate)
	{
		static_assert(std::is_arithmetic_v<T>, "T must be a numeric type.");
		return detail::getValidatedInput<T>(predicate);
	}

	template <typename T>
	T getValue()
	{
		return getValue<T>([](T) {return true; });
	}

	template <typename Predicate>
	math::Vector3D getVector3D(const Predicate& predicate)
	{
		double x, y, z;
		while (true) {
			std::cin >> x >> y >> z;
			if (!detail::recoverFromInputFailure()) {
				ConsoleWriter::write(localization::TextId::YouEnteredIncorrectValue, ". ", localization::TextId::EnterDifferentValue, ": ");
				continue;
			}
			if (predicate(x, y, z)) {
				detail::discardLineRemainder();
				return math::Vector3D{ x, y, z };
			}
			ConsoleWriter::write(localization::TextId::ValueOutOfRange, ". ", localization::TextId::EnterDifferentValue, ": ");
		}
	}

	inline math::Vector3D getVector3D()
	{
		return getVector3D([](double, double, double) {return true; });
	}

	std::size_t getSelectionNumber(const localization::TextId textId, const std::size_t count, bool includeZero = false);
	std::string getSingleWordText();
	std::string getFileBaseName();
} // namespace input::data
