#pragma once
#define _CRT_DECLARE_NONSTDC_NAMES 1
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h>

#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
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
