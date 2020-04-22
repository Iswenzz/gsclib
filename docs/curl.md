# [CURL](https://curl.haxx.se/)

#### ``CURL_Version()``
Print info about curl library.

Usage Example:
```c
CURL_Version();
```
<hr>

#### ``CURL_SetHeader(<commands>)``
Set CURL Header for the next requests, commands should be separated with a ",".

Usage Example:
```c
CURL_SetHeader("Accept: application/json,Content-Type: application/json");
CURL_SetHeader("RNFR libcurl.dll,RNTO test.dll");
CURL_SetHeader("rename libcurl.dll test.dll");
```
<hr>

#### ``CURL_HeaderCleanup()``
Clean header set by CURL_SetHeader.

Usage Example:
```c
CURL_HeaderCleanup();
```
<hr>

#### ``CURL_AddOpt(<option>, <value>)``
Add a CURL Option for the next request.

Usage Example:
```c
CURL_AddOpt(47, 1);
```
<hr>

#### ``CURL_OptCleanup()``
Clean all CURL Option added by CURL_AddOpt.

Usage Example:
```c
CURL_OptCleanup();
```
<hr>
