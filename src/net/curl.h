#pragma once
#include <CGSC/cgsc.h>
#include <curl/curl.h>

#include "sys/system.h"
#include "data/file.h"

#define CURL_CHECK_ERROR(x, msg)	\
if (!x)								\
{									\
	Plugin_Scr_Error(msg);			\
	return;							\
}

#define CHECK_CURL_REQUEST(curl)												\
CURL_CHECK_ERROR(curl, "CURL request not found.");								\
CURL_CHECK_ERROR((curl->status != ASYNC_PENDING), "CURL request is pending.");	\

#define CHECK_CURL_WORKING() \
CURL_CHECK_ERROR(!curl_handler.working, "CURL is processing another request.");

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
	CURL* handle;
	async_status status;
	struct curl_slist* header;
	int optsCount;
	CURL_OPTS opts[512];
} CURL_REQUEST;

extern CURL_HANDLER curl_handler;

/// <summary>
/// Init a new CURL request.
/// </summary>
void GScr_CURL_Init();

/// <summary>
/// Print info about curl library.
/// </summary>
void GScr_CURL_Version();

/// <summary>
/// Add a CURL Header for the next requests.
/// </summary>
void GScr_CURL_AddHeader();

/// <summary>
/// Clean header set by CURL_AddHeader.
/// </summary>
void GScr_CURL_HeaderCleanup();

/// <summary>
/// Clean all CURL Option added by CURL_AddOpt.
/// </summary>
void GScr_CURL_OptCleanup();

/// <summary>
/// Add a CURL Option for the next request.
/// </summary>
void GScr_CURL_AddOpt();

/// <summary>
/// Get the CURL request status.
/// </summary>
void GScr_CURL_Status();

/// <summary>
/// Free a CURL request.
/// </summary>
void GScr_CURL_Free();

/// <summary>
/// Set the options that has been set in the CURL_REQUEST struct.
/// </summary>
/// <param name="curl">The CURL request.</param>
void CURL_SetOpts(CURL_REQUEST* curl);

/// <summary>
/// Set the header that has been set in the CURL_REQUEST struct.
/// </summary>
/// <param name="curl">The CURL request.</param>
/// <param name="header_type">The header option type.</param>
void CURL_SetHeader(CURL_REQUEST* curl, CURLoption header_type);

/// <summary>
/// Cleanup all CURL options from the CURL_REQUEST struct.
/// </summary>
/// <param name="curl">The CURL request.</param>
void CURL_OptCleanup(CURL_REQUEST* curl);

/// <summary>
/// Cleanup the CURL header from the CURL_REQUEST struct.
/// </summary>
/// <param name="curl">The CURL request.</param>
void CURL_HeaderCleanup(CURL_REQUEST* curl);
