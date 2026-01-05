#include "File.hpp"
#include "Utils/Print.hpp"

#include <filesystem>
#include <fstream>

namespace gsclib
{
	void File::Create()
	{
		CHECK_PARAMS(1, "Usage: FILE_Create(<path>)\n");

		const char* path = Plugin_Scr_GetString(0);
		std::ofstream file(path);
		Plugin_Scr_AddBool(static_cast<qboolean>(file.good()));
	}

	void File::Open()
	{
		CHECK_PARAMS(2, "Usage: FILE_Open(<path>, <mode>)\n");

		const char* path = Plugin_Scr_GetString(0);
		const char* mode = Plugin_Scr_GetString(1);

		std::ios_base::openmode openMode = std::ios::in | std::ios::out;
		for (const char* m = mode; *m; m++)
		{
			switch (*m)
			{
			case 'r':
				openMode |= std::ios::in;
				break;
			case 'w':
				openMode |= std::ios::out | std::ios::trunc;
				break;
			case 'a':
				openMode |= std::ios::out | std::ios::app;
				break;
			case 'b':
				openMode |= std::ios::binary;
				break;
			case '+':
				openMode |= std::ios::in | std::ios::out;
				break;
			}
		}
		auto* file = new std::fstream(path, openMode);

		if (!file->is_open())
		{
			delete file;
			Plugin_Scr_Error(std::format("Couldn't open file {}\n", path).c_str());
			return;
		}
		Plugin_Scr_AddInt(reinterpret_cast<uintptr_t>(file));
	}

	void File::Exists()
	{
		CHECK_PARAMS(1, "Usage: FILE_Exists(<path>)\n");

		const char* path = Plugin_Scr_GetString(0);
		Plugin_Scr_AddBool(static_cast<qboolean>(std::filesystem::exists(path)));
	}

	void File::ReadLine()
	{
		CHECK_PARAMS(1, "Usage: FILE_ReadLine(<file>)\n");

		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));

		if (!file)
		{
			Plugin_Scr_Error("File handle is NULL\n");
			return;
		}
		std::string buffer;
		std::getline(*file, buffer);
		Plugin_Scr_AddString(buffer.c_str());
	}

	void File::WriteLine()
	{
		const int argCount = Plugin_Scr_GetNumParam();

		if (argCount < 2)
		{
			Plugin_Scr_Error("Usage: FILE_Write(<file>, <string>, <?arguments...>)\n");
			return;
		}
		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));
		const char* format = Plugin_Scr_GetString(1);
		std::string buffer = format;

		if (!file)
		{
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		if (argCount > 2)
		{
			VariableValueArray args = Plugin_Scr_CreateArray(argCount - 2);

			for (int i = 2; i < argCount; i++)
				args.items[i - 2] = *Plugin_Scr_SelectParam(i);
			buffer = Print::Format(format, args);
			Plugin_Scr_FreeArray(&args);
		}
		*file << buffer << '\n';
		file->flush();
		Plugin_Scr_AddBool(static_cast<qboolean>(file->good()));
	}

	void File::ReadLines()
	{
		CHECK_PARAMS(1, "Usage: FILE_ReadLines(<file>)\n");

		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));

		if (!file)
		{
			Plugin_Scr_Error("File handle is NULL\n");
			return;
		}
		std::string buffer;
		Plugin_Scr_MakeArray();

		while (std::getline(*file, buffer))
		{
			Plugin_Scr_AddString(buffer.c_str());
			Plugin_Scr_AddArray();
		}
	}

	void File::WriteLines()
	{
		CHECK_PARAMS(2, "Usage: FILE_WriteLines(<file>, <lines>)\n");

		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));
		VariableValueArray array = Plugin_Scr_GetArray(1);
		int lines = 0;

		for (int i = 0; i < array.length; i++)
		{
			if (array.items[i].type == VAR_STRING)
			{
				*file << Plugin_SL_ConvertToString(array.items[i].u.stringValue) << '\n';
				lines++;
			}
		}
		Plugin_Scr_AddInt(lines);
		Plugin_Scr_FreeArray(&array);
	}

	void File::Seek()
	{
		CHECK_PARAMS(2, "Usage: FILE_Seek(<file>, <offset>)\n");

		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));
		int offset = Plugin_Scr_GetInt(1);

		if (!file)
		{
			Plugin_Scr_Error("File handle is NULL\n");
			return;
		}
		file->seekg(offset, std::ios::beg);
		file->seekp(offset, std::ios::beg);
		Plugin_Scr_AddBool(static_cast<qboolean>(file->good()));
	}

	void File::Read()
	{
		CHECK_PARAMS(1, "Usage: FILE_Read(<file>)\n");

		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));

		if (!file)
		{
			Plugin_Scr_Error("File handle is NULL\n");
			return;
		}
		std::string buffer((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
		Plugin_Scr_AddString(buffer.c_str());
	}

	void File::Write()
	{
		const int argCount = Plugin_Scr_GetNumParam();

		if (argCount < 2)
		{
			Plugin_Scr_Error("Usage: FILE_Write(<file>, <string>, <?arguments...>)\n");
			return;
		}
		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));
		const char* format = Plugin_Scr_GetString(1);
		std::string buffer = format;

		if (!file)
		{
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		if (argCount > 2)
		{
			VariableValueArray args;
			args.length = argCount - 2;
			args.items = new VariableValue[args.length];

			for (int i = 2; i < argCount; i++)
				args.items[i - 2] = *Plugin_Scr_SelectParam(i);
			buffer = Print::Format(format, args);
			Plugin_Scr_FreeArray(&args);
		}
		*file << buffer;
		file->flush();
		Plugin_Scr_AddBool(static_cast<qboolean>(file->good()));
	}

	void File::Delete()
	{
		CHECK_PARAMS(1, "Usage: FILE_Delete(<path>)\n");

		const char* path = Plugin_Scr_GetString(0);
		Plugin_Scr_AddBool(static_cast<qboolean>(std::filesystem::remove(path)));
	}

	void File::Close()
	{
		CHECK_PARAMS(1, "Usage: FILE_Close(<file>)\n");

		auto* file = reinterpret_cast<std::fstream*>(Plugin_Scr_GetInt(0));
		if (!file)
		{
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		file->close();
		Plugin_Scr_AddBool(static_cast<qboolean>(!file->fail()));
		delete file;
	}

	void File::MkDir()
	{
		CHECK_PARAMS(1, "Usage: FILE_MkDir(<path>)\n");
		const char* path = Plugin_Scr_GetString(0);

		Plugin_Scr_AddBool(static_cast<qboolean>(std::filesystem::create_directory(path)));
	}

	void File::RmDir()
	{
		CHECK_PARAMS(1, "Usage: FILE_RmDir(<path>)\n");
		const char* path = Plugin_Scr_GetString(0);

		Plugin_Scr_AddBool(static_cast<qboolean>(std::filesystem::remove_all(path)));
	}

	void File::ReadDir()
	{
		CHECK_PARAMS(1, "Usage: FILE_ReadDir(<path>)\n");

		const char* path = Plugin_Scr_GetString(0);

		if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
		{
			Plugin_Scr_Error(std::format("Couldn't open dir {}\n", path).c_str());
			return;
		}
		Plugin_Scr_MakeArray();
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			Plugin_Scr_AddString(entry.path().filename().string().c_str());
			Plugin_Scr_AddArray();
		}
	}
}
