#pragma once
#include "file.h"

#include <CGSC/cgsc.h>
#include <zip.h>

void GScr_ZIP_Add();
void GScr_ZIP_Rename();
void GScr_ZIP_Delete();
void GScr_ZIP_Open();
void GScr_ZIP_Close();

qboolean ZIP_Add(zip_t* zip, const char* filepath, const char* outpath);
qboolean ZIP_Rename(zip_t* zip, const char* filepath, const char* renamepath);
qboolean ZIP_Delete(zip_t* zip, const char* filepath);
zip_t* ZIP_Open(const char* path);
qboolean ZIP_Close(zip_t* zip);
