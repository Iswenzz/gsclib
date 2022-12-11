# HTTP

### WARNING: **Requests are not thread safe, you'll need your own scripts in GSC to handle one request at a time !**

#### ``HTTP_GetFile(<filepath>, <url>)``
Save a file from HTTP url.

```c
HTTP_GetFile("test/version.txt", "https://iswenzz.com:1337/speedrun_app/version.txt");
```
<hr>

#### ``HTTP_PostFile(<filepath>, <url>)``
Upload a file to HTTP url.

```c
HTTP_PostFile("test/version.txt", "http://httpbin.org/post");
```
<hr>

#### ``HTTP_GetString(<url>)``
Get a string from HTTP url.

```c
HTTP_GetString("http://httpbin.org/get");
```
<hr>

#### ``HTTP_PostString(<string>, <url>)``
Post a string to HTTP url.

```c
HTTP_PostString("{\"login\":\"login\",\"password\":\"password\"}", "http://httpbin.org/post");
```
<hr>
