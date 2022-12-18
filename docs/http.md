# HTTP

### WARNING: **Requests are not thread safe, you'll need your own scripts in GSC to handle one request at a time !**

## Example
```c
json = "{\"login\":\"login\",\"password\":\"password\"}";
url = "http://httpbin.org/post";

request = HTTP_Init();
CURL_AddHeader(request, "Accept: application/json,Content-Type: application/json");
HTTP_Post(request, json, url);

while (AsyncStatus(request) <= 1)
	wait 0.05;

response = HTTP_Response(request);
HTTP_Free(request);
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

#### ``HTTP_GetString(<request>, <url>)``
Get a string from HTTP url.

```c
request = HTTP_Init();
HTTP_GetString(request, "http://httpbin.org/get");
```
<hr>

#### ``HTTP_PostString(<request>, <string>, <url>)``
Post a string to HTTP url.

```c
request = HTTP_Init();
HTTP_PostString(request, "{\"login\":\"login\",\"password\":\"password\"}", "http://httpbin.org/post");
```
<hr>
