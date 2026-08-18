#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include "localization/TextId.hpp"
#include "math/Vector3D.hpp"
#include "ui/ConsoleWriter.hpp"

namespace DataGetter
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
					ConsoleWriter::write(TextId::YouEnteredIncorrectValue, ". ", TextId::EnterDifferentValue, ": ");
					continue;
				}
				if (predicate(result)) {
					discardLineRemainder();
					return result;
				}
				ConsoleWriter::write(TextId::ValueOutOfRange, ". ", TextId::EnterDifferentValue, ": ");
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
	Vector3D getVector3D(const Predicate& predicate)
	{
		double x, y, z;
		while (true) {
			std::cin >> x >> y >> z;
			if (!detail::recoverFromInputFailure()) {
				ConsoleWriter::write(TextId::YouEnteredIncorrectValue, ". ", TextId::EnterDifferentValue, ": ");
				continue;
			}
			if (predicate(x, y, z)) {
				detail::discardLineRemainder();
				return Vector3D{ x, y, z };
			}
			ConsoleWriter::write(TextId::ValueOutOfRange, ". ", TextId::EnterDifferentValue, ": ");
		}
	}

	inline Vector3D getVector3D()
	{
		return getVector3D([](double, double, double) {return true; });
	}

	std::size_t getSelectionNumber(const TextId textId, const std::size_t count, bool includingZero = false);
	std::string getSingleWordText();
	std::string getFileBaseName();
} // namespace DataGetter
