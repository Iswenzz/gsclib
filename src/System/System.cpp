#include "System.hpp"

#include <curl/curl.h>
#include <cstdlib>

namespace gsclib
{
	void System::Initialize()
	{
		Plugin_Printf("^5[GSCLIB] Initialize\n");

		Async::Shutdown();
		Async::Initialize();
		CriticalSections.clear();
	}

	void System::Execute()
	{
		CHECK_PARAMS(1, "Usage: System(<command>)\n");
		Plugin_Scr_AddInt(std::system(Plugin_Scr_GetString(0)));
	}

	void System::GetSysTime()
	{
		CHECK_PARAMS(0, "Usage: GetSysTime()\n");
		Plugin_Scr_AddInt(Plugin_Milliseconds());
	}

	void System::Exit()
	{
		CHECK_PARAMS(1, "Usage: Exit(<code>)\n");
		std::exit(Plugin_Scr_GetInt(0));
	}

	void System::ListCriticalSections()
	{
		CHECK_PARAMS(0, "Usage: CriticalSections()\n");

		if (CriticalSections.empty())
			return;

		Plugin_Scr_MakeArray();
		for (const auto& [key, locked] : CriticalSections)
		{
			Plugin_Scr_AddBool(locked ? qtrue : qfalse);
			Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(key.c_str()));
		}
	}

	void System::StatusCriticalSections()
	{
		CHECK_PARAMS(0, "Usage: StatusCriticalSections()\n");

		if (CriticalSections.empty())
		{
			Plugin_Scr_AddBool(qtrue);
			return;
		}
		for (const auto& [key, locked] : CriticalSections)
		{
			if (locked)
			{
				Plugin_Scr_AddBool(qfalse);
				return;
			}
		}
		Plugin_Scr_AddBool(qtrue);
	}

	void System::CreateCriticalSection()
	{
		CHECK_PARAMS(1, "Usage: CriticalSection(<name>)\n");

		const char* name = Plugin_Scr_GetString(0);
		CriticalSections[name] = false;
	}

	void System::EnterCriticalSection()
	{
		CHECK_PARAMS(1, "Usage: EnterCriticalSection(<name>)\n");

		const char* name = Plugin_Scr_GetString(0);

		if (!CriticalSections.contains(name))
		{
			Plugin_Scr_Error(std::format("Section {} not found.\n", name).c_str());
			return;
		}
		if (!CriticalSections[name])
		{
			CriticalSections[name] = true;
			Plugin_Scr_AddBool(qtrue);
			return;
		}
		Plugin_Scr_AddBool(qfalse);
	}

	void System::LeaveCriticalSection()
	{
		CHECK_PARAMS(1, "Usage: LeaveCriticalSection(<name>)\n");

		const char* name = Plugin_Scr_GetString(0);

		if (!CriticalSections.contains(name))
		{
			Plugin_Scr_Error(std::format("Section {} not found.\n", name).c_str());
			return;
		}
		CriticalSections[name] = false;
	}

	void System::AsyncStatus()
	{
		CHECK_PARAMS(1, "Usage: AsyncStatus(<task>)\n");

		auto* task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_AddInt(static_cast<int>(AsyncStatus::Failure));
			return;
		}
		Plugin_Scr_AddInt(static_cast<int>(task->Status.load()));
	}

	void System::AsyncCancel()
	{
		CHECK_PARAMS(1, "Usage: AsyncCancel(<task>)\n");

		auto* task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		task->Cancel();
		Plugin_Scr_AddBool(qtrue);
	}

	void System::IsWindows()
	{
#ifdef _WIN32
		Plugin_Scr_AddBool(qtrue);
#else
		Plugin_Scr_AddBool(qfalse);
#endif
	}

	void System::IsLinux()
	{
#ifdef _WIN32
		Plugin_Scr_AddBool(qfalse);
#else
		Plugin_Scr_AddBool(qtrue);
#endif
	}

	void System::CoD4XVersion()
	{
		Plugin_Scr_AddString(Plugin_GetCommonVersionString());
	}

	void System::GSCLIBVersion()
	{
		Plugin_Scr_AddString(
			std::format("{}.{}.{}", GSCLIB_VERSION_MAJOR, GSCLIB_VERSION_MINOR, GSCLIB_VERSION_PATCH).c_str());
	}

	void System::CURLVersion()
	{
		CHECK_PARAMS(0, "Usage: CURL_Version()");

		curl_version_info_data* info = curl_version_info(CURLVERSION_NOW);
		if (!info)
			return;

		Plugin_Printf("^5----------[CURL INFO]----------\n");
		Plugin_Printf("^5Age: %d\nHost: %s\nSSH: %s\nSSL: %s\nVersion: %s\n", info->age, info->host, info->libssh_version,
			info->ssl_version, info->version);

		Plugin_Printf("^5Features: ");
		Plugin_Printf("%s", info->features & CURL_VERSION_IPV6 ? "IPv6 " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_SSL ? "SSL " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_LIBZ ? "LIBZ " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_NTLM ? "NTML " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_DEBUG ? "DEBUG " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_ASYNCHDNS ? "ASYNCHDNS " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_SPNEGO ? "SPNEGO " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_LARGEFILE ? "LARGEFILE " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_IDN ? "IDN " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_SSPI ? "SSPI " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_CONV ? "CONV " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_CURLDEBUG ? "CURLDEBUG " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_TLSAUTH_SRP ? "TLSAUTH_SRP " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_NTLM_WB ? "NTLM_WB " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_HTTP2 ? "HTTP2 " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_GSSAPI ? "GSSAPI " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_KERBEROS5 ? "KERBEROS5 " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_UNIX_SOCKETS ? "UNIX_SOCKETS " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_PSL ? "PSL " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_HTTPS_PROXY ? "HTTPS_PROXY " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_MULTI_SSL ? "MULTI_SSL " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_BROTLI ? "BROTLI " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_ALTSVC ? "ALTSVC " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_HTTP3 ? "HTTP3 " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_ZSTD ? "ZSTD " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_UNICODE ? "UNICODE " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_HSTS ? "HSTS " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_GSASL ? "GSASL " : "");
		Plugin_Printf("%s", info->features & CURL_VERSION_THREADSAFE ? "THREADSAFE " : "");
		Plugin_Printf("\n");

		Plugin_Printf("^5Protocols: ");
		for (int i = 0; info->protocols[i] != NULL; i++)
			Plugin_Printf("%s ", info->protocols[i]);
		Plugin_Printf("\n^5-------------------------------\n");

		Plugin_Scr_AddString(info->version);
	}
}
