#pragma once
#include "Base.hpp"

namespace gsclib
{
	class Print
	{
	public:
		static std::string Format(const char* format, VariableValueArray args);

	private:
		static std::string FormatValue(const std::string& spec, VariableValue* value);
		static std::string ConvertSpecifier(const std::string& spec);
	};
}
