#pragma once
#include <exception>
#include <string_view>
#include <utility>

namespace ExceptionHandler
{
	namespace detail
	{
		void writeError(std::string_view message = "Unknown exception");
	}

	enum class ExceptionType
	{
		Argument,
		Domain,
		Logic,
		Range,
		Runtime
	};

	void ensure(const bool condition, const ExceptionType type, const char* message);

	template<typename Action>
	void execute(Action&& action)
	{
		try {
			std::forward<Action>(action)();
		}
		catch (const std::exception& e) {
			detail::writeError(e.what());
		}
		catch (...) {
			detail::writeError();
		}
	}
}
