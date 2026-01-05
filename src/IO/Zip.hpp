#pragma once
#include "Base.hpp"

namespace gsclib
{
	class Zip
	{
	public:
		static void Add();
		static void Rename();
		static void Delete();
		static void Open();
		static void Close();
	};
}
