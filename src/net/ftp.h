#pragma once
#include "curl.h"

/**
 * @brief 
 * File write function to use with ftp CURL write callback.
 */
size_t ftp_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);

/**
 * @brief 
 * File read function to use with ftp CURL read callback.
 */
size_t ftp_fread(void *ptr, size_t size, size_t nmemb, void *stream);

/**
 * @brief 
 * Connect to an SFTP server, the connection can be closed with FTP_Close.
 */
void GScr_SFTP_Connect();

/**
 * @brief 
 * Connect to an FTP/FTPS server, the connection can be closed with FTP_Close.
 */
void GScr_FTP_Connect();

/**
 * @brief 
 * Close the FTP/FTPS/SFTP connection.
 */
void GScr_FTP_Close();

/**
 * @brief 
 * Execute a command to the FTP/FTPS/SFTP server.
 * The commands should be set with CURL_SetHeader.
 */
void GScr_FTP_Shell();

/**
 * @brief 
 * Upload a file to the FTP/FTPS/SFTP server.
 */
void GScr_FTP_PostFile();

/**
 * @brief 
 * Download a file from the FTP/FTPS/SFTP server.
 */
void GScr_FTP_GetFile();
