#include "math.h"
#include <math.h>

void GScr_fmod()
{
	CHECK_PARAMS(2, "Usage: fmod(<a>, <b>)");

	const float a = Plugin_Scr_GetFloat(0);
	const float b = Plugin_Scr_GetFloat(1);

	Plugin_Scr_AddFloat(fmod(a, b));
}

void GScr_tan1()
{
	CHECK_PARAMS(1, "Usage: tan1(<a>)");

	Plugin_Scr_AddFloat(tanf(Plugin_Scr_GetFloat(0)));
}

void GScr_atan1()
{
	CHECK_PARAMS(1, "Usage: atan1(<a>)");

	Plugin_Scr_AddFloat(atanf(Plugin_Scr_GetFloat(0)));
}

void GScr_atan2()
{
	CHECK_PARAMS(2, "Usage: atan2(<a>, <b>)");

	const float a = Plugin_Scr_GetFloat(0);
	const float b = Plugin_Scr_GetFloat(1);

	Plugin_Scr_AddFloat(atan2f(a, b));
}

void GScr_cos1()
{
	CHECK_PARAMS(1, "Usage: cos1(<a>)");

	Plugin_Scr_AddFloat(cos(Plugin_Scr_GetFloat(0)));
}

void GScr_acos1()
{
	CHECK_PARAMS(1, "Usage: acos1(<a>)");

	Plugin_Scr_AddFloat(acos(Plugin_Scr_GetFloat(0)));
}

void GScr_sin1()
{
	CHECK_PARAMS(1, "Usage: sin1(<a>)");

	Plugin_Scr_AddFloat(sin(Plugin_Scr_GetFloat(0)));
}

void GScr_asin1()
{
	CHECK_PARAMS(1, "Usage: asin1(<a>)");

	Plugin_Scr_AddFloat(asin(Plugin_Scr_GetFloat(0)));
}
