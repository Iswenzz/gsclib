#include "ftp.h"

#include <string.h>
#include <errno.h>

FTP_HANDLER ftp_handler = { 0 };

void GScr_FTP_Init()
{
	CHECK_PARAMS(0, "Usage: FTP_Init()");

	FTP_REQUEST* ftp = (FTP_REQUEST*)calloc(1, sizeof(FTP_REQUEST));
	ftp->curl.handle = ftp_handler.handle;
	ftp->curl.multiHandle = ftp_handler.multiHandle;
	curl_multi_add_handle(ftp->curl.multiHandle, ftp->curl.handle);
	ftp_handler.working = qtrue;

	Plugin_Scr_AddInt((int)ftp);
}

void GScr_SFTP_Connect()
{
	CHECK_PARAMS(4, "Usage: SFTP_Connect(<hostname>, <username>, <password>, <port>)");

	qboolean connect = FTP_Connect("sftp", Plugin_Scr_GetString(0), Plugin_Scr_GetString(1),
		Plugin_Scr_GetString(2), Plugin_Scr_GetInt(3));

	Plugin_Scr_AddBool(connect);
}

void GScr_FTP_Connect()
{
	CHECK_PARAMS(4, "Usage: FTP_Connect(<hostname>, <username>, <password>, <port>)");

	qboolean connect = FTP_Connect("ftp", Plugin_Scr_GetString(0), Plugin_Scr_GetString(1),
		Plugin_Scr_GetString(2), Plugin_Scr_GetInt(3));

	Plugin_Scr_AddBool(connect);
}

void GScr_FTP_Close()
{
	CHECK_PARAMS(0, "Usage: FTP_Close()");
	Plugin_Scr_AddBool(FTP_Close());
}

void GScr_FTP_Cancel()
{
	CHECK_PARAMS(1, "Usage: FTP_Cancel(<request>)");

	FTP_REQUEST* ftp = (FTP_REQUEST*)Plugin_Scr_GetInt(0);
	if (ftp) ftp->curl.request.canceled = qtrue;
}

