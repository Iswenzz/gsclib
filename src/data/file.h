#pragma once
#define _CRT_DECLARE_NONSTDC_NAMES 1
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#define _FILE_OFFSET_BITS 64
#define _XOPEN_SOURCE 700

#include <dirent.h>
#include <sys/stat.h>

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

void GScr_FILE_Create();
void GScr_FILE_Open();
void GScr_FILE_Exists();
void GScr_FILE_Seek();
void GScr_FILE_ReadLine();
void GScr_FILE_WriteLine();
void GScr_FILE_ReadLines();
void GScr_FILE_WriteLines();
void GScr_FILE_Read();
void GScr_FILE_Write();
void GScr_FILE_Delete();
void GScr_FILE_Close();
void GScr_FILE_MkDir();
void GScr_FILE_RmDir();
void GScr_FILE_ReadDir();

#ifdef _WIN32
BOOL WIN_RemoveDirectory(const char* path);
#else
int UNIX_RemoveDirectory(const char* path, const struct stat* sb, int typeflag, PFTW ftwbuf);
#endif
