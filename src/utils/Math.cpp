#include "Math.hpp"

#include <cmath>

namespace gsclib
{
	void Math::Fmod()
	{
		CHECK_PARAMS(2, "Usage: fmod(<a>, <b>)\n");

		const float a = Plugin_Scr_GetFloat(0);
		const float b = Plugin_Scr_GetFloat(1);

		Plugin_Scr_AddFloat(std::fmod(a, b));
	}

	void Math::Tan()
	{
		CHECK_PARAMS(1, "Usage: tan1(<a>)\n");

		Plugin_Scr_AddFloat(std::tan(Plugin_Scr_GetFloat(0)));
	}

	void Math::Atan()
	{
		CHECK_PARAMS(1, "Usage: atan1(<a>)\n");

		Plugin_Scr_AddFloat(std::atan(Plugin_Scr_GetFloat(0)));
	}

	void Math::Atan2()
	{
		CHECK_PARAMS(2, "Usage: atan2(<a>, <b>)\n");

		const float a = Plugin_Scr_GetFloat(0);
		const float b = Plugin_Scr_GetFloat(1);

		Plugin_Scr_AddFloat(std::atan2(a, b));
	}

	void Math::Cos()
	{
		CHECK_PARAMS(1, "Usage: cos1(<a>)\n");

		Plugin_Scr_AddFloat(std::cos(Plugin_Scr_GetFloat(0)));
	}

	void Math::Acos()
	{
		CHECK_PARAMS(1, "Usage: acos1(<a>)\n");

		Plugin_Scr_AddFloat(std::acos(Plugin_Scr_GetFloat(0)));
	}

	void Math::Sin()
	{
		CHECK_PARAMS(1, "Usage: sin1(<a>)\n");

		Plugin_Scr_AddFloat(std::sin(Plugin_Scr_GetFloat(0)));
	}

	void Math::Asin()
	{
		CHECK_PARAMS(1, "Usage: asin1(<a>)\n");

		Plugin_Scr_AddFloat(std::asin(Plugin_Scr_GetFloat(0)));
	}
}
