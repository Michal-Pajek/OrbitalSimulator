#include "app/ExceptionHandler.hpp"
#include <stdexcept>
#include "ui/ConsoleWriter.hpp"

namespace ExceptionHandler
{
	namespace
	{
		void throwException(const ExceptionType type, const char* message)
		{
			switch (type) {
			case ExceptionType::Argument:
				throw std::invalid_argument{ message };
			case ExceptionType::Domain:
				throw std::domain_error{ message };
			case ExceptionType::Logic:
				throw std::logic_error{ message };
			case ExceptionType::Range:
				throw std::out_of_range{ message };
			case ExceptionType::Runtime:
				throw std::runtime_error{ message };
			default:
				throw std::logic_error{ "Unknown ExceptionType" };
			}
		}
	}

	void ensure(const bool condition, const ExceptionType type, const char* message)
	{
		if (!condition) {
			throwException(type, message);
		}
	}

	void detail::writeError(std::string_view message)
	{
		ConsoleWriter::writeError(message);
	}

} // ExceptionHandler
