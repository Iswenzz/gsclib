#pragma once
#include "file.h"

#include <zip.h>
#include <CGSC/cgsc.h>

/// <summary>
/// Add a file to the archive.
/// </summary>
void GScr_ZIP_Add();

/// <summary>
/// Rename a file in the archive.
/// </summary>
void GScr_ZIP_Rename();

/// <summary>
/// Delete a file in the archive.
/// </summary>
void GScr_ZIP_Delete();

/// <summary>
/// Open an archive.
/// </summary>
void GScr_ZIP_Open();

/// <summary>
/// Close the archive.
/// </summary>
void GScr_ZIP_Close();

/// <summary>
/// Add a file to the archive.
/// </summary>
/// <param name="zip">The zip archive.</param>
/// <param name="filepath">The filepath to add.</param>
/// <param name="outpath">The output path in the archive.</param>
/// <returns></returns>
qboolean ZIP_Add(zip_t* zip, const char* filepath, const char* outpath);

/// <summary>
/// Rename a file in the archive.
/// </summary>
/// <param name="zip">The zip archive.</param>
/// <param name="filepath">The filepath to rename.</param>
/// <param name="renamepath">The renamed path.</param>
/// <returns></returns>
qboolean ZIP_Rename(zip_t* zip, const char* filepath, const char* renamepath);

/// <summary>
/// Delete a file in the archive.
/// </summary>
/// <param name="zip">The zip archive.</param>
/// <param name="filepath">The filepath to delete.</param>
/// <returns></returns>
qboolean ZIP_Delete(zip_t* zip, const char* filepath);

/// <summary>
/// Open an archive.
/// </summary>
/// <param name="path">The zip filepath.</param>
/// <returns></returns>
zip_t* ZIP_Open(const char* path);

/// <summary>
/// Close the archive.
/// </summary>
/// <param name="zip">The zip archive.</param>
/// <returns></returns>
qboolean ZIP_Close(zip_t* zip);
