#pragma once

namespace runtime_checks
{
	enum class Type
	{
		Argument,
		Domain,
		Logic,
		Range,
		Runtime
	};

	void ensure(const bool condition, const Type type, const char* message);
} // namespace runtime_checks
