#pragma once
#include <cgsc.h>
#include <curl/curl.h>

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

typedef struct
{
	struct curl_slist*	header;
	int 				opt_count;
	CURL_OPT 			opts[512];
} CURL_INSTANCE;

typedef struct
{
	CURL*				curl;
	char 				url[4096];
	char 				password[255];
	unsigned short 		port;
} FTP_INSTANCE;

extern CURL_INSTANCE curl_instance;
extern FTP_INSTANCE ftp_instance;

i_curl_string i_string_init();
qboolean i_curl_close();
void i_curl_setopts(CURL* curl);
void i_curl_setheader(CURL* curl, CURLoption header_type);
void i_curl_opt_cleanup();
void i_curl_header_cleanup();
qboolean i_curl_connect(const char *protocol, const char *hostname, const char *username, 
	const char *password, unsigned short port);

void GScr_CURL_Version();
void GScr_CURL_SetHeader();
void GScr_CURL_HeaderCleanup();
void GScr_CURL_OptCleanup();
void GScr_CURL_AddOpt();