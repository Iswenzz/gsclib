#include "curl.h"
#include <stdlib.h>

CURL_HANDLER curl_handler = { 0 };

void GScr_CURL_Init()
{
	CHECK_PARAMS(0, "Usage: CURL_Init()");

	CURL_REQUEST* curl = (CURL_REQUEST*)calloc(1, sizeof(CURL_REQUEST));
	curl->handle = curl_handler.handle;

	CURL_Working(qtrue);
	Plugin_Scr_AddInt((int)curl);
}

void GScr_CURL_Version()
{
	CHECK_PARAMS(0, "Usage: CURL_Version()");

	curl_version_info_data* info = curl_version_info(CURLVERSION_NOW);
	if (!info)
		return;

	Plugin_Printf("----------[CURL INFO]----------\n");
	Plugin_Printf("Age: %d\nHost: %s\nSSH: %s\nSSL: %s\nVersion: %s\n", info->age, info->host, info->libssh_version,
		info->ssl_version, info->version);

	Plugin_Printf("Features: ");
	Plugin_Printf("%s", info->features & CURL_VERSION_IPV6 ? "IPv6 " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_SSL ? "SSL " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_LIBZ ? "LIBZ " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_NTLM ? "NTML " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_DEBUG ? "Debug " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_ASYNCHDNS ? "AsyncHDNS " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_SPNEGO ? "SPNEGO " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_LARGEFILE ? "Largefile " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_IDN ? "IDN " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_SSPI ? "SSPI " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_CONV ? "CONV " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_CURLDEBUG ? "CURLDEBUG " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_TLSAUTH_SRP ? "TLSAUTH_SRP " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_NTLM_WB ? "NTLM_WB " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_HTTP2 ? "HTTP2 " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_GSSAPI ? "GSSAPI " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_KERBEROS5 ? "KERBEROS5 " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_UNIX_SOCKETS ? "Unix-Sockets " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_PSL ? "PSL " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_HTTPS_PROXY ? "HTTPS_PROXY " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_MULTI_SSL ? "MULTI_SSL " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_BROTLI ? "BROTLI " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_ALTSVC ? "ALTSVC " : "");
	Plugin_Printf("%s", info->features & CURL_VERSION_HTTP3 ? "HTTP3 " : "");
	Plugin_Printf("\n");

	Plugin_Printf("Protocols: ");
	for (int i = 0; info->protocols[i] != NULL; i++)
		Plugin_Printf("%s ", info->protocols[i]);
	Plugin_Printf("\n-------------------------------\n");

	Plugin_Scr_AddString(info->version);
}

void GScr_CURL_OptCleanup()
{
	CHECK_PARAMS(1, "Usage: CURL_OptCleanup(<request>)");

	CURL_REQUEST* curl = (CURL_REQUEST*)Plugin_Scr_GetInt(0);
	CHECK_CURL_REQUEST(curl);

	CURL_OptCleanup(curl);
}

void GScr_CURL_HeaderCleanup()
{
	CHECK_PARAMS(1, "Usage: CURL_HeaderCleanup(<request>)");

	CURL_REQUEST* curl = (CURL_REQUEST*)Plugin_Scr_GetInt(0);
	CHECK_CURL_REQUEST(curl);

	CURL_HeaderCleanup(curl);
}

void GScr_CURL_AddHeader()
{
	CHECK_PARAMS(2, "Usage: CURL_AddHeader(<request>, <header>)");

	CURL_REQUEST* curl = (CURL_REQUEST*)Plugin_Scr_GetInt(0);
	CHECK_CURL_REQUEST(curl);

	curl->header = curl_slist_append(curl->header, Plugin_Scr_GetString(1));
}

void GScr_CURL_AddOpt()
{
	CHECK_PARAMS(3, "Usage: CURL_AddOpt(<request>, <opt int>, <param generic>)");

	CURL_REQUEST* curl = (CURL_REQUEST*)Plugin_Scr_GetInt(0);
	CHECK_CURL_REQUEST(curl);

	curl->opts[curl->optsCount].opt = Plugin_Scr_GetInt(1);
	curl->opts[curl->optsCount].param = *Plugin_Scr_SelectParam(2);
	curl->optsCount++;
}

void GScr_CURL_Free()
{
	CHECK_PARAMS(1, "Usage: CURL_Free(<request>)");

	CURL_REQUEST* curl = (CURL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_CURL_REQUEST(curl);

	free(curl);

	CURL_Working(qfalse);
	Plugin_Scr_AddBool(qtrue);
}

void CURL_Working(qboolean state)
{
	curl_handler.working = state;
}

void CURL_SetHeader(CURL_REQUEST* curl, CURLoption headerType)
{
	if (curl->header != NULL)
		curl_easy_setopt(curl->handle, headerType, curl->header);
}

void CURL_OptCleanup(CURL_REQUEST* curl)
{
	curl->optsCount = 0;
	memset(&curl->opts, 0, sizeof(curl->opts));
}

void CURL_HeaderCleanup(CURL_REQUEST* curl)
{
	if (curl->header != NULL)
	{
		curl_slist_free_all(curl->header);
		curl->header = NULL;
	}
}

void CURL_SetOpts(CURL_REQUEST* curl)
{
	if (curl->optsCount > 0)
	{
		for (int i = 0; i < curl->optsCount; i++)
		{
			switch (curl->opts[i].param.type)
			{
			case VAR_INTEGER:
				curl_easy_setopt(curl->handle, curl->opts[i].opt, curl->opts[i].param.u.intValue);
				break;
			case VAR_FLOAT:
				curl_easy_setopt(curl->handle, curl->opts[i].opt, curl->opts[i].param.u.floatValue);
				break;
			case VAR_ISTRING:
			case VAR_STRING:
				curl_easy_setopt(curl->handle, curl->opts[i].opt,
					Plugin_SL_ConvertToString(curl->opts[i].param.u.stringValue));
				break;
			}
		}
	}
}
