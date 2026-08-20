#include "common/RuntimeChecks.hpp"

#include <stdexcept>

namespace RuntimeChecks
{
	namespace
	{
		void throwException(const Type type, const char* message)
		{
			switch (type) {
			case Type::Argument:
				throw std::invalid_argument{ message };
			case Type::Domain:
				throw std::domain_error{ message };
			case Type::Logic:
				throw std::logic_error{ message };
			case Type::Range:
				throw std::out_of_range{ message };
			case Type::Runtime:
				throw std::runtime_error{ message };
			default:
				throw std::logic_error{ "Unknown RuntimeChecks::Type" };
			}
		}
	} // anonymous namespace

	void ensure(const bool condition, const Type type, const char* message)
	{
		if (!condition) {
			throwException(type, message);
		}
	}
} // namespace RuntimeChecks
