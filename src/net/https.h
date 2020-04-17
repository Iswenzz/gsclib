#pragma once
#include "curl.h"

size_t https_fwrite(void *ptr, size_t size, size_t nmemb, void *stream);
size_t https_write_string(void *ptr, size_t size, size_t nmemb, void *stream);

void GScr_HTTPS_PostFile();
void GScr_HTTPS_PostString();

void GScr_HTTPS_GetFile();
void GScr_HTTPS_GetString();