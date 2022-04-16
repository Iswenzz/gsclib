#include "zip.h"

void GScr_ZIP_Add()
{
	CHECK_PARAMS(3, "Usage: ZIP_Add(<zip>, <filepath>, <outpath>)");

	zip_t* zip = (zip_t*)Plugin_Scr_GetInt(0);
	const char* filepath = Plugin_Scr_GetString(1);
	const char* outpath = Plugin_Scr_GetString(2);

	Plugin_Scr_AddBool(ZIP_Add(zip, filepath, outpath));
}

void GScr_ZIP_Rename()
{
	CHECK_PARAMS(3, "Usage: ZIP_Rename(<zip>, <filepath>, <renamepath>)");

	zip_t* zip = (zip_t*)Plugin_Scr_GetInt(0);
	const char* filepath = Plugin_Scr_GetString(1);
	const char* renamepath = Plugin_Scr_GetString(2);

	Plugin_Scr_AddBool(ZIP_Rename(zip, filepath, renamepath));
}

void GScr_ZIP_Delete()
{
	CHECK_PARAMS(2, "Usage: ZIP_Delete(<zip>, <filepath>)");

	zip_t* zip = (zip_t*)Plugin_Scr_GetInt(0);
	const char* filepath = Plugin_Scr_GetString(1);

	Plugin_Scr_AddBool(ZIP_Delete(zip, filepath));
}

void GScr_ZIP_Open()
{
	CHECK_PARAMS(1, "Usage: ZIP_Open(<filepath>)");

	const char* filepath = Plugin_Scr_GetString(0);
	Plugin_Scr_AddInt((int)ZIP_Open(filepath));
}

void GScr_ZIP_Close()
{
	CHECK_PARAMS(1, "Usage: ZIP_Close(<zip>)");

	zip_t* zip = (zip_t*)Plugin_Scr_GetInt(0);
	Plugin_Scr_AddBool(ZIP_Close(zip));
}

qboolean ZIP_Add(zip_t* zip, const char* filepath, const char* outpath)
{
	struct stat fileinfo;
	if (stat(filepath, &fileinfo))
	{
		Plugin_Scr_Error(fmt("File does not exists: %s", filepath));
		return qfalse;
	}

	zip_source_t* source = zip_source_file(zip, filepath, 0, 0);
	if (!source)
	{
		Plugin_Scr_Error(fmt("Failed to add file %s: %s", filepath, zip_strerror(zip)));
		return qfalse;
	}
	if (zip_file_add(zip, outpath, source, ZIP_FL_OVERWRITE) < 0)
	{
		zip_source_free(source);
		Plugin_Scr_Error(fmt("Failed to add file %s: %s", filepath, zip_strerror(zip)));
		return qfalse;
	}
	return qtrue;
}

qboolean ZIP_Rename(zip_t* zip, const char* filepath, const char* renamepath)
{
	int index = zip_name_locate(zip, filepath, ZIP_FL_ENC_GUESS);
	if (index == -1)
	{
		Plugin_Scr_Error(fmt("File not found in the archive %s", filepath));
		return qfalse;
	}
	if (zip_file_rename(zip, index, renamepath, ZIP_FL_ENC_GUESS) < 0)
	{
		Plugin_Scr_Error(fmt("Failed to rename file %s: %s", filepath, zip_strerror(zip)));
		return qfalse;
	}
	return qtrue;
}

qboolean ZIP_Delete(zip_t* zip, const char* filepath)
{
	int index = zip_name_locate(zip, filepath, ZIP_FL_ENC_GUESS);
	if (index == -1)
	{
		Plugin_Scr_Error(fmt("File not found in the archive %s", filepath));
		return qfalse;
	}
	if (zip_delete(zip, index) < 0)
	{
		Plugin_Scr_Error(fmt("Failed to delete file %s: %s", filepath, zip_strerror(zip)));
		return qfalse;
	}
	return qtrue;
}

zip_t* ZIP_Open(const char* path)
{
	int error;
	struct stat fileinfo;
	int flags = stat(path, &fileinfo) ? ZIP_CREATE : 0;

	zip_t* zip = zip_open(path, flags, &error);
	if (!zip)
	{
		zip_error_t ziperror;
		zip_error_init_with_code(&ziperror, error);
		Plugin_Scr_Error(fmt("Failed to open file %s: %s", path, zip_error_strerror(&ziperror)));
		return NULL;
	}
	return zip;
}

qboolean ZIP_Close(zip_t* zip)
{
	if (zip)
		return zip_close(zip) == 0;
	return qfalse;
}
