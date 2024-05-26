#include "utils/vsnprintf.h"

#include <CGSC/cgsc.h>
#include <greatest.h>

TEST test_vsnprintf()
{
	char buffer[MAX_STRING_CHARS];
	const char* format = "%d %d";
	const int argCount = 2;

	VariableValueArray args = Plugin_Scr_CreateArray(argCount);
	args.items[0].type = VAR_INTEGER;
	args.items[0].u.intValue = 1;
	args.items[1].type = VAR_INTEGER;
	args.items[1].u.intValue = 2;

	Scr_vsnprintf(buffer, sizeof(buffer), format, args);
	Plugin_Scr_FreeArray(&args);

	ASSERT_STR_EQ(buffer, "1 2");
	PASS();
}

SUITE(Suite_utils_vsnprintf)
{
	RUN_TEST(test_vsnprintf);
}
