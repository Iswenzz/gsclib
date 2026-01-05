
#include "System.hpp"

#include "Network/FTP.hpp"
#include "Network/HTTP.hpp"
#include "Network/MySQL.hpp"

#include <cstdlib>

namespace gsclib
{
	void System::Initialize()
	{
		Plugin_Printf("[GSCLIB] Initialize\n");

		Async::Shutdown();
		Async::Initialize();

		CriticalSections.clear();

		Ftp::Working = false;
		Http::Working = false;
		MySql::Working = false;
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

	void System::CriticalSectionCreate()
	{
		CHECK_PARAMS(1, "Usage: CriticalSection(<name>)\n");

		const char* name = Plugin_Scr_GetString(0);
		CriticalSections[name] = false;
	}

	void System::CriticalSectionList()
	{
		CHECK_PARAMS(0, "Usage: CriticalSections()\n");

		if (CriticalSections.empty())
			return;

		Plugin_Scr_MakeArray();
		for (const auto& [key, locked] : CriticalSections)
		{
			Plugin_Scr_AddInt(locked ? 1 : 0);
			Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(key.c_str()));
		}
	}

	void System::EnterCriticalSection()
	{
		CHECK_PARAMS(1, "Usage: EnterCriticalSection(<name>)\n");

		const char* name = Plugin_Scr_GetString(0);

		if (!CriticalSections.contains(name))
		{
			Plugin_Scr_Error(std::format("EnterCriticalSection(): section {} not found.\n", name).c_str());
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
			Plugin_Scr_Error(std::format("LeaveCriticalSection(): section {} not found.\n", name).c_str());
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
		Plugin_Scr_AddString(std::format("{}.{}", GSCLIB_VERSION_MAJOR, GSCLIB_VERSION_MINOR).c_str());
	}
}
