#pragma once
#include "curl.h"
#include <cgsc.h>

/// <summary>
/// File write function to use with CURL https write callback.
/// </summary>
/// <returns></returns>
size_t PCL HTTPS_Write(void *ptr, size_t size, size_t nmemb, void *stream);

/// <summary>
/// String write function to use with CURL https write callback.
/// </summary>
/// <returns></returns>
size_t PCL HTTPS_WriteString(void *ptr, size_t size, size_t nmemb, void *stream);

/// <summary>
/// Upload a file to an HTTP/HTTPS url.
/// </summary>
void GScr_HTTPS_PostFile();

/// <summary>
/// Post a string to an HTTP/HTTPS url.
/// </summary>
void GScr_HTTPS_PostString();

/// <summary>
/// Save a file from an HTTP/HTTPS url.
/// </summary>
void GScr_HTTPS_GetFile();

/// <summary>
/// Get a string from an HTTP/HTTPS url.
/// </summary>
void GScr_HTTPS_GetString();
