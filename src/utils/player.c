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
