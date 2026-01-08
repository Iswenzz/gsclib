#pragma once
#include "Base.hpp"

#include <unordered_map>

namespace gsclib
{
	class System
	{
	public:
		static inline std::unordered_map<std::string, bool> CriticalSections;

		static void Initialize();
		static void Execute();
		static void GetSysTime();
		static void Exit();
		static void ListCriticalSections();
		static void StatusCriticalSections();
		static void CreateCriticalSection();
		static void EnterCriticalSection();
		static void LeaveCriticalSection();
		static void AsyncStatus();
		static void AsyncCancel();
		static void IsWindows();
		static void IsLinux();
		static void CoD4XVersion();
		static void GSCLIBVersion();
		static void CURLVersion();
	};
}
