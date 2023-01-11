# FTP/FTPS/SFTP

### WARNING: **Requests are not thread safe. Use critical sections when needed**

## Example
```c
critical_enter("ftp");

request = FTP_Init();
FTP_PostFile(request, "temp/test.txt", "get.txt");
status = AsyncWait(request);
FTP_Free(request);

critical_leave("ftp");
```
**The example above use GSC functions defined in [Critical Sections](https://github.com/Iswenzz/gsclib/blob/master/docs/critical.md)**

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
The commands should be set with CURL_AddHeader.

```c
request = FTP_Init();
CURL_AddHeader(request, "rename libcurl.dll test.dll");
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
