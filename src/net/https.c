#include "https.h"

#include <stdlib.h>
#include <string.h>

size_t https_fwrite(void *ptr, size_t size, size_t nmemb, void *stream)
{
	return fwrite(ptr, size, nmemb, (FILE *)stream);
}

size_t https_write_string(void *ptr, size_t size, size_t nmemb, void *stream)
{
	i_curl_string *s = (i_curl_string *)stream;
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
	CURL *curl;
	CURLcode res;
	
	i_curl_string str = i_string_init();
	curl = curl_easy_init();
	if(curl) 
	{
		i_curl_setheader(curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(curl, CURLOPT_URL, Plugin_Scr_GetString(0));
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, https_write_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
		i_curl_setopts(curl);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			Plugin_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddUndefined();
		}
		else if (str.buffer != NULL)
			Plugin_Scr_AddString(str.buffer);
		else
			Plugin_Scr_AddUndefined();

		curl_easy_cleanup(curl);
	}
	if (str.buffer != NULL)
		free(str.buffer);

	i_curl_opt_cleanup();
	i_curl_header_cleanup();
}

void GScr_HTTPS_GetFile()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: HTTPS_GetFile(<filepath>, <url>)");
		return;
	}
	CURL *curl;
	CURLcode res;
	FILE *pagefile;

	curl = curl_easy_init();
	if (curl)
	{
		i_curl_setheader(curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(curl, CURLOPT_URL, Plugin_Scr_GetString(1));
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, https_fwrite);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		i_curl_setopts(curl);

		pagefile = fopen(Plugin_Scr_GetString(0), "wb");
		if(pagefile) 
		{
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, pagefile);

			res = curl_easy_perform(curl);
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

		curl_easy_cleanup(curl);
	}
	i_curl_opt_cleanup();
	i_curl_header_cleanup();
}

void GScr_HTTPS_PostString()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: HTTPS_PostString(<string>, <url>)");
		return;
	}
	CURL *curl;
	CURLcode res;

	i_curl_string str = i_string_init();
	curl = curl_easy_init();
	if(curl) 
	{
		i_curl_setheader(curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(curl, CURLOPT_URL, Plugin_Scr_GetString(1));
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, Plugin_Scr_GetString(0));
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, https_write_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
		i_curl_setopts(curl);
 
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
		{
			Plugin_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else if (str.buffer != NULL)
			Plugin_Scr_AddString(str.buffer);
		else
			Plugin_Scr_AddBool(qtrue);

		curl_easy_cleanup(curl);
	}
	if (str.buffer != NULL)
		free(str.buffer);

	i_curl_opt_cleanup();
	i_curl_header_cleanup();
}

void GScr_HTTPS_PostFile()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: HTTPS_PostFile(<filepath>, <url>)");
		return;
	}
	CURL *curl;
	CURLcode res;
	void *buffer = NULL;
	long length;
	FILE *fd;

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

	i_curl_string str = i_string_init();
	curl = curl_easy_init();
	if (curl) 
	{
		i_curl_setheader(curl, CURLOPT_HTTPHEADER);
		curl_easy_setopt(curl, CURLOPT_URL, Plugin_Scr_GetString(1));
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, length);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, https_write_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
		i_curl_setopts(curl);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			Plugin_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else if (str.buffer != NULL)
			Plugin_Scr_AddString(str.buffer);
		else
			Plugin_Scr_AddBool(qtrue);

		curl_easy_cleanup(curl);
	}
	if (buffer != NULL)
		free(buffer);
	if (str.buffer != NULL)
		free(str.buffer);

	i_curl_opt_cleanup();
	i_curl_header_cleanup();
}
