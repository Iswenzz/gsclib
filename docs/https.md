# HTTP/HTTPS

#### ``HTTPS_GetFile(<filepath>, <url>)``
Save a file from HTTP/HTTPS url.

Usage Example:
```c
HTTPS_GetFile("test/version.txt", "https://iswenzz.com:1337/speedrun_app/version.txt");
```
<hr>

#### ``HTTPS_PostFile(<filepath>, <url>)``
Upload a file to HTTP/HTTPS url.

Usage Example:
```c
HTTPS_PostFile("test/version.txt", "http://httpbin.org/post");
```
<hr>

#### ``HTTPS_GetString(<url>)``
Get a string from HTTP/HTTPS url.

Usage Example:
```c
HTTPS_GetString("http://httpbin.org/get");
```
<hr>

#### ``HTTPS_PostString(<string>, <url>)``
Post a string to HTTP/HTTPS url.

Usage Example:
```c
HTTPS_PostString("{\"login\":\"login\",\"password\":\"password\"}", "http://httpbin.org/post");
```
<hr>