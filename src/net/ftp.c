#include "ftp.h"
#include "data/file.h"

#include <string.h>
#include <errno.h>

size_t FTP_Write(void *buffer, size_t size, size_t nmemb, void *stream)
{
	FTPfile *out = (FTPfile *)stream;
	if(!out->stream)
	{
		out->stream = fopen(out->filename, "wb");
		if(!out->stream)
			return -1;
	}
	return fwrite(buffer, size, nmemb, out->stream);
}

size_t FTP_Read(void *ptr, size_t size, size_t nmemb, void *stream)
{
	return (curl_off_t)fread(ptr, size, nmemb, (FILE *)stream);
}

void GScr_SFTP_Connect()
{
	CHECK_PARAMS(4, "Usage: SFTP_Connect(<hostname>, <username>, <password>, <port>)");

	qboolean connect = CURL_FTP_Connect("sftp",
		Plugin_Scr_GetString(0), Plugin_Scr_GetString(1),
		Plugin_Scr_GetString(2), Plugin_Scr_GetInt(3));
	Plugin_Scr_AddBool(connect);
}

void GScr_FTP_Connect()
{
	CHECK_PARAMS(4, "Usage: FTP_Connect(<hostname>, <username>, <password>, <port>)");

	qboolean connect = CURL_FTP_Connect("ftp",
		Plugin_Scr_GetString(0), Plugin_Scr_GetString(1),
		Plugin_Scr_GetString(2), Plugin_Scr_GetInt(3));
	Plugin_Scr_AddBool(connect);
}

void GScr_FTP_Close()
{
	CHECK_PARAMS(0, "Usage: FTP_Close()");
	Plugin_Scr_AddBool(CURL_FTP_Close());
}

void GScr_FTP_Shell()
{
	CHECK_PARAMS(0, "Usage: FTP_Shell() - Execute header from CURL_AddHeader()");
	CHECK_FTP_CONNECTION();

	CURLcode res;
	if(ftp.handle)
	{
		curl_easy_reset(ftp.handle);

		CURL_SetHeader(ftp.handle, CURLOPT_QUOTE);
		curl_easy_setopt(ftp.handle, CURLOPT_URL, ftp.url);
		curl_easy_setopt(ftp.handle, CURLOPT_PASSWORD, ftp.password);
		curl_easy_setopt(ftp.handle, CURLOPT_PORT, ftp.port);
		curl_easy_setopt(ftp.handle, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		CURL_SetOpts(ftp.handle);

		res = curl_easy_perform(ftp.handle);
		if(CURLE_OK != res)
		{
			Plugin_Printf("curl_easy_perform() failed %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else
			Plugin_Scr_AddBool(qtrue);
	}
	CURL_OptCleanup();
	CURL_HeaderCleanup();
}

void GScr_FTP_PostFile()
{
	CHECK_PARAMS(2, "Usage: FTP_PostFile(<filepath>, <uploadtopath>)");
	CHECK_FTP_CONNECTION();

	const char *filepath = Plugin_Scr_GetString(0);
	CURLcode res;
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;

	// Check file
	if(stat(filepath, &file_info))
	{
		Plugin_Printf("Couldn't open '%s': %s\n", filepath, strerror(errno));
		Plugin_Scr_AddBool(qfalse);
		return;
	}
	fsize = (curl_off_t)file_info.st_size;

	hd_src = fopen(filepath, "rb");
	if (!hd_src)
	{
		Plugin_Printf("File not found.\n");
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Post file
	if(ftp.handle)
	{
		curl_easy_reset(ftp.handle);

		char url[4096];
		strcpy(url, ftp.url);
		strcat(url, Plugin_Scr_GetString(1));

		CURL_SetHeader(ftp.handle, CURLOPT_POSTQUOTE);
		curl_easy_setopt(ftp.handle, CURLOPT_URL, url);
		curl_easy_setopt(ftp.handle, CURLOPT_PASSWORD, ftp.password);
		curl_easy_setopt(ftp.handle, CURLOPT_PORT, ftp.port);
		curl_easy_setopt(ftp.handle, CURLOPT_READFUNCTION, FTP_Read);
		curl_easy_setopt(ftp.handle, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(ftp.handle, CURLOPT_READDATA, hd_src);
		curl_easy_setopt(ftp.handle, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
		curl_easy_setopt(ftp.handle, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		CURL_SetOpts(ftp.handle);

		res = curl_easy_perform(ftp.handle);
		if(res != CURLE_OK)
		{
			Plugin_Printf("curl_easy_perform() failed %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else
			Plugin_Scr_AddBool(qtrue);
	}
	fclose(hd_src);

	CURL_OptCleanup();
	CURL_HeaderCleanup();
}

void GScr_FTP_GetFile()
{
	CHECK_PARAMS(2, "Usage: FTP_GetFile(<savefilepath>, <download filepath>)");
	CHECK_FTP_CONNECTION();

	const char *filepath = Plugin_Scr_GetString(0);
	CURLcode res;
	FTPfile ftpfile = { filepath, NULL };

	if(ftp.handle)
	{
		curl_easy_reset(ftp.handle);

		char url[4096];
		strcpy(url, ftp.url);
		strcat(url, Plugin_Scr_GetString(1));

		CURL_SetHeader(ftp.handle, CURLOPT_PREQUOTE);
		curl_easy_setopt(ftp.handle, CURLOPT_URL, url);
		curl_easy_setopt(ftp.handle, CURLOPT_PASSWORD, ftp.password);
		curl_easy_setopt(ftp.handle, CURLOPT_PORT, ftp.port);
		curl_easy_setopt(ftp.handle, CURLOPT_WRITEFUNCTION, FTP_Write);
		curl_easy_setopt(ftp.handle, CURLOPT_WRITEDATA, &ftpfile);
		curl_easy_setopt(ftp.handle, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		CURL_SetOpts(ftp.handle);

		res = curl_easy_perform(ftp.handle);
		if(CURLE_OK != res)
		{
			Plugin_Printf("curl_easy_perform() failed %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else
			Plugin_Scr_AddBool(qtrue);
	}
	if(ftpfile.stream)
		fclose(ftpfile.stream);

	CURL_OptCleanup();
	CURL_HeaderCleanup();
}
