#include "Print.hpp"

#include <cmath>

namespace gsclib
{
	std::string Print::Format(const char* format, VariableValueArray args)
	{
		std::string result;
		int argIndex = 0;
		const char* p = format;

		while (*p)
		{
			if (*p != '%')
			{
				result += *p++;
				continue;
			}
			p++; // Skip '%'

			if (*p == '%')
			{
				result += '%';
				p++;
				continue;
			}
			// Parse the format specifier
			std::string spec;
			spec += '%';

			// Flags: -, +, ' ', #, 0
			while (*p == '-' || *p == '+' || *p == ' ' || *p == '#' || *p == '0' || *p == '\'')
				spec += *p++;

			// Width
			while (*p >= '0' && *p <= '9')
				spec += *p++;

			// Precision
			if (*p == '.')
			{
				spec += *p++;
				while (*p >= '0' && *p <= '9')
					spec += *p++;
			}
			// Length modifiers (ignored, we use VariableValue types)
			while (*p == 'h' || *p == 'l' || *p == 'L' || *p == 'z' || *p == 'j' || *p == 't')
				p++;

			// Conversion specifier
			if (*p)
				spec += *p++;

			// Format the argument
			if (argIndex < args.length)
				result += FormatValue(spec, &args.items[argIndex++]);
		}
		return result;
	}

	std::string Print::FormatValue(const std::string& spec, VariableValue* value)
	{
		if (spec.empty())
			return "";

		char type = spec.back();
		std::string fmtSpec = ConvertSpecifier(spec);

		switch (value->type)
		{
		case VAR_STRING:
		case VAR_ISTRING:
		{
			const char* str = Plugin_SL_ConvertToString(value->u.stringValue);
			if (type == 's')
				return std::vformat(fmtSpec, std::make_format_args(str));
			return str;
		}
		case VAR_INTEGER:
		{
			int val = value->u.intValue;
			switch (type)
			{
			case 'd':
			case 'i':
				return std::vformat(fmtSpec, std::make_format_args(val));
			case 'u':
			case 'x':
			case 'X':
			case 'o':
			{
				unsigned int uval = static_cast<unsigned int>(val);
				return std::vformat(fmtSpec, std::make_format_args(uval));
			}
			case 'f':
			case 'F':
			case 'e':
			case 'E':
			case 'g':
			case 'G':
			{
				double dval = static_cast<double>(val);
				return std::vformat(fmtSpec, std::make_format_args(dval));
			}
			case 's':
			default:
				return std::format("{}", val);
			}
		}
		case VAR_FLOAT:
		{
			double val = static_cast<double>(value->u.floatValue);
			switch (type)
			{
			case 'f':
			case 'F':
			case 'e':
			case 'E':
			case 'g':
			case 'G':
				return std::vformat(fmtSpec, std::make_format_args(val));
			case 'd':
			case 'i':
			{
				int ival = static_cast<int>(val);
				return std::vformat(fmtSpec, std::make_format_args(ival));
			}
			case 's':
			default:
				return std::format("{}", val);
			}
		}
		case VAR_VECTOR:
		{
			const float* vec = value->u.vectorValue;
			return std::format("({}, {}, {})", vec[0], vec[1], vec[2]);
		}
		}
		return "";
	}

	std::string Print::ConvertSpecifier(const std::string& spec)
	{
		if (spec.length() < 2)
			return "{}";

		std::string result = "{:";
		size_t i = 1; // Skip '%'
		char type = spec.back();

		// Flags
		while (i < spec.length() - 1)
		{
			char c = spec[i];
			if (c == '-')
			{
				result += '<';
				i++;
			}
			else if (c == '+')
			{
				result += '+';
				i++;
			}
			else if (c == ' ')
			{
				result += ' ';
				i++;
			}
			else if (c == '#')
			{
				result += '#';
				i++;
			}
			else if (c == '0')
			{
				result += '0';
				i++;
			}
			else if (c == '\'')
				i++; // Skip, not supported in std::format
			else
				break;
		}
		// Width
		std::string width;
		while (i < spec.length() - 1 && spec[i] >= '0' && spec[i] <= '9')
			width += spec[i++];
		if (!width.empty())
			result += width;

		// Precision
		if (i < spec.length() - 1 && spec[i] == '.')
		{
			result += '.';
			i++;
			while (i < spec.length() - 1 && spec[i] >= '0' && spec[i] <= '9')
				result += spec[i++];
		}
		// Type
		switch (type)
		{
		case 'd':
		case 'i':
			result += 'd';
			break;
		case 'u':
			result += 'd';
			break;
		case 'x':
			result += 'x';
			break;
		case 'X':
			result += 'X';
			break;
		case 'o':
			result += 'o';
			break;
		case 'f':
			result += 'f';
			break;
		case 'F':
			result += 'F';
			break;
		case 'e':
			result += 'e';
			break;
		case 'E':
			result += 'E';
			break;
		case 'g':
			result += 'g';
			break;
		case 'G':
			result += 'G';
			break;
		case 's':
			result += 's';
			break;
		case 'c':
			result += 'c';
			break;
		case 'p':
			result += 'p';
			break;
		default:
			break;
		}
		result += '}';
		return result;
	}
}
