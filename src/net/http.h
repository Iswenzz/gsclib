#pragma once
#include "curl.h"

#define CHECK_HTTP_REQUEST(http)                        \
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

void GScr_HTTP_Init();
void GScr_HTTP_Free();
void GScr_HTTP_PostFile();
void GScr_HTTP_Post();
void GScr_HTTP_GetFile();
void GScr_HTTP_Get();
void GScr_HTTP_Response();

size_t HTTP_WriteFile(void* ptr, size_t size, size_t nmemb, void* stream);
size_t HTTP_WriteString(void* ptr, size_t size, size_t nmemb, void* stream);
void HTTP_Working(qboolean state);
void HTTP_Execute(uv_work_t* req);
