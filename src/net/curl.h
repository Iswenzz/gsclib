#pragma once
#include <CGSC/cgsc.h>
#include <curl/curl.h>

extern CURLcode CURLinitCode;

/// <summary>
/// Check if an FTP connection exists and return if not.
/// </summary>
#define CHECK_FTP_CONNECTION() 						\
if (ftp.handle == NULL)							    \
{											        \
	Plugin_Printf("FTP Connection not found.\n");	\
	return;									        \
}

typedef struct
{
	const char* filename;
	FILE* stream;
} FTPfile;

typedef struct
{
    char *buffer;
    size_t len;
} CURLstring;

typedef struct
{
	long opt;
	VariableValue param;
} CURLopt;

/// <summary>
/// Structure that contains a CURL header struct and an array of CURL options.
/// </summary>
typedef struct
{
	struct curl_slist*	header;
	int 				optsCount;
	CURLopt 			opts[512];
} CURLinstance;

/// <summary>
/// Structure that contains a CURL handle and information about the FTP connection
/// such as ftp url, password, port.
/// </summary>
typedef struct
{
	CURL*				handle;
	char 				url[4096];
	char 				password[255];
	unsigned short 		port;
} FTPinstance;

extern CURLinstance curl;
extern FTPinstance ftp;

/// <summary>
/// Alloc a string buffer for curl manipulation. The buffer needs to call free().
/// </summary>
/// <returns></returns>
CURLstring CURL_StringInit();

/// <summary>
/// Close all connections.
/// </summary>
/// <returns></returns>
qboolean CURL_FTP_Close();

/// <summary>
/// Set the options that has been set in the CURLinstance struct.
/// </summary>
/// <param name="curl"></param>
void CURL_SetOpts(CURL* handle);

/// <summary>
/// Set the header that has been set in the CURLinstance struct.
/// </summary>
/// <param name="handle">The CURL handle.</param>
/// <param name="header_type">The header option type.</param>
void CURL_SetHeader(CURL* handle, CURLoption header_type);

/// <summary>
/// Cleanup all CURL options from the CURLinstance struct.
/// </summary>
void CURL_OptCleanup();

/// <summary>
/// Cleanup the CURL header from the CURLinstance struct.
/// </summary>
void CURL_HeaderCleanup();

/// <summary>
/// Connect to a FTP/FTPS/SFTP server.
/// </summary>
/// <param name="protocol">File protocol to use i.e: FTP/SFTP.</param>
/// <param name="hostname">Host ip/name address.</param>
/// <param name="username">The username to connect with.</param>
/// <param name="password">The password to connect with.</param>
/// <param name="port">The server port.</param>
/// <returns>True when the connection succeded.</returns>
qboolean CURL_FTP_Connect(const char *protocol, const char *hostname, const char *username,
	const char *password, unsigned short port);

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
