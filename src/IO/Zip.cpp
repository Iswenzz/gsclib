#include "Zip.hpp"

#include <libzippp.h>
#include <zip.h>
#include <filesystem>

namespace gsclib
{
	void Zip::Add()
	{
		CHECK_PARAMS(3, "Usage: ZIP_Add(<zip>, <filepath>, <outpath>)\n");

		auto* zip = reinterpret_cast<libzippp::ZipArchive*>(Plugin_Scr_GetInt(0));
		const char* filepath = Plugin_Scr_GetString(1);
		const char* outpath = Plugin_Scr_GetString(2);

		if (!std::filesystem::exists(filepath))
		{
			Plugin_Scr_Error(std::format("File does not exists {}\n", filepath).c_str());
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		if (!zip->addFile(outpath, filepath))
		{
			Plugin_Scr_Error(std::format("Failed to add file {}\n", filepath).c_str());
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		Plugin_Scr_AddBool(qtrue);
	}

	void Zip::Rename()
	{
		CHECK_PARAMS(3, "Usage: ZIP_Rename(<zip>, <filepath>, <renamepath>)\n");

		auto* zip = reinterpret_cast<libzippp::ZipArchive*>(Plugin_Scr_GetInt(0));
		const char* filepath = Plugin_Scr_GetString(1);
		const char* renamepath = Plugin_Scr_GetString(2);

		int index = zip_name_locate(zip->getZipHandle(), filepath, ZIP_FL_ENC_GUESS);
		if (index == -1)
		{
			Plugin_Scr_Error(std::format("File not found in the archive {}\n", filepath).c_str());
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		if (zip_file_rename(zip->getZipHandle(), index, renamepath, ZIP_FL_ENC_GUESS) < 0)
		{
			Plugin_Scr_Error(std::format("Failed to rename file {}\n", filepath).c_str());
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		Plugin_Scr_AddBool(qtrue);
	}

	void Zip::Delete()
	{
		CHECK_PARAMS(2, "Usage: ZIP_Delete(<zip>, <filepath>)\n");

		auto* zip = reinterpret_cast<libzippp::ZipArchive*>(Plugin_Scr_GetInt(0));
		const char* filepath = Plugin_Scr_GetString(1);

		libzippp::ZipEntry entry = zip->getEntry(filepath);
		if (entry.isNull())
		{
			Plugin_Scr_Error(std::format("File not found in the archive {}\n", filepath).c_str());
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		if (zip->deleteEntry(entry) < 1)
		{
			Plugin_Scr_Error(std::format("Failed to delete file {}\n", filepath).c_str());
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		Plugin_Scr_AddBool(qtrue);
	}

	void Zip::Open()
	{
		CHECK_PARAMS(1, "Usage: ZIP_Open(<filepath>)\n");

		const char* filepath = Plugin_Scr_GetString(0);
		auto mode = std::filesystem::exists(filepath) ? libzippp::ZipArchive::Write : libzippp::ZipArchive::New;
		auto* zip = new libzippp::ZipArchive(filepath);

		if (!zip->open(mode))
		{
			delete zip;
			Plugin_Scr_Error(std::format("Failed to open file {}\n", filepath).c_str());
			Plugin_Scr_AddInt(0);
			return;
		}
		Plugin_Scr_AddInt(reinterpret_cast<uintptr_t>(zip));
	}

	void Zip::Close()
	{
		CHECK_PARAMS(1, "Usage: ZIP_Close(<zip>)\n");

		auto* zip = reinterpret_cast<libzippp::ZipArchive*>(Plugin_Scr_GetInt(0));
		if (!zip)
		{
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		zip->close();
		delete zip;
		Plugin_Scr_AddBool(qtrue);
	}
}
