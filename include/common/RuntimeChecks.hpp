#pragma once

namespace RuntimeChecks
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
} // namespace RuntimeChecks
