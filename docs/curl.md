# [CURL](https://curl.haxx.se/)

#### ``CURL_Version()``
Print info about curl library.

```c
CURL_Version();
```
<hr>

#### ``CURL_AddHeader(<commands>)``
Set CURL Header for the next requests, commands should be separated with a ",".

```c
CURL_AddHeader("Accept: application/json,Content-Type: application/json");
CURL_AddHeader("RNFR libcurl.dll,RNTO test.dll");
CURL_AddHeader("rename libcurl.dll test.dll");
```
<hr>

#### ``CURL_HeaderCleanup()``
Clean header set by CURL_AddHeader.

```c
CURL_HeaderCleanup();
```
<hr>

#### ``CURL_AddOpt(<option>, <value>)``
Add a CURL Option for the next request.

```c
CURL_AddOpt(47, 1);
```
<hr>

#### ``CURL_OptCleanup()``
Clean all CURL Option added by CURL_AddOpt.

```c
CURL_OptCleanup();
```
<hr>
