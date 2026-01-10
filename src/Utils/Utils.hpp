#pragma once
#include "Base.hpp"

#define Q_COLOR_ESCAPE '^'
#define Q_IsColorString(p) (p && *(p) == Q_COLOR_ESCAPE && *((p) + 1) && *((p) + 1) != Q_COLOR_ESCAPE)

#define COLOR_BLACK '0'
#define COLOR_RED '1'
#define COLOR_GREEN '2'
#define COLOR_YELLOW '3'
#define COLOR_BLUE '4'
#define COLOR_CYAN '5'
#define COLOR_MAGENTA '6'
#define COLOR_WHITE '7'

#define ColorIndex(c) (((c) - '0') & 7)

namespace gsclib
{
	class Utils
	{
	public:
		static void ToInt();
		static void ToFloat();
		static void ToString();
		static void Ternary();
		static void IfUndef();
		static void GetType();

		static void IsStringAlpha();
		static void IsStringFloat();
		static void IsStringInt();
		static void IsNullOrEmpty();
		static void ToRGB();
		static void HexToRGB();
		static void ComPrint();
		static void ComPrintLn();
		static void SysPrint();
		static void SysPrintLn();
		static void Fmt();
		static void Trim();
		static void StartsWith();
		static void EndsWith();
		static void StrJoin();
		static void Replace();
		static void PathJoin();

		static float VectorDistance(const vec3_t a, const vec3_t b);
		static int VectorCmp(const void* a, const void* b);
		static int FloatCmp(const void* a, const void* b);
		static int IntCmp(const void* a, const void* b);
		static int StringCmp(const void* a, const void* b);

		static bool HasFlag(int var, int flag);
		static bool IsFlag(int var, int flag);

	private:
		static void SysPrintF(const char* format, ...);
		static void ScrPrintF(bool newLine, void (*print)(const char*, ...));
		static void AnsiColorPrint(const char* msg, void (*print)(const char*, ...));
	};
}
