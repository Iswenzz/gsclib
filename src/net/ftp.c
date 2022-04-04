#include "ftp.h"

#include <string.h>
#include <sys/stat.h>
#include <errno.h>

size_t ftp_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
	struct FtpFile *out = (struct FtpFile *)stream;
	if(!out->stream)
	{
		out->stream = fopen(out->filename, "wb");
		if(!out->stream)
			return -1;
	}
	return fwrite(buffer, size, nmemb, out->stream);
}

size_t ftp_fread(void *ptr, size_t size, size_t nmemb, void *stream)
{
	return (curl_off_t)fread(ptr, size, nmemb, (FILE *)stream);
}

void GScr_SFTP_Connect()
{
	if (Plugin_Scr_GetNumParam() != 4)
	{
		Plugin_Scr_Error("Usage: SFTP_Connect(<hostname>, <username>, <password>, <port>)");
		return;
	}
	Plugin_Scr_AddBool(i_curl_connect("sftp", Plugin_Scr_GetString(0), Plugin_Scr_GetString(1),
		Plugin_Scr_GetString(2), Plugin_Scr_GetInt(3)));
}

void GScr_FTP_Connect()
{
	if (Plugin_Scr_GetNumParam() != 4)
	{
		Plugin_Scr_Error("Usage: FTP_Connect(<hostname>, <username>, <password>, <port>)");
		return;
	}
	Plugin_Scr_AddBool(i_curl_connect("ftp", Plugin_Scr_GetString(0), Plugin_Scr_GetString(1),
		Plugin_Scr_GetString(2), Plugin_Scr_GetInt(3)));
}

void GScr_FTP_Close()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: FTP_Close()");
		return;
	}
	Plugin_Scr_AddBool(i_curl_close());
}

void GScr_FTP_Shell()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: FTP_Shell() - Execute header from CURL_AddHeader()");
		return;
	}
	CHECK_FTP_CONNECTION(ftp_instance);
	CURLcode res;

	if(ftp_instance.curl)
	{
		curl_easy_reset(ftp_instance.curl);

		i_curl_setheader(ftp_instance.curl, CURLOPT_QUOTE);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_URL, ftp_instance.url);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_PASSWORD, ftp_instance.password);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_PORT, ftp_instance.port);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		i_curl_setopts(ftp_instance.curl);

		res = curl_easy_perform(ftp_instance.curl);
		if(CURLE_OK != res)
		{
			Plugin_Printf("Error: curl_easy_perform: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else
			Plugin_Scr_AddBool(qtrue);
	}
	i_curl_opt_cleanup();
	i_curl_header_cleanup();
}

void GScr_FTP_PostFile()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: FTP_PostFile(<filepath>, <uploadtopath>)");
		return;
	}
	CHECK_FTP_CONNECTION(ftp_instance);
	const char *filepath = Plugin_Scr_GetString(0);

	CURLcode res;
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;

	if(stat(filepath, &file_info))
	{
		Plugin_Printf("Couldn't open '%s': %s\n", filepath, strerror(errno));
		Plugin_Scr_AddBool(qfalse);
		return;
	}
	fsize = (curl_off_t)file_info.st_size;
	Plugin_Printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);
	hd_src = fopen(filepath, "rb");
	if (!hd_src)
	{
		Plugin_Printf("File not found.\n");
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	if(ftp_instance.curl)
	{
		curl_easy_reset(ftp_instance.curl);

		char url[4096];
		strcpy(url, ftp_instance.url);
		strcat(url, Plugin_Scr_GetString(1));

		i_curl_setheader(ftp_instance.curl, CURLOPT_POSTQUOTE);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_URL, url);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_PASSWORD, ftp_instance.password);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_PORT, ftp_instance.port);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_READFUNCTION, ftp_fread);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_READDATA, hd_src);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		i_curl_setopts(ftp_instance.curl);

		res = curl_easy_perform(ftp_instance.curl);
		if(res != CURLE_OK)
		{
			Plugin_Printf("Error: curl_easy_perform: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else
			Plugin_Scr_AddBool(qtrue);
	}
	fclose(hd_src);

	i_curl_opt_cleanup();
	i_curl_header_cleanup();
}

void GScr_FTP_GetFile()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: FTP_GetFile(<savefilepath>, <download filepath>)");
		return;
	}
	CHECK_FTP_CONNECTION(ftp_instance);
	const char *filepath = Plugin_Scr_GetString(0);

	CURLcode res;
	struct FtpFile ftpfile = { filepath, NULL};

	if(ftp_instance.curl)
	{
		curl_easy_reset(ftp_instance.curl);

		char url[4096];
		strcpy(url, ftp_instance.url);
		strcat(url, Plugin_Scr_GetString(1));

		i_curl_setheader(ftp_instance.curl, CURLOPT_PREQUOTE);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_URL, url);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_PASSWORD, ftp_instance.password);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_PORT, ftp_instance.port);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_WRITEFUNCTION, ftp_fwrite);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_WRITEDATA, &ftpfile);
		curl_easy_setopt(ftp_instance.curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		i_curl_setopts(ftp_instance.curl);

		res = curl_easy_perform(ftp_instance.curl);
		if(CURLE_OK != res)
		{
			Plugin_Printf("Error: curl_easy_perform: %s\n", curl_easy_strerror(res));
			Plugin_Scr_AddBool(qfalse);
		}
		else
			Plugin_Scr_AddBool(qtrue);
	}
	if(ftpfile.stream)
		fclose(ftpfile.stream);

	i_curl_opt_cleanup();
	i_curl_header_cleanup();
}
