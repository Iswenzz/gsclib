#pragma once
#include <CGSC/cgsc.h>
#include <curl/curl.h>

#include "data/file.h"
#include "sys/system.h"

#include <stdlib.h>

#define CURL_CHECK_ERROR(x, msg) \
	if (x)                       \
	{                            \
		Plugin_Scr_Error(msg);   \
		return;                  \
	}

#define CHECK_CURL_REQUEST(curl)                        \
	CURL_CHECK_ERROR(!curl, "CURL request not found."); \
	CURL_CHECK_ERROR(curl->worker && curl->worker->status == ASYNC_PENDING, "CURL request is pending.");

#define CHECK_CURL_WORKING() CURL_CHECK_ERROR(curl_handler.working, "CURL is processing another request.");

typedef struct
{
	CURLcode code;
	CURL* handle;
	qboolean working;
} CURL_HANDLER;

typedef struct
{
	long opt;
	VariableValue param;
} CURL_OPTS;

typedef struct
{
	async_worker* worker;
	CURL* handle;
	CURLM* multiHandle;
	struct curl_slist* header;
	int optsCount;
	CURL_OPTS opts[512];
} CURL_REQUEST;

extern CURL_HANDLER curl_handler;

void GScr_CURL_Init();
void GScr_CURL_Version();
void GScr_CURL_AddHeader();
void GScr_CURL_HeaderCleanup();
void GScr_CURL_OptCleanup();
void GScr_CURL_AddOpt();
void GScr_CURL_Free();

void CURL_Working(qboolean state);
void CURL_SetOpts(CURL_REQUEST* curl);
void CURL_SetHeader(CURL_REQUEST* curl, CURLoption header_type);
void CURL_OptCleanup(CURL_REQUEST* curl);
void CURL_HeaderCleanup(CURL_REQUEST* curl);
