#include "curl.h"
#include <stdlib.h>

CURLcode curl_library_init_code;
CURL_INSTANCE curl_instance = { NULL, 0, { 0 } };
FTP_INSTANCE ftp_instance = { NULL, { 0 }, { 0 }, 0};

i_curl_string i_string_init() 
{
	i_curl_string str;
	memset(&str, 0, sizeof(i_curl_string));
	str.buffer = NULL;
	return str;
}

void i_curl_setopts(CURL* curl)
{
	if (curl_instance.opt_count > 0)
	{
		for (int i = 0; i < curl_instance.opt_count; i++)
		{
			if (curl_instance.opts[i].param != NULL)
			{
				switch (curl_instance.opts[i].param->type)
				{
					case VAR_INTEGER:
						curl_easy_setopt(curl, curl_instance.opts[i].opt, curl_instance.opts[i].param->u.intValue);
						break;
					case VAR_FLOAT:
						curl_easy_setopt(curl, curl_instance.opts[i].opt, curl_instance.opts[i].param->u.floatValue);
						break;
					case VAR_ISTRING:
					case VAR_STRING:
						curl_easy_setopt(curl, curl_instance.opts[i].opt, 
							Plugin_SL_ConvertToString(curl_instance.opts[i].param->u.stringValue));
						break;
				}
			}
		}
	}
}

void i_curl_setheader(CURL* curl, CURLoption header_type)
{
	if (curl_instance.header != NULL)
		curl_easy_setopt(curl, header_type, curl_instance.header);
}

void i_curl_opt_cleanup()
{
	curl_instance.opt_count = 0;
	memset(&curl_instance.opts, 0, sizeof(curl_instance.opts));
}

void i_curl_header_cleanup()
{
	if (curl_instance.header != NULL)
	{
		curl_slist_free_all(curl_instance.header);
		curl_instance.header = NULL;
	}
}

qboolean i_curl_close()
{
	if (ftp_instance.curl != NULL)
	{
		curl_easy_cleanup(ftp_instance.curl);
		memset(&ftp_instance, 0, sizeof(ftp_instance));
		ftp_instance.curl = NULL;
		return qtrue;
	}
	return qfalse;
}

qboolean i_curl_connect(const char* protocol, const char* hostname, const char* username,
	const char* password, unsigned short port)
{
	i_curl_close();

	snprintf(ftp_instance.url, sizeof(ftp_instance.url), "%s://%s@%s/", protocol, username, hostname);
	strcpy(ftp_instance.password, password);
	ftp_instance.port = port;
	ftp_instance.curl = curl_easy_init();
	return ftp_instance.curl != NULL;
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
	i_curl_opt_cleanup();
}

void GScr_CURL_HeaderCleanup()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: CURL_HeaderCleanup()");
		return;
	}
	i_curl_header_cleanup();
}

void GScr_CURL_AddHeader()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: CURL_AddHeader(<header parse>)");
		return;
	}
	curl_instance.header = curl_slist_append(curl_instance.header, Plugin_Scr_GetString(0));
}

void GScr_CURL_AddOpt()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: CURL_AddOpt(<opt int>, <param generic>)");
		return;
	}
	curl_instance.opts[curl_instance.opt_count].opt = Plugin_Scr_GetInt(0);
	curl_instance.opts[curl_instance.opt_count].param = Plugin_Scr_AllocVariable(Plugin_Scr_SelectParam(1));
	curl_instance.opt_count++;
}
