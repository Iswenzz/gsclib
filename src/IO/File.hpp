#pragma once
#include "Base.hpp"

namespace gsclib
{
	class File
	{
	public:
		static void Create();
		static void Open();
		static void Close();
		static void Exists();
		static void ReadLine();
		static void WriteLine();
		static void ReadLines();
		static void WriteLines();
		static void Read();
		static void Write();
		static void Seek();
		static void Delete();
		static void MkDir();
		static void RmDir();
		static void ReadDir();
	};
}
