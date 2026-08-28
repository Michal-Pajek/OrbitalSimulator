#include "app/ExceptionHandler.hpp"

#include "ui/ConsoleWriter.hpp"

namespace app::exception_handler
{
	void detail::writeError(std::string_view message)
	{
		ui::console::writeError(message);
	}
} // namespace app::exception_handler
