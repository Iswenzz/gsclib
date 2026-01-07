# HTTP

**Requests are not thread safe. Use critical sections when needed**
**The example below uses GSC functions defined in [Async](https://github.com/Iswenzz/gsclib/blob/master/docs/async.md)**

## Example
```c
critical_enter("http");

json = "{\"login\":\"login\",\"password\":\"password\"}";
url = "http://httpbin.org/post";

request = HTTP_Init();
HTTP_AddHeader(request, "Accept: application/json,Content-Type: application/json");
HTTP_Post(request, json, url);
AsyncWait(request);

response = HTTP_Response(request);
HTTP_Free(request);

critical_leave("http");
```

#### ``HTTP_Init()``
Initialize an HTTP request.
The request should be freed when done using HTTP_Free.

```c
request = HTTP_Init();
```
<hr>

#### ``HTTP_Free(<request>)``
Free the HTTP request.

```c
HTTP_Free(request);
```
<hr>

#### ``HTTP_GetFile(<request>, <filepath>, <url>)``
Save a file from HTTP url.

```c
request = HTTP_Init();
HTTP_GetFile(request, "test/version.txt", "https://iswenzz.com:1337/speedrun_app/version.txt");
```
<hr>

#### ``HTTP_PostFile(<request>, <filepath>, <url>)``
Upload a file to HTTP url.

```c
request = HTTP_Init();
HTTP_PostFile(request, "test/version.txt", "http://httpbin.org/post");
```
<hr>

#### ``HTTP_Get(<request>, <url>)``
Get a string from HTTP url.

```c
request = HTTP_Init();
HTTP_Get(request, "http://httpbin.org/get");
```
<hr>

#### ``HTTP_Post(<request>, <string>, <url>)``
Post a string to HTTP url.

```c
request = HTTP_Init();
HTTP_Post(request, "{\"login\":\"login\",\"password\":\"password\"}", "http://httpbin.org/post");
```
<hr>

#### ``HTTP_Response(<request>, <?chunkIndex>)``
Get the HTTP response string.

```c
response = HTTP_Response(request);
```
<hr>

#### ``HTTP_AddHeader(<request>, <commands>)``
Set HTTP Header for the next requests.

```c
HTTP_AddHeader(request, "Accept: application/json");
HTTP_AddHeader(request, "Content-Type: application/json");
```
<hr>

#### ``HTTP_HeaderCleanup(<request>)``
Clean header set by HTTP_AddHeader.

```c
HTTP_HeaderCleanup(request);
```
<hr>

#### ``HTTP_AddOpt(<request>, <option>, <value>)``
Add a HTTP Option for the next request.

```c
HTTP_AddOpt(request, 47, 1);
```
<hr>

#### ``HTTP_OptCleanup(<request>)``
Clean all HTTP Option added by HTTP_AddOpt.

```c
HTTP_OptCleanup(request);
```
<hr>
