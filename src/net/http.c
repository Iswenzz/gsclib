#include "http.h"

#include <stdlib.h>
#include <string.h>

HTTP_HANDLER http_handler = { 0 };

void GScr_HTTP_Init()
{
	CHECK_PARAMS(0, "Usage: HTTP_Init()");

	HTTP_REQUEST* http = (HTTP_REQUEST*)calloc(1, sizeof(HTTP_REQUEST));
	http->curl.handle = curl_easy_init();
	http->curl.multiHandle = curl_multi_init();
	curl_multi_add_handle(http->curl.multiHandle, http->curl.handle);

	HTTP_Working(qtrue);
	Plugin_Scr_AddInt((int)http);
}

void GScr_HTTP_Free()
{
	CHECK_PARAMS(1, "Usage: HTTP_Free(<request>)");

	HTTP_REQUEST* http = (HTTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_HTTP_REQUEST(http);

	CURL_OptCleanup(&http->curl);
	CURL_HeaderCleanup(&http->curl);

	if (http->curl.multiHandle)
	{
		curl_multi_remove_handle(http->curl.multiHandle, http->curl.handle);
		curl_multi_cleanup(http->curl.multiHandle);
	}
	if (http->curl.handle)
		curl_easy_cleanup(http->curl.handle);
	if (http->response.buffer)
		free(http->response.buffer);
	if (http->file.stream)
		fclose(http->file.stream);
	free(http);

	HTTP_Working(qfalse);
	Plugin_Scr_AddBool(qtrue);
}

void GScr_HTTP_Get()
{
	CHECK_PARAMS(2, "Usage: HTTP_GetString(<request>, <url>)");

	HTTP_REQUEST* http = (HTTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_HTTP_REQUEST(http);

	if (http->curl.handle)
	{
		CURL_SetHeader(&http->curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(http->curl.handle, CURLOPT_URL, Plugin_Scr_GetString(1));
		curl_easy_setopt(http->curl.handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(http->curl.handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEFUNCTION, HTTP_WriteString);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEDATA, &http->response);
		CURL_SetOpts(&http->curl);

		http->curl.worker = Plugin_AsyncWorker(asyncHandler, http, &HTTP_Execute, NULL);
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_HTTP_GetFile()
{
	CHECK_PARAMS(3, "Usage: HTTP_GetFile(<request>, <filepath>, <url>)");

	HTTP_REQUEST* http = (HTTP_REQUEST*)Plugin_Scr_GetInt(0);
	const char* filepath = Plugin_Scr_GetString(1);

	CHECK_HTTP_REQUEST(http);

	strcpy((char*)http->file.filename, filepath);
	http->file.stream = fopen(filepath, "wb");

	if (!http->file.stream)
	{
		Plugin_Printf("File not found.\n");
		Plugin_Scr_AddBool(qfalse);
		http->curl.worker->status = ASYNC_FAILURE;
		return;
	}
	if (http->curl.handle)
	{
		CURL_SetHeader(&http->curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(http->curl.handle, CURLOPT_URL, Plugin_Scr_GetString(2));
		curl_easy_setopt(http->curl.handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEFUNCTION, HTTP_WriteFile);
		curl_easy_setopt(http->curl.handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEDATA, http->file.stream);
		CURL_SetOpts(&http->curl);

		http->curl.worker = Plugin_AsyncWorker(asyncHandler, http, &HTTP_Execute, NULL);
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_HTTP_Post()
{
	CHECK_PARAMS(3, "Usage: HTTP_PostString(<request>, <string>, <url>)");

	HTTP_REQUEST* http = (HTTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_HTTP_REQUEST(http);

	if (http->curl.handle)
	{
		CURL_SetHeader(&http->curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(http->curl.handle, CURLOPT_URL, Plugin_Scr_GetString(2));
		curl_easy_setopt(http->curl.handle, CURLOPT_POSTFIELDS, Plugin_Scr_GetString(1));
		curl_easy_setopt(http->curl.handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(http->curl.handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEFUNCTION, HTTP_WriteString);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEDATA, &http->response);
		CURL_SetOpts(&http->curl);

		http->curl.worker = Plugin_AsyncWorker(asyncHandler, http, &HTTP_Execute, NULL);
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_HTTP_PostFile()
{
	CHECK_PARAMS(3, "Usage: HTTP_PostFile(<request>, <filepath>, <url>)");

	HTTP_REQUEST* http = (HTTP_REQUEST*)Plugin_Scr_GetInt(0);
	const char* filepath = Plugin_Scr_GetString(1);

	CHECK_HTTP_REQUEST(http);

	// Check file
	strcpy((char*)http->file.filename, filepath);
	http->file.stream = fopen(filepath, "rb");

	if (http->file.stream)
	{
		fseek(http->file.stream, 0, SEEK_END);
		http->response.len = ftell(http->file.stream);
		fseek(http->file.stream, 0, SEEK_SET);
		http->response.buffer = malloc(http->response.len * sizeof(char));

		if (http->response.buffer)
			fread(http->response.buffer, 1, http->response.len, http->file.stream);
		fclose(http->file.stream);
	}
	else
	{
		Plugin_Printf("File not found.\n");
		Plugin_Scr_AddBool(qfalse);
		http->curl.worker->status = ASYNC_FAILURE;
		return;
	}

	// Post file
	if (http->curl.handle)
	{
		CURL_SetHeader(&http->curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(http->curl.handle, CURLOPT_URL, Plugin_Scr_GetString(2));
		curl_easy_setopt(http->curl.handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(http->curl.handle, CURLOPT_POSTFIELDSIZE, http->response.len);
		curl_easy_setopt(http->curl.handle, CURLOPT_POSTFIELDS, http->response.buffer);
		curl_easy_setopt(http->curl.handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEFUNCTION, HTTP_WriteString);
		curl_easy_setopt(http->curl.handle, CURLOPT_WRITEDATA, &http->response);
		CURL_SetOpts(&http->curl);

		http->curl.worker = Plugin_AsyncWorker(asyncHandler, http, &HTTP_Execute, NULL);
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_HTTP_Response()
{
	CHECK_PARAMS(1, "Usage: HTTP_Response(<request>)");

	HTTP_REQUEST* http = (HTTP_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_HTTP_REQUEST(http);

	Plugin_Scr_AddString(http->response.buffer ? http->response.buffer : "");
}

size_t HTTP_WriteFile(void* ptr, size_t size, size_t nmemb, void* stream)
{
	return fwrite(ptr, size, nmemb, (FILE*)stream);
}

size_t HTTP_WriteString(void* ptr, size_t size, size_t nmemb, void* stream)
{
	HTTP_RESPONSE* res = (HTTP_RESPONSE*)stream;
	size_t new_len = res->len + size * nmemb;
	if (res->buffer == NULL)
		res->buffer = (char*)malloc(new_len + 1);
	else
	{
		char* tmp = (char*)realloc(res->buffer, new_len + 1);
		if (tmp != NULL)
			res->buffer = tmp;
	}

	memcpy(res->buffer + res->len, ptr, size * nmemb);
	res->buffer[new_len] = '\0';
	res->len = new_len;

	return size * nmemb;
}

void HTTP_Working(qboolean state)
{
	http_handler.working = state;
}

void HTTP_Execute(uv_work_t* req)
{
	async_worker* worker = (async_worker*)req->data;
	HTTP_REQUEST* http = (HTTP_REQUEST*)worker->data;
	int running = 0;

	do
	{
		const CURLMcode res = curl_multi_perform(http->curl.multiHandle, &running);
		if (res != CURLM_OK)
		{
			Sys_PrintF("curl_multi_perform() failed: %s\n", curl_multi_strerror(res));
			Plugin_AsyncWorkerDone(req, ASYNC_FAILURE);
			return;
		}
	} while (running && worker->status != ASYNC_CANCEL);

	Plugin_AsyncWorkerDone(req, ASYNC_SUCCESSFUL);
}
