#include "https.h"

#include <stdlib.h>
#include <string.h>

size_t HTTPS_Write(void *ptr, size_t size, size_t nmemb, void *stream)
{
	return fwrite(ptr, size, nmemb, (FILE *)stream);
}

size_t HTTPS_WriteString(void *ptr, size_t size, size_t nmemb, void *stream)
{
	CURLstring *s = (CURLstring *)stream;
	size_t new_len = s->len + size * nmemb;
	if (s->buffer == NULL)
		s->buffer = (char *)malloc(new_len + 1);
	else
	{
		char *tmp = (char *)realloc(s->buffer, new_len + 1);
		if (tmp != NULL)
			s->buffer = tmp;
	}

	memcpy(s->buffer + s->len, ptr, size * nmemb);
	s->buffer[new_len] = '\0';
	s->len = new_len;

	return size * nmemb;
}

void GScr_HTTPS_GetString()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: HTTPS_GetString(<url>)");
		return;
	}
	CURL *handle;
	CURLcode res;
	
	CURLstring str = CURL_StringInit();
	handle = curl_easy_init();
	if(handle) 
	{
		CURL_SetHeader(handle, CURLOPT_HTTPHEADER);
		curl_easy_setopt(handle, CURLOPT_URL, Plugin_Scr_GetString(0));
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HTTPS_WriteString);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, &str);
		CURL_SetOpts(handle);

		res = curl_easy_perform(handle);
		if (res != CURLE_OK)
		{
			Plugin_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddUndefined();
		}
		else if (str.buffer != NULL)
			Plugin_Scr_AddString(str.buffer);
		else
			Plugin_Scr_AddUndefined();

		curl_easy_cleanup(handle);
	}
	if (str.buffer != NULL)
		free(str.buffer);

	CURL_OptCleanup();
	CURL_HeaderCleanup();
}

void GScr_HTTPS_GetFile()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: HTTPS_GetFile(<filepath>, <url>)");
		return;
	}
	CURL *handle;
	CURLcode res;
	FILE *pagefile;

	handle = curl_easy_init();
	if (handle)
	{
		CURL_SetHeader(handle, CURLOPT_HTTPHEADER);
		curl_easy_setopt(handle, CURLOPT_URL, Plugin_Scr_GetString(1));
		curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HTTPS_Write);
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
		CURL_SetOpts(handle);

		pagefile = fopen(Plugin_Scr_GetString(0), "wb");
		if(pagefile) 
		{
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, pagefile);

			res = curl_easy_perform(handle);
			if (res != CURLE_OK)
			{
				Plugin_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
				Plugin_Scr_AddBool(qfalse);
			}
			else
				Plugin_Scr_AddBool(qtrue);

			fclose(pagefile);
		}
		else
			Plugin_Scr_AddBool(qfalse);

		curl_easy_cleanup(handle);
	}
	CURL_OptCleanup();
	CURL_HeaderCleanup();
}

void GScr_HTTPS_PostString()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: HTTPS_PostString(<string>, <url>)");
		return;
	}
	CURL *handle;
	CURLcode res;

	CURLstring str = CURL_StringInit();
	handle = curl_easy_init();
	if(handle) 
	{
		CURL_SetHeader(handle, CURLOPT_HTTPHEADER);
		curl_easy_setopt(handle, CURLOPT_URL, Plugin_Scr_GetString(1));
		curl_easy_setopt(handle, CURLOPT_POSTFIELDS, Plugin_Scr_GetString(0));
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HTTPS_WriteString);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, &str);
		CURL_SetOpts(handle);
 
		res = curl_easy_perform(handle);
		if(res != CURLE_OK)
		{
			Plugin_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddUndefined();
		}
		else if (str.buffer != NULL)
			Plugin_Scr_AddString(str.buffer);
		else
			Plugin_Scr_AddUndefined();

		curl_easy_cleanup(handle);
	}
	if (str.buffer != NULL)
		free(str.buffer);

	CURL_OptCleanup();
	CURL_HeaderCleanup();
}

void GScr_HTTPS_PostFile()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: HTTPS_PostFile(<filepath>, <url>)");
		return;
	}
	CURL *handle;
	CURLcode res;
	void *buffer = NULL;
	long length;
	FILE *fd;

	// Check file
	fd = fopen(Plugin_Scr_GetString(0), "rb");
	if (fd) 
	{
		fseek(fd, 0, SEEK_END);
		length = ftell(fd);
		fseek(fd, 0, SEEK_SET);
		buffer = malloc(length * sizeof(char));

		if (buffer)
			(void)!fread(buffer, 1, length, fd);
		fclose(fd);
	}
	else
	{
		Plugin_Printf("File not found.\n");
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Post file
	CURLstring str = CURL_StringInit();
	handle = curl_easy_init();
	if (handle) 
	{
		CURL_SetHeader(handle, CURLOPT_HTTPHEADER);
		curl_easy_setopt(handle, CURLOPT_URL, Plugin_Scr_GetString(1));
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, length);
		curl_easy_setopt(handle, CURLOPT_POSTFIELDS, buffer);
		curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HTTPS_WriteString);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, &str);
		CURL_SetOpts(handle);

		res = curl_easy_perform(handle);
		if (res != CURLE_OK)
		{
			Plugin_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else if (str.buffer != NULL)
			Plugin_Scr_AddString(str.buffer);
		else
			Plugin_Scr_AddBool(qfalse);

		curl_easy_cleanup(handle);
	}
	if (buffer != NULL)
		free(buffer);
	if (str.buffer != NULL)
		free(str.buffer);

	CURL_OptCleanup();
	CURL_HeaderCleanup();
}
