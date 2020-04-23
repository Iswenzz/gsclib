#pragma once
#include <cgsc.h>
#include <curl/curl.h>

/**
 * @brief 
 * Check if an FTP connection exists and return if not.
 */
#define CHECK_FTP_CONNECTION(x) 			        \
if (x.curl == NULL)							        \
{											        \
	Plugin_Printf("FTP Connection not found.\n");	\
	return;									        \
}

typedef struct 
{
    char *buffer;
    size_t len;
} i_curl_string;

struct FtpFile 
{
	const char *filename;
	FILE *stream;
};

typedef struct
{
	long opt;
	VariableValue *param;
} CURL_OPT;

/**
 * @brief 
 * Structure that contains a CURL header struct and an array of CURL options.
 */
typedef struct
{
	struct curl_slist*	header;
	int 				opt_count;
	CURL_OPT 			opts[512];
} CURL_INSTANCE;

/**
 * @brief 
 * Structure that contains a CURL handle and information about the FTP connection
 * such as ftp url, password, port.
 */
typedef struct
{
	CURL*				curl;
	char 				url[4096];
	char 				password[255];
	unsigned short 		port;
} FTP_INSTANCE;

extern CURL_INSTANCE curl_instance;
extern FTP_INSTANCE ftp_instance;

/**
 * @brief 
 * Alloc a string buffer for curl manipulation. the buffer can be free with free().
 * @return i_curl_string 
 */
i_curl_string i_string_init();

/**
 * @brief 
 * Close all connections.
 * @return qboolean 
 */
qboolean i_curl_close();

/**
 * @brief 
 * Set the options that has been set in the CURL_INSTANCE struct.
 * @param curl - The CURL handle.
 */
void i_curl_setopts(CURL* curl);

/**
 * @brief 
 * Set the header that has been set in the CURL_INSTANCE struct.
 * @param curl - The CURL handle.
 * @param header_type - The header option type.
 */
void i_curl_setheader(CURL* curl, CURLoption header_type);

/**
 * @brief 
 * Cleanup all CURL options from the CURL_INSTANCE struct.
 */
void i_curl_opt_cleanup();

/**
 * @brief 
 * Cleanup the CURL header from the CURL_INSTANCE struct.
 */
void i_curl_header_cleanup();

/**
 * @brief 
 * Connect to a FTP/FTPS/SFTP server.
 * @param protocol - File protocol to use i.e: ftp/sftp
 * @param hostname - Host ip/name address.
 * @param username - The username to connect with.
 * @param password - The password to connect with.
 * @param port - The server port.
 * @return qboolean - If the connection succeded.
 */
qboolean i_curl_connect(const char *protocol, const char *hostname, const char *username, 
	const char *password, unsigned short port);

/**
 * @brief 
 * Print info about curl library. 
 */
void GScr_CURL_Version();

/**
 * @brief 
 * Set CURL Header for the next requests, commands should be separated with a ",".
 */
void GScr_CURL_SetHeader();

/**
 * @brief 
 * Clean header set by CURL_SetHeader.
 */
void GScr_CURL_HeaderCleanup();

/**
 * @brief 
 * Clean all CURL Option added by CURL_AddOpt.
 */
void GScr_CURL_OptCleanup();

/**
 * @brief 
 * Add a CURL Option for the next request.
 */
void GScr_CURL_AddOpt();