#include "curl.h"
#include <stdlib.h>

CURLcode CURLinitCode;
CURLinstance curl = { NULL, 0, { 0 } };
FTPinstance ftp = { NULL, { 0 }, { 0 }, 0};

CURLstring CURL_StringInit() 
{
	CURLstring str;
	memset(&str, 0, sizeof(CURLstring));
	str.buffer = NULL;
	return str;
}

void CURL_SetHeader(CURL* handle, CURLoption headerType)
{
	if (curl.header != NULL)
		curl_easy_setopt(handle, headerType, curl.header);
}

void CURL_OptCleanup()
{
	curl.optsCount = 0;
	memset(&curl.opts, 0, sizeof(curl.opts));
}

void CURL_HeaderCleanup()
{
	if (curl.header != NULL)
	{
		curl_slist_free_all(curl.header);
		curl.header = NULL;
	}
}

void CURL_SetOpts(CURL* handle)
{
	if (curl.optsCount > 0)
	{
		for (int i = 0; i < curl.optsCount; i++)
		{
			if (curl.opts[i].param != NULL)
			{
				switch (curl.opts[i].param->type)
				{
				case VAR_INTEGER:
					curl_easy_setopt(handle, curl.opts[i].opt, curl.opts[i].param->u.intValue);
					break;
				case VAR_FLOAT:
					curl_easy_setopt(handle, curl.opts[i].opt, curl.opts[i].param->u.floatValue);
					break;
				case VAR_ISTRING:
				case VAR_STRING:
					curl_easy_setopt(handle, curl.opts[i].opt,
						Plugin_SL_ConvertToString(curl.opts[i].param->u.stringValue));
					break;
				}
			}
		}
	}
}

qboolean CURL_FTP_Close()
{
	if (ftp.handle != NULL)
	{
		curl_easy_cleanup(ftp.handle);
		memset(&ftp, 0, sizeof(ftp));
		ftp.handle = NULL;
		return qtrue;
	}
	return qfalse;
}

qboolean CURL_FTP_Connect(const char* protocol, const char* hostname, const char* username,
	const char* password, unsigned short port)
{
	CURL_FTP_Close();

	snprintf(ftp.url, sizeof(ftp.url), "%s://%s@%s/", protocol, username, hostname);
	strcpy(ftp.password, password);
	ftp.port = port;
	ftp.handle = curl_easy_init();
	return ftp.handle != NULL;
}

void GScr_CURL_Version()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: CURL_Version()");
		return;
	}
	curl_version_info_data* info = curl_version_info(CURLVERSION_NOW);

	if (info != NULL)
	{
		Plugin_Printf("----------[CURL INFO]----------\n");
		Plugin_Printf("Age: %d\nHost: %s\nSSH: %s\nSSL: %s\nVersion: %s\n",
			info->age, info->host, info->libssh_version, info->ssl_version, info->version);

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
	else
		Plugin_Scr_AddUndefined();
}

void GScr_CURL_OptCleanup()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: CURL_OptCleanup()");
		return;
	}
	CURL_OptCleanup();
}

void GScr_CURL_HeaderCleanup()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: CURL_HeaderCleanup()");
		return;
	}
	CURL_HeaderCleanup();
}

void GScr_CURL_AddHeader()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: CURL_AddHeader(<header parse>)");
		return;
	}
	curl.header = curl_slist_append(curl.header, Plugin_Scr_GetString(0));
}

void GScr_CURL_AddOpt()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: CURL_AddOpt(<opt int>, <param generic>)");
		return;
	}
	curl.opts[curl.optsCount].opt = Plugin_Scr_GetInt(0);
	curl.opts[curl.optsCount].param = Plugin_Scr_AllocVariable(Plugin_Scr_SelectParam(1));
	curl.optsCount++;
}
