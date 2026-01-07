# FTP/FTPS/SFTP

**Requests are not thread safe. Use critical sections when needed**
**The example below uses GSC functions defined in [Async](https://github.com/Iswenzz/gsclib/blob/master/docs/async.md)**

## Example
```c
critical_enter("ftp");

request = FTP_Init();
FTP_PostFile(request, "temp/test.txt", "get.txt");
AsyncWait(request);
FTP_Free(request);

critical_leave("ftp");
```

#### ``SFTP_Connect(<host>, <user>, <password>, <port>)``
Connect to an SFTP server, the connection can be closed with FTP_Close.

```c
SFTP_Connect("localhost", "root", "rootpassword", 22);
```
<hr>

#### ``FTP_Connect(<host>, <user>, <password>, <port>)``
Connect to an FTP/FTPS server, the connection can be closed with FTP_Close.

```c
FTP_Connect("localhost", "root", "rootpassword", 21);
```
<hr>

#### ``FTP_Close()``
Close the FTP/FTPS/SFTP connection.

```c
FTP_Close();
```
<hr>

#### ``FTP_Init()``
Initialize a FTP request.
The request should be freed when done using FTP_Free.

```c
request = FTP_Init();
```
<hr>

#### ``FTP_Free(<request>)``
Initialize a FTP request.

```c
FTP_Free(request);
```
<hr>

#### ``FTP_Shell(<request>)``
Execute a command to the FTP/FTPS/SFTP server.
The commands should be set with FTP_AddHeader.

```c
request = FTP_Init();
FTP_AddHeader(request, "rename libcurl.dll test.dll");
FTP_Shell(request);
```
<hr>

#### ``FTP_PostFile(<request>, <filepath>, <uploadfilepath>)``
Upload a file to the FTP/FTPS/SFTP server.

```c
request = FTP_Init();
FTP_PostFile(request, "libcurl.dll", "/user/libcurl.dll");
```
<hr>

#### ``FTP_GetFile(<request>, <filepath>, <downloadfilepath>)``
Download a file from the FTP/FTPS/SFTP server.

```c
request = FTP_Init();
FTP_GetFile(request, "test.dll", "/user/test.dll");
```
<hr>

#### ``FTP_AddHeader(<request>, <commands>)``
Set FTP Header for the next requests.

```c
FTP_AddHeader(request, "RNFR libcurl.dll,RNTO test.dll");
FTP_AddHeader(request, "rename libcurl.dll test.dll");
```
<hr>

#### ``FTP_HeaderCleanup(<request>)``
Clean header set by FTP_AddHeader.

```c
FTP_HeaderCleanup(request);
```
<hr>

#### ``FTP_AddOpt(<request>, <option>, <value>)``
Add a FTP Option for the next request.

```c
FTP_AddOpt(request, 47, 1);
```
<hr>

#### ``FTP_OptCleanup(<request>)``
Clean all FTP Option added by FTP_AddOpt.

```c
FTP_OptCleanup(request);
```
<hr>
