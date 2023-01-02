#pragma once
#include "curl.h"
#include <CGSC/cgsc.h>

#define CHECK_FTP_REQUEST(ftp)													\
CURL_CHECK_ERROR(ftp, "FTP request not found.");								\
CURL_CHECK_ERROR((ftp->curl.status != ASYNC_PENDING), "FTP request is pending.");	\

#define CHECK_FTP_INSTANCE(handle) \
CURL_CHECK_ERROR(handle, "FTP Connection not found.\n");

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

/// <summary>
/// Init the FTP request.
/// </summary>
void GScr_FTP_Init();

/// <summary>
/// Connect to an SFTP server, the connection can be closed with FTP_Close.
/// </summary>
void GScr_SFTP_Connect();

/// <summary>
/// Connect to an FTP/FTPS server, the connection can be closed with FTP_Close.
/// </summary>
void GScr_FTP_Connect();

/// <summary>
/// Close the FTP/FTPS/SFTP connection.
/// </summary>
void GScr_FTP_Close();

/// <summary>
/// Cancel an FTP request.
/// </summary>
void GScr_FTP_Cancel();

/// <summary>
/// Execute a command to the FTP/FTPS/SFTP server.
/// The commands should be set with CURL_AddHeader.
/// </summary>
void GScr_FTP_Shell();

/// <summary>
/// Upload a file to the FTP/FTPS/SFTP server.
/// </summary>
void GScr_FTP_PostFile();

/// <summary>
/// Download a file from the FTP/FTPS/SFTP server.
/// </summary>
void GScr_FTP_GetFile();

/// <summary>
/// Free an FTP request.
/// </summary>
void GScr_FTP_Free();

/// <summary>
/// Connect to a FTP/FTPS/SFTP server.
/// </summary>
/// <param name="protocol">File protocol to use i.e: FTP/SFTP.</param>
/// <param name="hostname">Host ip/name address.</param>
/// <param name="username">The username to connect with.</param>
/// <param name="password">The password to connect with.</param>
/// <param name="port">The server port.</param>
/// <returns>True when the connection succeded.</returns>
qboolean FTP_Connect(const char* protocol, const char* hostname, const char* username,
	const char* password, unsigned short port);

/// <summary>
/// Close all connections.
/// </summary>
/// <returns></returns>
qboolean FTP_Close();

/// <summary>
/// File write function to use with ftp CURL write callback.
/// </summary>
/// <returns></returns>
size_t FTP_Write(void* buffer, size_t size, size_t nmemb, void* stream);

/// <summary>
/// File read function to use with ftp CURL read callback.
/// </summary>
/// <returns></returns>
size_t FTP_Read(void* ptr, size_t size, size_t nmemb, void* stream);

/// <summary>
/// Execute an FTP shell command.
/// </summary>
/// <param name="req">The worker request.</param>
void FTP_Shell(uv_work_t * req);

/// <summary>
/// Post a file.
/// </summary>
/// <param name="req">The worker request</param>
void FTP_PostFile(uv_work_t* req);

/// <summary>
/// Get a file.
/// </summary>
/// <param name="req">The worker request</param>
void FTP_GetFile(uv_work_t* req);
