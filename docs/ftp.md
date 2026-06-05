# FTP

Functions for connecting to and transferring files over FTP, FTPS, and SFTP.

> **Note:** Requests are not thread safe. Wrap all FTP calls in a [critical section](async.md).

## Functions

- [FTP_Connect](#ftp_connect)
- [SFTP_Connect](#sftp_connect)
- [FTP_Close](#ftp_close)
- [FTP_Init](#ftp_init)
- [FTP_Free](#ftp_free)
- [FTP_GetFile](#ftp_getfile)
- [FTP_PostFile](#ftp_postfile)
- [FTP_Shell](#ftp_shell)
- [FTP_AddHeader](#ftp_addheader)
- [FTP_HeaderCleanup](#ftp_headercleanup)
- [FTP_AddOpt](#ftp_addopt)
- [FTP_OptCleanup](#ftp_optcleanup)

---

## Example

```c
critical_enter("ftp");

FTP_Connect("localhost", "root", "rootpassword", 21);

request = FTP_Init();
FTP_PostFile(request, "temp/test.txt", "/remote/test.txt");
AsyncWait(request);
FTP_Free(request);

FTP_Close();

critical_leave("ftp");
```

---

### `FTP_Connect(<host>, <user>, <password>, <port>)`

Connects to an FTP or FTPS server. Close the connection with `FTP_Close`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `host` | string | Hostname or IP address |
| `user` | string | FTP username |
| `password` | string | FTP password |
| `port` | int | Server port (typically `21`) |

```c
FTP_Connect("localhost", "root", "rootpassword", 21);
```

---

### `SFTP_Connect(<host>, <user>, <password>, <port>)`

Connects to an SFTP server. Close the connection with `FTP_Close`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `host` | string | Hostname or IP address |
| `user` | string | SFTP username |
| `password` | string | SFTP password |
| `port` | int | Server port (typically `22`) |

```c
SFTP_Connect("localhost", "root", "rootpassword", 22);
```

---

### `FTP_Close()`

Closes the active FTP/FTPS/SFTP connection.

```c
FTP_Close();
```

---

### `FTP_Init()`

Initializes an FTP request and returns a handle. Must be freed with `FTP_Free` when done.

```c
request = FTP_Init();
```

---

### `FTP_Free(<request>)`

Frees an FTP request handle and releases its resources.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |

```c
FTP_Free(request);
```

---

### `FTP_GetFile(<request>, <filepath>, <downloadfilepath>)`

Downloads a file from the server to a local path.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |
| `filepath` | string | Local path to save the downloaded file |
| `downloadfilepath` | string | Remote path of the file on the server |

```c
request = FTP_Init();
FTP_GetFile(request, "local/test.dll", "/remote/test.dll");
AsyncWait(request);
FTP_Free(request);
```

---

### `FTP_PostFile(<request>, <filepath>, <uploadfilepath>)`

Uploads a local file to the server.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |
| `filepath` | string | Local path of the file to upload |
| `uploadfilepath` | string | Destination path on the server |

```c
request = FTP_Init();
FTP_PostFile(request, "local/test.txt", "/remote/test.txt");
AsyncWait(request);
FTP_Free(request);
```

---

### `FTP_Shell(<request>)`

Executes FTP commands on the server. Commands must be set first with `FTP_AddHeader`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |

```c
request = FTP_Init();
FTP_AddHeader(request, "rename old.dll new.dll");
FTP_Shell(request);
FTP_Free(request);
```

---

### `FTP_AddHeader(<request>, <commands>)`

Sets FTP commands to be sent with the next request. Multiple commands can be comma-separated or use the protocol format.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |
| `commands` | string | FTP command string |

```c
FTP_AddHeader(request, "RNFR old.dll,RNTO new.dll");
```

---

### `FTP_HeaderCleanup(<request>)`

Clears all commands previously set with `FTP_AddHeader`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |

```c
FTP_HeaderCleanup(request);
```

---

### `FTP_AddOpt(<request>, <option>, <value>)`

Sets a libcurl option on the request. Refer to the [libcurl option list](https://curl.se/libcurl/c/curl_easy_setopt.html) for valid option codes.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |
| `option` | int | libcurl option constant |
| `value` | any | Value for the option |

```c
FTP_AddOpt(request, 47, 1);
```

---

### `FTP_OptCleanup(<request>)`

Clears all options previously set with `FTP_AddOpt`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An FTP request handle |

```c
FTP_OptCleanup(request);
```
