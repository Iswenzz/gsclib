# FTP/FTPS/SFTP

### WARNING: **Requests are not thread safe, you'll need your own scripts in GSC to handle one request at a time !**

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

#### ``FTP_Shell()``
Execute a command to the FTP/FTPS/SFTP server.
The commands should be set with CURL_AddHeader.

```c
CURL_AddHeader("rename libcurl.dll test.dll");
FTP_Shell();
```
<hr>

#### ``FTP_PostFile(<filepath>, <uploadfilepath>)``
Upload a file to the FTP/FTPS/SFTP server.

```c
FTP_PostFile("libcurl.dll", "/user/libcurl.dll");
```
<hr>

#### ``FTP_GetFile(<filepath>, <downloadfilepath>)``
Download a file from the FTP/FTPS/SFTP server.

```c
FTP_GetFile("test.dll", "/user/test.dll");
```
<hr>
