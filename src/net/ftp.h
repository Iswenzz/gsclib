#pragma once
#include "curl.h"
#include <CGSC/cgsc.h>

/// <summary>
/// File write function to use with ftp CURL write callback.
/// </summary>
/// <returns></returns>
size_t FTP_Write(void *buffer, size_t size, size_t nmemb, void *stream);

/// <summary>
/// File read function to use with ftp CURL read callback.
/// </summary>
/// <returns></returns>
size_t FTP_Read(void *ptr, size_t size, size_t nmemb, void *stream);

/// <summary>
/// Connect to an SFTP server, the connection can be closed with FTP_Close.
/// </summary>
void GScr_SFTP_Connect();

/// <summary>
/// Connect to an FTP/FTPS server, the connection can be closed with FTP_Close.
/// </summary>
void GScr_FTP_Connect();

/// <summary>
/// Close the FTP/FTPS/SFTP connection.
/// </summary>
void GScr_FTP_Close();

/// <summary>
/// Execute a command to the FTP/FTPS/SFTP server.
/// The commands should be set with CURL_AddHeader.
/// </summary>
void GScr_FTP_Shell();

/// <summary>
/// Upload a file to the FTP/FTPS/SFTP server.
/// </summary>
void GScr_FTP_PostFile();

/// <summary>
/// Download a file from the FTP/FTPS/SFTP server.
/// </summary>
void GScr_FTP_GetFile();
