# HTTP

Functions for making HTTP and HTTPS requests.

> **Note:** Requests are not thread safe. Wrap all HTTP calls in a [critical section](async.md).

## Functions

- [HTTP_Init](#http_init)
- [HTTP_Free](#http_free)
- [HTTP_Get](#http_get)
- [HTTP_Post](#http_post)
- [HTTP_GetFile](#http_getfile)
- [HTTP_PostFile](#http_postfile)
- [HTTP_Response](#http_response)
- [HTTP_AddHeader](#http_addheader)
- [HTTP_HeaderCleanup](#http_headercleanup)
- [HTTP_AddOpt](#http_addopt)
- [HTTP_OptCleanup](#http_optcleanup)

---

## Example

```c
critical_enter("http");

json = "{\"login\":\"login\",\"password\":\"password\"}";
url = "http://httpbin.org/post";

request = HTTP_Init();
HTTP_AddHeader(request, "Accept: application/json");
HTTP_AddHeader(request, "Content-Type: application/json");
HTTP_Post(request, json, url);
AsyncWait(request);

response = HTTP_Response(request);
HTTP_Free(request);

critical_leave("http");
```

---

### `HTTP_Init()`

Initializes an HTTP request and returns a handle. Must be freed with `HTTP_Free` when done.

```c
request = HTTP_Init();
```

---

### `HTTP_Free(<request>)`

Frees an HTTP request handle and releases its resources.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |

```c
HTTP_Free(request);
```

---

### `HTTP_Get(<request>, <url>)`

Performs an HTTP GET request.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |
| `url` | string | The URL to fetch |

```c
request = HTTP_Init();
HTTP_Get(request, "http://httpbin.org/get");
AsyncWait(request);
response = HTTP_Response(request);
HTTP_Free(request);
```

---

### `HTTP_Post(<request>, <string>, <url>)`

Performs an HTTP POST request with a string body.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |
| `string` | string | The request body |
| `url` | string | The URL to post to |

```c
request = HTTP_Init();
HTTP_Post(request, "{\"key\":\"value\"}", "http://httpbin.org/post");
AsyncWait(request);
HTTP_Free(request);
```

---

### `HTTP_GetFile(<request>, <filepath>, <url>)`

Downloads a file from a URL and saves it to disk.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |
| `filepath` | string | Local path to save the downloaded file |
| `url` | string | The URL to download from |

```c
request = HTTP_Init();
HTTP_GetFile(request, "version.txt", "https://example.com/version.txt");
AsyncWait(request);
HTTP_Free(request);
```

---

### `HTTP_PostFile(<request>, <filepath>, <url>)`

Uploads a local file to a URL via HTTP POST.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |
| `filepath` | string | Local path of the file to upload |
| `url` | string | The URL to upload to |

```c
request = HTTP_Init();
HTTP_PostFile(request, "report.txt", "http://httpbin.org/post");
AsyncWait(request);
HTTP_Free(request);
```

---

### `HTTP_Response(<request>, <?chunkIndex>)`

Returns the response body as a string. Optionally specify a chunk index for large responses.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |
| `chunkIndex` | int | *(optional)* Index of the response chunk |

```c
response = HTTP_Response(request);
```

---

### `HTTP_AddHeader(<request>, <header>)`

Adds an HTTP header to the next request. Multiple headers can be set before sending.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |
| `header` | string | Header string in `"Key: Value"` format |

```c
HTTP_AddHeader(request, "Accept: application/json");
HTTP_AddHeader(request, "Content-Type: application/json");
```

---

### `HTTP_HeaderCleanup(<request>)`

Clears all headers previously set with `HTTP_AddHeader`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |

```c
HTTP_HeaderCleanup(request);
```

---

### `HTTP_AddOpt(<request>, <option>, <value>)`

Sets a libcurl option on the request. Refer to the [libcurl option list](https://curl.se/libcurl/c/curl_easy_setopt.html) for valid option codes.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |
| `option` | int | libcurl option constant |
| `value` | any | Value for the option |

```c
HTTP_AddOpt(request, 47, 1);
```

---

### `HTTP_OptCleanup(<request>)`

Clears all options previously set with `HTTP_AddOpt`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An HTTP request handle |

```c
HTTP_OptCleanup(request);
```
