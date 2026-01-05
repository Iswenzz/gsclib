#pragma once
#include "Base.hpp"

namespace gsclib
{
	class File
	{
	public:
		static void Create();
		static void Open();
		static void Exists();
		static void Seek();
		static void ReadLine();
		static void WriteLine();
		static void ReadLines();
		static void WriteLines();
		static void Read();
		static void Write();
		static void Delete();
		static void Close();
		static void MkDir();
		static void RmDir();
		static void ReadDir();
	};
}
