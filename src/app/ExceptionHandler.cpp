#include "app/ExceptionHandler.hpp"

#include "ui/ConsoleWriter.hpp"

namespace ExceptionHandler
{
	void detail::writeError(std::string_view message)
	{
		ConsoleWriter::writeError(message);
	}
} // namespace ExceptionHandler
