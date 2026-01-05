#include "Utils.hpp"
#include "Print.hpp"

#include <cctype>
#include <charconv>
#include <cmath>
#include <cstdarg>
#include <cstring>
#include <filesystem>

static int Q3ToAnsi[8] = {
	30, // COLOR_BLACK
	31, // COLOR_RED
	32, // COLOR_GREEN
	33, // COLOR_YELLOW
	34, // COLOR_BLUE
	36, // COLOR_CYAN
	35, // COLOR_MAGENTA
	0	// COLOR_WHITE
};

namespace gsclib
{
	void Utils::ToInt()
	{
		CHECK_PARAMS(1, "Usage: ToInt(<type>)\n");

		VariableValue* var = Plugin_Scr_SelectParam(0);
		switch (var->type)
		{
		case VAR_ISTRING:
		case VAR_STRING:
		{
			const char* str = Plugin_SL_ConvertToString(var->u.stringValue);
			std::string_view sv(str);
			int number = 0;
			auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), number);

			if (ec == std::errc() && ptr == sv.data() + sv.size())
				Plugin_Scr_AddInt(number);
			break;
		}
		case VAR_VECTOR:
			Plugin_Scr_AddInt(static_cast<int>(var->u.vectorValue[0] + var->u.vectorValue[1] + var->u.vectorValue[2]));
			break;
		case VAR_INTEGER:
			Plugin_Scr_AddInt(var->u.intValue);
			break;
		case VAR_FLOAT:
			Plugin_Scr_AddInt(static_cast<int>(var->u.floatValue));
			break;
		}
	}

	void Utils::ToFloat()
	{
		CHECK_PARAMS(1, "Usage: ToFloat(<type>)\n");

		VariableValue* var = Plugin_Scr_SelectParam(0);
		switch (var->type)
		{
		case VAR_ISTRING:
		case VAR_STRING:
		{
			const char* str = Plugin_SL_ConvertToString(var->u.stringValue);
			std::string_view sv(str);
			float number = 0.0f;
			auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), number);

			if (ec == std::errc() && ptr == sv.data() + sv.size())
				Plugin_Scr_AddFloat(number);
			break;
		}
		case VAR_VECTOR:
			Plugin_Scr_AddFloat(var->u.vectorValue[0] + var->u.vectorValue[1] + var->u.vectorValue[2]);
			break;
		case VAR_INTEGER:
			Plugin_Scr_AddFloat(static_cast<float>(var->u.intValue));
			break;
		case VAR_FLOAT:
			Plugin_Scr_AddFloat(var->u.floatValue);
			break;
		}
	}

	void Utils::ToString()
	{
		CHECK_PARAMS(1, "Usage: ToString(<type>)\n");

		VariableValue* var = Plugin_Scr_SelectParam(0);
		switch (var->type)
		{
		case VAR_ISTRING:
		case VAR_STRING:
			Plugin_Scr_AddString(Plugin_SL_ConvertToString(var->u.stringValue));
			break;
		case VAR_VECTOR:
			Plugin_Scr_AddString(
				std::format("({}, {}, {})", var->u.vectorValue[0], var->u.vectorValue[1], var->u.vectorValue[2])
					.c_str());
			break;
		case VAR_INTEGER:
			Plugin_Scr_AddString(std::format("{}", var->u.intValue).c_str());
			break;
		case VAR_FLOAT:
			Plugin_Scr_AddString(std::format("{}", var->u.floatValue).c_str());
			break;
		}
	}

	void Utils::Ternary()
	{
		CHECK_PARAMS(3, "Usage: Ternary(<condition>, <var if true>, <var if false>)\n");

		int condition = Plugin_Scr_GetInt(0);
		VariableValue* a = Plugin_Scr_SelectParam(1);
		VariableValue* b = Plugin_Scr_SelectParam(2);
		Plugin_Scr_AddVariable(condition ? *a : *b);
	}

	void Utils::IfUndef()
	{
		CHECK_PARAMS(2, "Usage: IfUndef(<var>, <default if undef>)\n");

		VariableValue* a = Plugin_Scr_SelectParam(0);
		VariableValue* b = Plugin_Scr_SelectParam(1);
		Plugin_Scr_AddVariable(a->type == VAR_UNDEFINED ? *b : *a);
	}

	void Utils::GetType()
	{
		CHECK_PARAMS(1, "Usage: GetType(<var>)\n");

		VariableValue* var = Plugin_Scr_SelectParam(0);
		switch (var->type)
		{
		case VAR_POINTER:
			switch (Plugin_Scr_GetObjectType(var->u.pointerValue))
			{
			case VAR_ARRAY:
				Plugin_Scr_AddString("ARRAY");
				break;
			case VAR_OBJECT:
				Plugin_Scr_AddString("OBJECT");
				break;
			case VAR_ENTITY:
				Plugin_Scr_AddString("ENTITY");
				break;
			case VAR_UNDEFINED:
			default:
				Plugin_Scr_AddString("UNDEFINED");
				break;
			}
			break;
		case VAR_STRING:
			Plugin_Scr_AddString("STRING");
			break;
		case VAR_ISTRING:
			Plugin_Scr_AddString("ISTRING");
			break;
		case VAR_VECTOR:
			Plugin_Scr_AddString("VECTOR");
			break;
		case VAR_FLOAT:
			Plugin_Scr_AddString("FLOAT");
			break;
		case VAR_INTEGER:
			Plugin_Scr_AddString("INTEGER");
			break;
		case VAR_CODEPOS:
			Plugin_Scr_AddString("CODEPOS");
			break;
		case VAR_PRECODEPOS:
			Plugin_Scr_AddString("PRECODEPOS");
			break;
		case VAR_FUNCTION:
			Plugin_Scr_AddString("FUNCTION");
			break;
		case VAR_STACK:
			Plugin_Scr_AddString("STACK");
			break;
		case VAR_ANIMATION:
			Plugin_Scr_AddString("ANIMATION");
			break;
		case VAR_DEVELOPER_CODEPOS:
			Plugin_Scr_AddString("DEVELOPER_CODEPOS");
			break;
		case VAR_INCLUDE_CODEPOS:
			Plugin_Scr_AddString("INCLUDE_CODEPOS");
			break;
		case VAR_THREAD:
			Plugin_Scr_AddString("THREAD");
			break;
		case VAR_NOTIFY_THREAD:
			Plugin_Scr_AddString("NOTIFY_THREAD");
			break;
		case VAR_TIME_THREAD:
			Plugin_Scr_AddString("TIME_THREAD");
			break;
		case VAR_CHILD_THREAD:
			Plugin_Scr_AddString("CHILD_THREAD");
			break;
		case VAR_OBJECT:
			Plugin_Scr_AddString("OBJECT");
			break;
		case VAR_DEAD_ENTITY:
			Plugin_Scr_AddString("DEAD_ENTITY");
			break;
		case VAR_ENTITY:
			Plugin_Scr_AddString("ENTITY");
			break;
		case VAR_ARRAY:
			Plugin_Scr_AddString("ARRAY");
			break;
		case VAR_DEAD_THREAD:
			Plugin_Scr_AddString("DEAD_THREAD");
			break;
		case VAR_COUNT:
			Plugin_Scr_AddString("COUNT");
			break;
		case VAR_THREAD_LIST:
			Plugin_Scr_AddString("THREAD_LIST");
			break;
		case VAR_ENDON_LIST:
			Plugin_Scr_AddString("ENDON_LIST");
			break;
		case VAR_UNDEFINED:
		default:
			Plugin_Scr_AddString("UNDEFINED");
			break;
		}
	}

	void Utils::IsStringAlpha()
	{
		CHECK_PARAMS(1, "Usage: IsStringAlpha(<string>)\n");

		const char* str = Plugin_Scr_GetString(0);
		std::string_view sv(str);

		for (char c : sv)
		{
			if (!std::isalpha(static_cast<unsigned char>(c)))
			{
				Plugin_Scr_AddBool(qfalse);
				return;
			}
		}
		Plugin_Scr_AddBool(qtrue);
	}

	void Utils::IsStringFloat()
	{
		CHECK_PARAMS(1, "Usage: IsStringFloat(<string>)\n");

		const char* str = Plugin_Scr_GetString(0);
		std::string_view sv(str);
		float number = 0.0f;
		auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), number);

		Plugin_Scr_AddBool(static_cast<qboolean>(ec == std::errc() && ptr == sv.data() + sv.size()));
	}

	void Utils::IsStringInt()
	{
		CHECK_PARAMS(1, "Usage: IsStringInt(<string>)\n");

		const char* str = Plugin_Scr_GetString(0);
		std::string_view sv(str);
		int number = 0;
		auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), number);

		Plugin_Scr_AddBool(static_cast<qboolean>(ec == std::errc() && ptr == sv.data() + sv.size()));
	}

	void Utils::IsNullOrEmpty()
	{
		CHECK_PARAMS(1, "Usage: IsNullOrEmpty(<string>)\n");

		VariableValue* var = Plugin_Scr_SelectParam(0);
		bool isString = var->type == VAR_STRING || var->type == VAR_ISTRING;

		Plugin_Scr_AddBool(
			static_cast<qboolean>(!(isString && Plugin_SL_ConvertToString(var->u.stringValue)[0] != '\0')));
	}

	void Utils::ToRGB()
	{
		CHECK_PARAMS(3, "Usage: ToRGB(<r>, <g>, <b>)\n");

		vec3_t vec = { 0, 0, 0 };
		vec[0] = static_cast<float>(Plugin_Scr_GetInt(0)) / 255.0f;
		vec[1] = static_cast<float>(Plugin_Scr_GetInt(1)) / 255.0f;
		vec[2] = static_cast<float>(Plugin_Scr_GetInt(2)) / 255.0f;

		Plugin_Scr_AddVector(vec);
	}

	void Utils::HexToRGB()
	{
		CHECK_PARAMS(1, "Usage: HexToRGB(<hex string>)\n");

		const char* str = Plugin_Scr_GetString(0);
		std::string_view sv(str);

		if (sv.starts_with('#'))
			sv.remove_prefix(1);

		if (sv.size() != 6)
		{
			Plugin_Scr_ParamError(1, "Wrong HEX color input\n");
			return;
		}
		int rgb = 0;
		auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), rgb, 16);

		if (ec != std::errc())
		{
			Plugin_Scr_ParamError(1, "Wrong HEX color input\n");
			return;
		}
		vec3_t vec = { 0, 0, 0 };
		vec[0] = static_cast<float>((rgb >> 16) & 0xFF) / 255.0f;
		vec[1] = static_cast<float>((rgb >> 8) & 0xFF) / 255.0f;
		vec[2] = static_cast<float>(rgb & 0xFF) / 255.0f;

		Plugin_Scr_AddVector(vec);
	}

	void Utils::ComPrint()
	{
		ScrPrintF(false, &Plugin_Printf);
	}

	void Utils::ComPrintLn()
	{
		ScrPrintF(true, &Plugin_Printf);
	}

	void Utils::SysPrint()
	{
		ScrPrintF(false, &SysPrintF);
	}

	void Utils::SysPrintLn()
	{
		ScrPrintF(true, &SysPrintF);
	}

	void Utils::SysPrintF(const char* format, ...)
	{
		std::va_list argptr;
		va_start(argptr, format);
		std::vfprintf(stderr, format, argptr);
		va_end(argptr);
	}

	void Utils::ScrPrintF(bool newLine, void (*print)(const char*, ...))
	{
		const int argCount = Plugin_Scr_GetNumParam();

		if (argCount == 0)
		{
			print(newLine ? "\n" : "");
			return;
		}
		const char* format = Plugin_Scr_GetString(0);

		if (argCount == 1)
		{
			std::string output = format;
			if (newLine)
				output += "\n";
			AnsiColorPrint(output.c_str(), print);
			return;
		}
		VariableValueArray args = Plugin_Scr_CreateArray(argCount - 1);

		for (int i = 1; i < argCount; i++)
			args.items[i - 1] = *Plugin_Scr_SelectParam(i);

		std::string buffer = Print::Format(format, args);
		if (newLine)
			buffer += "\n";

		AnsiColorPrint(buffer.c_str(), print);
		Plugin_Scr_FreeArray(&args);
	}

	void Utils::AnsiColorPrint(const char* msg, void (*print)(const char*, ...))
	{
		int length = 0;
		static char buffer[MAXPRINTMSG] = { 0 };

		while (*msg)
		{
			if (Q_IsColorString(msg) || *msg == '\n')
			{
				if (length > 0)
				{
					buffer[length] = '\0';
					print(buffer);
					length = 0;
				}
				if (*msg == '\n')
				{
					print("\033[0m\n");
					msg++;
				}
				else
				{
					std::snprintf(buffer, sizeof(buffer), "\033[1;%dm", Q3ToAnsi[ColorIndex(*(msg + 1))]);
					print(buffer);
					msg += 2;
				}
			}
			else
			{
				if (length >= MAXPRINTMSG - 1)
					break;
				buffer[length] = *msg;
				length++;
				msg++;
			}
		}
		if (length > 0)
		{
			buffer[length] = '\0';
			print(buffer);
		}
	}
	void Utils::Fmt()
	{
		const int argCount = Plugin_Scr_GetNumParam();

		if (argCount < 1)
		{
			Plugin_Scr_Error("Usage: fmt(<string>, <?arguments...>)\n");
			return;
		}
		const char* format = Plugin_Scr_GetString(0);

		if (argCount == 1)
		{
			Plugin_Scr_AddString(format);
			return;
		}
		VariableValueArray args = Plugin_Scr_CreateArray(argCount - 1);

		for (int i = 1; i < argCount; i++)
			args.items[i - 1] = *Plugin_Scr_SelectParam(i);

		std::string result = Print::Format(format, args);

		Plugin_Scr_AddString(result.c_str());
		Plugin_Scr_FreeArray(&args);
	}

	void Utils::Trim()
	{
		CHECK_PARAMS(1, "Usage: Trim(<string>)\n");

		std::string str = Plugin_Scr_GetString(0);

		size_t start = str.find_first_not_of(' ');
		if (start == std::string::npos)
		{
			Plugin_Scr_AddString("");
			return;
		}
		size_t end = str.find_last_not_of(' ');
		Plugin_Scr_AddString(str.substr(start, end - start + 1).c_str());
	}

	void Utils::StartsWith()
	{
		CHECK_PARAMS(2, "Usage: StartsWith(<string>, <value>)\n");

		std::string_view str = Plugin_Scr_GetString(0);
		std::string_view value = Plugin_Scr_GetString(1);

		Plugin_Scr_AddBool(static_cast<qboolean>(str.starts_with(value)));
	}

	void Utils::EndsWith()
	{
		CHECK_PARAMS(2, "Usage: EndsWith(<string>, <value>)\n");

		std::string_view str = Plugin_Scr_GetString(0);
		std::string_view value = Plugin_Scr_GetString(1);

		Plugin_Scr_AddBool(static_cast<qboolean>(str.ends_with(value)));
	}

	void Utils::StrJoin()
	{
		CHECK_PARAMS(2, "Usage: StrJoin(<array>, <separator>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const char* separator = Plugin_Scr_GetString(1);

		std::string result;
		uint32_t flags = Plugin_Scr_GetArrayFlags(array);

		if (IsFlag(flags, FLAG_STRING) || IsFlag(flags, FLAG_ISTRING))
		{
			for (int i = 0; i < array.length; i++)
			{
				if (i > 0)
					result += separator;
				result += Plugin_SL_ConvertToString(array.items[i].u.stringValue);
			}
		}
		Plugin_Scr_AddString(result.c_str());
	}

	void Utils::Replace()
	{
		CHECK_PARAMS(3, "Usage: Replace(<source>, <search>, <replace>)\n");

		std::string source = Plugin_Scr_GetString(0);
		std::string_view search = Plugin_Scr_GetString(1);
		std::string_view replace = Plugin_Scr_GetString(2);

		size_t pos = source.find(search);
		if (pos != std::string::npos)
			source.replace(pos, search.length(), replace);

		Plugin_Scr_AddString(source.c_str());
	}

	void Utils::PathJoin()
	{
		const int argCount = Plugin_Scr_GetNumParam();

		if (argCount < 2)
		{
			Plugin_Scr_Error("Usage: PathJoin(<paths...>)\n");
			return;
		}
		std::filesystem::path result = Plugin_Scr_GetString(0);

		for (int i = 1; i < argCount; i++)
			result /= Plugin_Scr_GetString(i);

		Plugin_Scr_AddString(result.string().c_str());
	}

	float Utils::VectorDistance(const vec3_t a, const vec3_t b)
	{
		float x = a[0] - b[0];
		float y = a[1] - b[1];
		float z = a[2] - b[2];

		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	int Utils::VectorCmp(const void* a, const void* b)
	{
		vec3_t zero = { 0, 0, 0 };
		const VariableValue* ia = static_cast<const VariableValue*>(a);
		const VariableValue* ib = static_cast<const VariableValue*>(b);

		float distanceA = VectorDistance(const_cast<vec_t*>(ia->u.vectorValue), zero);
		float distanceB = VectorDistance(const_cast<vec_t*>(ib->u.vectorValue), zero);

		return static_cast<int>(distanceA - distanceB);
	}

	int Utils::FloatCmp(const void* a, const void* b)
	{
		const VariableValue* ia = static_cast<const VariableValue*>(a);
		const VariableValue* ib = static_cast<const VariableValue*>(b);

		return static_cast<int>(ia->u.floatValue - ib->u.floatValue);
	}

	int Utils::IntCmp(const void* a, const void* b)
	{
		const VariableValue* ia = static_cast<const VariableValue*>(a);
		const VariableValue* ib = static_cast<const VariableValue*>(b);

		return ia->u.intValue - ib->u.intValue;
	}

	int Utils::StringCmp(const void* a, const void* b)
	{
		const VariableValue* ia = static_cast<const VariableValue*>(a);
		const VariableValue* ib = static_cast<const VariableValue*>(b);

		const char* sia = Plugin_SL_ConvertToString(ia->u.stringValue);
		const char* sib = Plugin_SL_ConvertToString(ib->u.stringValue);

		return std::strcmp(sia, sib);
	}

	bool Utils::HasFlag(int var, int flag)
	{
		return (var & flag) == flag;
	}

	bool Utils::IsFlag(int var, int flag)
	{
		return var == flag;
	}
}
