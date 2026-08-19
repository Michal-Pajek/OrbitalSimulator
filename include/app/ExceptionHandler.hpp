#pragma once

namespace ExceptionHandler
{
	enum class ExceptionType
	{
		Argument,
		Domain,
		Logic,
		Range,
		Runtime
	};

	void ensure(const bool condition, const ExceptionType type, const char* message);
}
