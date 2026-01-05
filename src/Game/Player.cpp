#include "Player.hpp"

namespace gsclib
{
	void Player::GetIP(scr_entref_t num)
	{
		client_t* cl = Plugin_GetClientForClientNum(num);

		if (!cl)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		char ip[128];
		Plugin_NET_AdrToStringShortMT(&cl->netchan.remoteAddress, ip, sizeof(ip));
		Plugin_Scr_AddString(ip);
	}

	void Player::GetForwardMove(scr_entref_t num)
	{
		client_t* cl = Plugin_GetClientForClientNum(num);

		if (!cl)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		Plugin_Scr_AddInt(static_cast<int>(cl->lastUsercmd.forwardmove));
	}

	void Player::GetRightMove(scr_entref_t num)
	{
		client_t* cl = Plugin_GetClientForClientNum(num);

		if (!cl)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		Plugin_Scr_AddInt(static_cast<int>(cl->lastUsercmd.rightmove));
	}

	void Player::GetJumpOrigin(scr_entref_t num)
	{
		gentity_t* ent = Plugin_GetGentityForEntityNum(num);

		if (!ent || !ent->client)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		Plugin_Scr_AddInt(ent->client->ps.jumpOriginZ);
	}

	void Player::PmFlags(scr_entref_t num)
	{
		gentity_t* ent = Plugin_GetGentityForEntityNum(num);

		if (!ent || !ent->client)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		Plugin_Scr_AddInt(ent->client->ps.pm_flags);
	}

	void Player::SetPmFlags(scr_entref_t num)
	{
		CHECK_PARAMS(1, "Usage: SetPmFlags(<flags>)\n");

		gentity_t* ent = Plugin_GetGentityForEntityNum(num);
		int flags = Plugin_Scr_GetInt(0);

		if (!ent || !ent->client)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		ent->client->ps.pm_flags = flags;
	}

	void Player::PmTime(scr_entref_t num)
	{
		gentity_t* ent = Plugin_GetGentityForEntityNum(num);

		if (!ent || !ent->client)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		Plugin_Scr_AddInt(ent->client->ps.pm_time);
	}

	void Player::SetPmTime(scr_entref_t num)
	{
		CHECK_PARAMS(1, "Usage: SetPmTime(<time>)\n");

		gentity_t* ent = Plugin_GetGentityForEntityNum(num);
		int time = Plugin_Scr_GetInt(0);

		if (!ent || !ent->client)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		ent->client->ps.pm_time = time;
	}

	void Player::PmType(scr_entref_t num)
	{
		gentity_t* ent = Plugin_GetGentityForEntityNum(num);

		if (!ent || !ent->client)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		Plugin_Scr_AddInt(ent->client->ps.pm_type);
	}

	void Player::WeaponFlags(scr_entref_t num)
	{
		gentity_t* ent = Plugin_GetGentityForEntityNum(num);

		if (!ent || !ent->client)
		{
			Plugin_Scr_ObjectError("Not a client\n");
			return;
		}
		Plugin_Scr_AddInt(ent->client->ps.weapFlags);
	}
}
