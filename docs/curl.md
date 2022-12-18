# [CURL](https://curl.haxx.se/)

#### ``CURL_Version()``
Print info about curl library.

```c
CURL_Version();
```
<hr>

#### ``CURL_AddHeader(<request>, <commands>)``
Set CURL Header for the next requests.

```c
CURL_AddHeader(request, "Accept: application/json");
CURL_AddHeader(request, "Content-Type: application/json");
CURL_AddHeader(request, "RNFR libcurl.dll,RNTO test.dll");
CURL_AddHeader(request, "rename libcurl.dll test.dll");
```
<hr>

#### ``CURL_HeaderCleanup(<request>)``
Clean header set by CURL_AddHeader.

```c
CURL_HeaderCleanup(request);
```
<hr>

#### ``CURL_AddOpt(<request>, <option>, <value>)``
Add a CURL Option for the next request.

```c
CURL_AddOpt(request, 47, 1);
```
<hr>

#### ``CURL_OptCleanup(<request>)``
Clean all CURL Option added by CURL_AddOpt.

```c
CURL_OptCleanup(request);
```
<hr>
