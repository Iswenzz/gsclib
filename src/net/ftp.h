#pragma once
#include "curl.h"

size_t ftp_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);
size_t ftp_fread(void *ptr, size_t size, size_t nmemb, void *stream);

void GScr_SFTP_Connect();
void GScr_FTP_Connect();
void GScr_FTP_Close();
void GScr_FTP_Shell();
void GScr_FTP_PostFile();
void GScr_FTP_GetFile();