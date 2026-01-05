#pragma once
#include "Base.hpp"

namespace gsclib
{
	class Player
	{
	public:
		static void GetIP(scr_entref_t num);
		static void GetForwardMove(scr_entref_t num);
		static void GetRightMove(scr_entref_t num);
		static void GetJumpOrigin(scr_entref_t num);
		static void PmFlags(scr_entref_t num);
		static void SetPmFlags(scr_entref_t num);
		static void PmTime(scr_entref_t num);
		static void SetPmTime(scr_entref_t num);
		static void PmType(scr_entref_t num);
		static void WeaponFlags(scr_entref_t num);
	};
}
