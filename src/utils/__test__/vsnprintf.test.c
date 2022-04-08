#include "utils/vsnprintf.h"

#include <greatest.h>
#include <cgsc.h>

const char* Plugin_SL_ConvertToString(int index) { return "string"; }

TEST test_vsnprintf()
{
	char buffer[MAX_STRING_CHARS];
	const char* format = "%d %d";
	const int argCount = 2;

	VariableValue* args = (VariableValue*)malloc(argCount * sizeof(VariableValue));
	args[0].u.intValue = 1;
	args[1].u.intValue = 2;

	Scr_vsnprintf(buffer, sizeof(buffer), format, args);
	free(args);

	ASSERT_STR_EQ(buffer, "1 2");
	PASS();
}

SUITE(Suite_utils_vsnprintf)
{
	RUN_TEST(test_vsnprintf);
}
