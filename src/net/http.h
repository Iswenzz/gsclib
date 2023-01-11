#pragma once
#include "curl.h"

#define CHECK_HTTP_REQUEST(http) \
CURL_CHECK_ERROR(!http, "HTTP request not found."); \
CURL_CHECK_ERROR(http->curl.worker && http->curl.worker->status == ASYNC_PENDING, "HTTP request is pending.");

typedef struct
{
    char* buffer;
    size_t len;
} HTTP_RESPONSE;

typedef struct
{
	const char filename[MAX_PATH];
	FILE* stream;
} HTTP_FILE;

typedef struct
{
	qboolean working;
} HTTP_HANDLER;

typedef struct
{
	CURL_REQUEST curl;
	HTTP_RESPONSE response;
	HTTP_FILE file;
} HTTP_REQUEST;

extern HTTP_HANDLER http_handler;

/// <summary>
/// Init the HTTP request.
/// </summary>
void GScr_HTTP_Init();

/// <summary>
/// Free an HTTP request.
/// </summary>
void GScr_HTTP_Free();

/// <summary>
/// Upload a file to an HTTP url.
/// </summary>
void GScr_HTTP_PostFile();

/// <summary>
/// Post a string to an HTTP url.
/// </summary>
void GScr_HTTP_Post();

/// <summary>
/// Save a file from an HTTP url.
/// </summary>
void GScr_HTTP_GetFile();

/// <summary>
/// Get a string from an HTTP url.
/// </summary>
void GScr_HTTP_Get();

/// <summary>
/// Get the HTTP response.
/// </summary>
void GScr_HTTP_Response();

/// <summary>
/// File write function to use with CURL http write callback.
/// </summary>
/// <returns></returns>
size_t HTTP_WriteFile(void* ptr, size_t size, size_t nmemb, void* stream);

/// <summary>
/// String write function to use with CURL http write callback.
/// </summary>
/// <returns></returns>
size_t HTTP_WriteString(void* ptr, size_t size, size_t nmemb, void* stream);

/// <summary>
/// Set the HTTP working state.
/// </summary>
/// <param name="state">The working state.</param>
void HTTP_Working(qboolean state);

/// <summary>
/// Execute the async request.
/// </summary>
/// <param name="req">The worker request.</param>
void HTTP_Execute(uv_work_t* req);
