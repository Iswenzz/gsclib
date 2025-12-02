#pragma once
#include <CGSC/cgsc.h>
#include "curl.h"

#define CHECK_FTP_REQUEST(ftp)                        \
	CURL_CHECK_ERROR(!ftp, "FTP request not found."); \
	CURL_CHECK_ERROR(ftp->curl.worker && ftp->curl.worker->status == ASYNC_PENDING, "FTP request is pending.");

#define CHECK_FTP_INSTANCE(handle) CURL_CHECK_ERROR(!handle, "FTP Connection not found.\n");

typedef struct
{
	const char filename[MAX_PATH];
	FILE* stream;
} FTP_FILE;

typedef struct
{
	CURL* handle;
	CURLM* multiHandle;
	char url[4096];
	char password[255];
	unsigned short port;
	qboolean working;
} FTP_HANDLER;

typedef struct
{
	CURL_REQUEST curl;
	FTP_FILE file;
} FTP_REQUEST;

extern FTP_HANDLER ftp_handler;

void GScr_FTP_Init();
void GScr_SFTP_Connect();
void GScr_FTP_Connect();
void GScr_FTP_Close();
void GScr_FTP_Shell();
void GScr_FTP_PostFile();
void GScr_FTP_GetFile();
void GScr_FTP_Free();

qboolean FTP_Connect(const char* protocol, const char* hostname, const char* username, const char* password,
	unsigned short port);
qboolean FTP_Close();
size_t FTP_Write(void* buffer, size_t size, size_t nmemb, void* stream);
size_t FTP_Read(void* ptr, size_t size, size_t nmemb, void* stream);
void FTP_Working(qboolean state);
void FTP_Execute(uv_work_t* req);
