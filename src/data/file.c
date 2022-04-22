#include "file.h"
#include "utils/vsnprintf.h"

#include <cgsc.h>
#include <stdlib.h>

void GScr_FILE_Create()
{
	CHECK_PARAMS(1, "Usage: FILE_Create(<path>)");

	const char* path = Plugin_Scr_GetString(0);

	FILE* file = fopen(path, "w");
	Plugin_Scr_AddBool(file ? fclose(file) == 0 : qfalse);
}

void GScr_FILE_Open()
{
	CHECK_PARAMS(2, "Usage: FILE_Open(<path>, <mode>)");

	const char* path = Plugin_Scr_GetString(0);
	const char* mode = Plugin_Scr_GetString(1);

	FILE* file = fopen(path, mode);
	if (!file)
	{
		Plugin_Scr_Error(fmt("Error: Couldn't open file %s", path));
		return;
	}
	Plugin_Scr_AddInt((int)file);
}

void GScr_FILE_Exists()
{
	CHECK_PARAMS(1, "Usage: FILE_Exists(<path>)");

	struct stat fileinfo;
	const char* path = Plugin_Scr_GetString(0);
	
	Plugin_Scr_AddBool(stat(path, &fileinfo) == 0);
}

void GScr_FILE_ReadLine()
{
	CHECK_PARAMS(1, "Usage: FILE_ReadLine(<file>)");

	char buffer[MAX_STRING_CHARS] = { 0 };
	FILE* file = (FILE*)Plugin_Scr_GetInt(0);

	if (!file)
	{
		Plugin_Scr_Error("Error: File handle is NULL");
		return;
	}
	fgets(buffer, sizeof(buffer), file);
	buffer[strcspn(buffer, "\n")] = 0;
	Plugin_Scr_AddString(buffer);
}

void GScr_FILE_WriteLine()
{
	const int argCount = Plugin_Scr_GetNumParam();
	if (argCount < 2)
	{
		Plugin_Scr_Error("Usage: FILE_Write(<file>, <string>, <?arguments...>)");
		return;
	}
	char buffer[MAX_STRING_CHARS] = { 0 };
	FILE* file = (FILE*)Plugin_Scr_GetInt(0);
	const char* format = Plugin_Scr_GetString(1);

	if (!file)
	{
		Plugin_Scr_AddBool(qfalse);
		return;
	}
	if (argCount > 2)
	{
		VariableValue* args = (VariableValue*)malloc((argCount - 2) * sizeof(VariableValue));

		for (int i = 2; i < argCount; i++)
			args[i - 2] = *Plugin_Scr_SelectParam(i);
		Scr_vsnprintf(buffer, sizeof(buffer), format, args);
		free(args);
	}
	else
		strcpy(buffer, format);

	int code = fprintf(file, "%s\n", buffer);
	fflush(file);
	Plugin_Scr_AddBool(code != EOF);
}

void GScr_FILE_Seek()
{
	CHECK_PARAMS(2, "Usage: FILE_Seek(<file>, <offset>)");

	FILE* file = (FILE*)Plugin_Scr_GetInt(0);
	int offset = Plugin_Scr_GetInt(1);

	if (!file)
	{
		Plugin_Scr_Error("Error: File handle is NULL");
		return;
	}
	Plugin_Scr_AddBool(fseek(file, offset, SEEK_SET) == 0);
}

void GScr_FILE_Read()
{
	CHECK_PARAMS(1, "Usage: FILE_Read(<file>)");

	char buffer[MAX_STRING_CHARS] = { 0 };
	FILE* file = (FILE*)Plugin_Scr_GetInt(0);

	if (!file)
	{
		Plugin_Scr_Error("Error: File handle is NULL");
		return;
	}
	fread(buffer, sizeof(buffer), 1, file);
	Plugin_Scr_AddString(buffer);
}

void GScr_FILE_Write()
{
	const int argCount = Plugin_Scr_GetNumParam();
	if (argCount < 2)
	{
		Plugin_Scr_Error("Usage: FILE_Write(<file>, <string>, <?arguments...>)");
		return;
	}
	char buffer[MAX_STRING_CHARS] = { 0 };
	FILE* file = (FILE*)Plugin_Scr_GetInt(0);
	const char* format = Plugin_Scr_GetString(1);

	if (!file)
	{
		Plugin_Scr_AddBool(qfalse);
		return;
	}
	if (argCount > 2)
	{
		VariableValue* args = (VariableValue*)malloc((argCount - 2) * sizeof(VariableValue));

		for (int i = 2; i < argCount; i++)
			args[i - 2] = *Plugin_Scr_SelectParam(i);
		Scr_vsnprintf(buffer, sizeof(buffer), format, args);
		free(args);
	}
	else
		strcpy(buffer, format);

	int code = fputs(buffer, file);
	fflush(file);
	Plugin_Scr_AddBool(code != EOF);
}

void GScr_FILE_Delete()
{
	CHECK_PARAMS(1, "Usage: FILE_Delete(<path>)");

	const char* path = Plugin_Scr_GetString(0);
	Plugin_Scr_AddBool(remove(path) == 0);
}

void GScr_FILE_Close()
{
	CHECK_PARAMS(1, "Usage: FILE_Close(<file>)");

	FILE* file = (FILE*)Plugin_Scr_GetInt(0);
	Plugin_Scr_AddBool(file ? fclose(file) == 0 : qfalse);
}

void GScr_FILE_MkDir()
{
	CHECK_PARAMS(1, "Usage: FILE_MkDir(<path>)");
	const char* path = Plugin_Scr_GetString(0);
	
#ifdef _WIN32
	Plugin_Scr_AddBool(CreateDirectory(path, NULL));
#else
	Plugin_Scr_AddBool(mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0);
#endif
}

void GScr_FILE_RmDir()
{
	CHECK_PARAMS(1, "Usage: FILE_RmDir(<path>)");
	const char* path = Plugin_Scr_GetString(0);

#ifdef _WIN32
	Plugin_Scr_AddBool(WIN_RemoveDirectory(path) == 0);
#else
	Plugin_Scr_AddBool(nftw(path, UNIX_RemoveEntry, 64, FTW_DEPTH | FTW_PHYS) == 0);
#endif
}

void GScr_FILE_ReadDir()
{
	CHECK_PARAMS(1, "Usage: FILE_ReadDir(<path>)");

	const char* path = Plugin_Scr_GetString(0);
	DIR* dir = opendir(path);
	struct dirent* entry;

	if (!dir)
	{
		Plugin_Scr_Error(fmt("Error: Couldn't open dir %s", path));
		return;
	}

	Plugin_Scr_MakeArray();
	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		Plugin_Scr_AddString(entry->d_name);
		Plugin_Scr_AddArray();
	}
	closedir(dir);
}

#ifdef _WIN32
BOOL WIN_RemoveDirectory(const char* path)
{
	// Required to set 2 nulls at end of argument to SHFileOperation.
	int len = strlen(path) + 2;
	char* tempdir = (char*)malloc(len);
	memset(tempdir, 0, len);
	strcpy(tempdir, path);

	SHFILEOPSTRUCT file_op = { NULL, FO_DELETE, tempdir, NULL,
		FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT, false, 0, "" };
	int ret = SHFileOperation(&file_op);
	free(tempdir);

	return ret;
}
#else
int UNIX_RemoveEntry(const char* path, const struct stat* sb, int typeflag, PFTW ftwbuf)
{
	int ret = remove(path);
	if (ret) perror(path);
	return ret;
}
#endif
