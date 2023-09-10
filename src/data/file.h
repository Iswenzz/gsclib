#pragma once
#define _CRT_DECLARE_NONSTDC_NAMES 1
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#define _FILE_OFFSET_BITS 64
#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <dirent.h>

#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
	#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
	#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

#ifdef _WIN32
	#include <windows.h>
	#include <shellapi.h>
#else
	#include <ftw.h>
	#include <unistd.h>

	typedef struct FTW* PFTW;
#endif

#ifndef MAX_PATH
	#define MAX_PATH 255
#endif

/// <summary>
/// Create a file.
/// </summary>
void GScr_FILE_Create();

/// <summary>
/// Open a file.
/// </summary>
void GScr_FILE_Open();

/// <summary>
/// Check if a file exists.
/// </summary>
void GScr_FILE_Exists();

/// <summary>
/// Set the file buffer position.
/// </summary>
void GScr_FILE_Seek();

/// <summary>
/// Read a line.
/// </summary>
void GScr_FILE_ReadLine();

/// <summary>
/// Write a line.
/// </summary>
void GScr_FILE_WriteLine();

/// <summary>
/// Read lines.
/// </summary>
void GScr_FILE_ReadLines();

/// <summary>
/// Write lines.
/// </summary>
void GScr_FILE_WriteLines();

/// <summary>
/// Read the file.
/// </summary>
void GScr_FILE_Read();

/// <summary>
/// Write in the file.
/// </summary>
void GScr_FILE_Write();

/// <summary>
/// Delete a file.
/// </summary>
void GScr_FILE_Delete();

/// <summary>
/// Close a file.
/// </summary>
void GScr_FILE_Close();

/// <summary>
/// Create a directory.
/// </summary>
void GScr_FILE_MkDir();

/// <summary>
/// Delete a directory.
/// </summary>
void GScr_FILE_RmDir();

/// <summary>
/// Read directory files.
/// </summary>
void GScr_FILE_ReadDir();

#ifdef _WIN32
/// <summary>
/// Remove a directory.
/// </summary>
/// <param name="path">The directory path.</param>
/// <returns></returns>
BOOL WIN_RemoveDirectory(const char* path);
#else
/// <summary>
/// Remove a file/directory entry.
/// </summary>
/// <param name="path">The entry path.</param>
/// <param name="sb">The file stat.</param>
/// <param name="typeflag">The type flag.</param>
/// <param name="ftwbuf">The FTW struct buffer.</param>
/// <returns></returns>
int UNIX_RemoveDirectory(const char* path, const struct stat* sb, int typeflag, PFTW ftwbuf);
#endif
