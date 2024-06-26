#include "player.h"

void GScr_GetIP(scr_entref_t num)
{
	client_t* cl = Plugin_GetClientForClientNum(num);

	if (!cl)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	char ip[128];
	Plugin_NET_AdrToStringShortMT(&cl->netchan.remoteAddress, ip, sizeof(ip));
	Plugin_Scr_AddString(ip);
}

void GScr_GetForwardMove(scr_entref_t num)
{
	client_t* cl = Plugin_GetClientForClientNum(num);

	if (!cl)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	Plugin_Scr_AddInt((int)cl->lastUsercmd.forwardmove);
}

void GScr_GetRightMove(scr_entref_t num)
{
	client_t* cl = Plugin_GetClientForClientNum(num);

	if (!cl)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	Plugin_Scr_AddInt((int)cl->lastUsercmd.rightmove);
}

void GScr_GetJumpOrigin(scr_entref_t num)
{
	gentity_t* ent = Plugin_GetGentityForEntityNum(num);

	if (!ent || !ent->client)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	Plugin_Scr_AddInt(ent->client->ps.jumpOriginZ);
}

void GScr_PmFlags(scr_entref_t num)
{
	gentity_t* ent = Plugin_GetGentityForEntityNum(num);

	if (!ent || !ent->client)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	Plugin_Scr_AddInt(ent->client->ps.pm_flags);
}

void GScr_SetPmFlags(scr_entref_t num)
{
	CHECK_PARAMS(1, "Usage: SetPmFlags(<flags>)");

	gentity_t* ent = Plugin_GetGentityForEntityNum(num);
	int flags = Plugin_Scr_GetInt(0);

	if (!ent || !ent->client)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	ent->client->ps.pm_flags = flags;
}

void GScr_PmTime(scr_entref_t num)
{
	gentity_t* ent = Plugin_GetGentityForEntityNum(num);

	if (!ent || !ent->client)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	Plugin_Scr_AddInt(ent->client->ps.pm_time);
}

void GScr_SetPmTime(scr_entref_t num)
{
	CHECK_PARAMS(1, "Usage: SetPmTime(<time>)");

	gentity_t* ent = Plugin_GetGentityForEntityNum(num);
	int time = Plugin_Scr_GetInt(0);

	if (!ent || !ent->client)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	ent->client->ps.pm_time = time;
}

void GScr_PmType(scr_entref_t num)
{
	gentity_t* ent = Plugin_GetGentityForEntityNum(num);

	if (!ent || !ent->client)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	Plugin_Scr_AddInt(ent->client->ps.pm_type);
}

void GScr_WeaponFlags(scr_entref_t num)
{
	gentity_t* ent = Plugin_GetGentityForEntityNum(num);

	if (!ent || !ent->client)
	{
		Plugin_Scr_ObjectError("not a client\n");
		return;
	}
	Plugin_Scr_AddInt(ent->client->ps.weapFlags);
}
