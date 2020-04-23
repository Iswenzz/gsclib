#pragma once
#include "curl.h"

/**
 * @brief 
 * File write function to use with CURL https write callback.
 */
size_t https_fwrite(void *ptr, size_t size, size_t nmemb, void *stream);

/**
 * @brief 
 * String write function to use with CURL https write callback.
 */
size_t https_write_string(void *ptr, size_t size, size_t nmemb, void *stream);

/**
 * @brief 
 * Upload a file to HTTP/HTTPS url.
 */
void GScr_HTTPS_PostFile();

/**
 * @brief 
 * Post a string to HTTP/HTTPS url.
 */
void GScr_HTTPS_PostString();

/**
 * @brief 
 * Save a file from HTTP/HTTPS url.
 */
void GScr_HTTPS_GetFile();

/**
 * @brief 
 * Get a string from HTTP/HTTPS url.
 */
void GScr_HTTPS_GetString();