void GScr_FTP_Shell()
{
	CHECK_PARAMS(1, "Usage: FTP_Shell(<request>)");

	FTP_REQUEST* ftp = (FTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_FTP_REQUEST(ftp);
	CHECK_FTP_INSTANCE(ftp->curl.handle);

	if (ftp->curl.handle)
	{
		curl_easy_reset(ftp->curl.handle);

		CURL_SetHeader(&ftp->curl, CURLOPT_QUOTE);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_URL, ftp_handler.url);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_PASSWORD, ftp_handler.password);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_PORT, ftp_handler.port);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		CURL_SetOpts(&ftp->curl);

		ftp->curl.request.status = ASYNC_PENDING;
		Plugin_AsyncCall(ftp, &FTP_Shell, &Plugin_AsyncNull);
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_FTP_PostFile()
{
	CHECK_PARAMS(3, "Usage: FTP_PostFile(<request>, <filepath>, <uploadtopath>)");

	FTP_REQUEST* ftp = (FTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_FTP_REQUEST(ftp);
	CHECK_FTP_INSTANCE(ftp->curl.handle);

	const char *filepath = Plugin_Scr_GetString(1);
	struct stat file_info;
	curl_off_t fsize;

	// Check file
	if (stat(filepath, &file_info))
	{
		Plugin_Printf("Couldn't open '%s': %s\n", filepath, strerror(errno));
		Plugin_Scr_AddBool(qfalse);
		ftp->curl.request.status = ASYNC_FAILURE;
		return;
	}
	fsize = (curl_off_t)file_info.st_size;

	strcpy((char*)ftp->file.filename, filepath);
	ftp->file.stream = fopen(filepath, "rb");

	if (!ftp->file.stream)
	{
		Plugin_Printf("File not found.\n");
		Plugin_Scr_AddBool(qfalse);
		ftp->curl.request.status = ASYNC_FAILURE;
		return;
	}

	// Post file
	if (ftp->curl.handle)
	{
		curl_easy_reset(ftp->curl.handle);

		char url[4096];
		strcpy(url, ftp_handler.url);
		strcat(url, Plugin_Scr_GetString(2));

		CURL_SetHeader(&ftp->curl, CURLOPT_POSTQUOTE);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_URL, url);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_PASSWORD, ftp_handler.password);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_PORT, ftp_handler.port);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_READFUNCTION, FTP_Read);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_READDATA, ftp->file.stream);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		CURL_SetOpts(&ftp->curl);

		ftp->curl.request.status = ASYNC_PENDING;
		Plugin_AsyncCall(ftp, &FTP_PostFile, &Plugin_AsyncNull);
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_FTP_GetFile()
{
	CHECK_PARAMS(3, "Usage: FTP_GetFile(<request>, <savefilepath>, <download filepath>)");

	FTP_REQUEST* ftp = (FTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_FTP_REQUEST(ftp);
	CHECK_FTP_INSTANCE(ftp->curl.handle);

	const char *filepath = Plugin_Scr_GetString(1);
	strcpy((char*)ftp->file.filename, filepath);

	if (ftp->curl.handle)
	{
		curl_easy_reset(ftp->curl.handle);

		char url[4096];
		strcpy(url, ftp_handler.url);
		strcat(url, Plugin_Scr_GetString(2));

		CURL_SetHeader(&ftp->curl, CURLOPT_PREQUOTE);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_URL, url);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_PASSWORD, ftp_handler.password);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_PORT, ftp_handler.port);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_WRITEFUNCTION, FTP_Write);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_WRITEDATA, ftp->file.stream);
		curl_easy_setopt(ftp->curl.handle, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		CURL_SetOpts(&ftp->curl);

		ftp->curl.request.status = ASYNC_PENDING;
		Plugin_AsyncCall(ftp, &FTP_GetFile, &Plugin_AsyncNull);
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_FTP_Free()
{
	CHECK_PARAMS(1, "Usage: FTP_Free(<request>)");

	FTP_REQUEST* ftp = (FTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_FTP_REQUEST(ftp);

	if (ftp->file.stream)
		fclose(ftp->file.stream);

	free(ftp);
	ftp = NULL;

	ftp_handler.working = qfalse;
	Plugin_Scr_AddBool(qtrue);
}

qboolean FTP_Close()
{
	if (ftp_handler.handle != NULL)
	{
		if (ftp_handler.multiHandle)
		{
			curl_multi_remove_handle(ftp_handler.multiHandle, ftp_handler.handle);
			curl_multi_cleanup(ftp_handler.multiHandle);
		}
		curl_easy_cleanup(ftp_handler.handle);
		memset(&ftp_handler, 0, sizeof(ftp_handler));
		return qtrue;
	}
	return qfalse;
}

qboolean FTP_Connect(const char* protocol, const char* hostname, const char* username,
	const char* password, unsigned short port)
{
	FTP_Close();

	snprintf(ftp_handler.url, sizeof(ftp_handler.url), "%s://%s@%s/", protocol, username, hostname);
	strcpy(ftp_handler.password, password);
	ftp_handler.port = port;
	ftp_handler.handle = curl_easy_init();
	ftp_handler.multiHandle = curl_multi_init();
	return ftp_handler.handle != NULL;
}

size_t FTP_Write(void* buffer, size_t size, size_t nmemb, void* stream)
{
	FTP_FILE* out = (FTP_FILE*)stream;
	if (!out->stream)
	{
		out->stream = fopen(out->filename, "wb");
		if (!out->stream)
			return -1;
	}
	return fwrite(buffer, size, nmemb, out->stream);
}

size_t FTP_Read(void* ptr, size_t size, size_t nmemb, void* stream)
{
	return (curl_off_t)fread(ptr, size, nmemb, (FILE*)stream);
}

void FTP_Shell(uv_work_t* req)
{
	FTP_REQUEST* ftp = (FTP_REQUEST*)req->data;
	CURLMcode res = 0;
	int running = 0;

	do
	{
		res = curl_multi_perform(ftp->curl.multiHandle, &running);
		if (res != CURLE_OK)
		{
			Sys_PrintF("curl_easy_perform() failed: %s\n", curl_multi_strerror(res));
			ftp->curl.request.status = ASYNC_FAILURE;
		}
	} 
	while (running && !ftp->curl.request.canceled);

	CURL_OptCleanup(&ftp->curl);
	CURL_HeaderCleanup(&ftp->curl);
	ftp->curl.request.status = ASYNC_SUCCESSFUL;
}

void FTP_PostFile(uv_work_t* req)
{
	FTP_REQUEST* ftp = (FTP_REQUEST*)req->data;
	CURLMcode res = 0;
	int running = 0;

	do
	{
		res = curl_multi_perform(ftp->curl.multiHandle, &running);
		if (res != CURLE_OK)
		{
			Sys_PrintF("curl_easy_perform() failed: %s\n", curl_multi_strerror(res));
			ftp->curl.request.status = ASYNC_FAILURE;
		}
	} 
	while (running && !ftp->curl.request.canceled);

	CURL_OptCleanup(&ftp->curl);
	CURL_HeaderCleanup(&ftp->curl);
	ftp->curl.request.status = ASYNC_SUCCESSFUL;
}

void FTP_GetFile(uv_work_t* req)
{
	FTP_REQUEST* ftp = (FTP_REQUEST*)req->data;
	CURLMcode res = 0;
	int running = 0;

	do
	{
		res = curl_multi_perform(ftp->curl.multiHandle, &running);
		if (res != CURLE_OK)
		{
			Sys_PrintF("curl_easy_perform() failed: %s\n", curl_multi_strerror(res));
			ftp->curl.request.status = ASYNC_FAILURE;
		}
	} 
	while (running && !ftp->curl.request.canceled);

	CURL_OptCleanup(&ftp->curl);
	CURL_HeaderCleanup(&ftp->curl);
	ftp->curl.request.status = ASYNC_SUCCESSFUL;
}
