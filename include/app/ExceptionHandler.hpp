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
