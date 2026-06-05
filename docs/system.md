# System

Core library functions for initialization, versioning, async request management, and system-level operations.

## Functions

- [GSCLIB_Init](#gsclib_init)
- [GSCLIB_Version](#gsclib_version)
- [CoD4X_Version](#cod4x_version)
- [CURL_Version](#curl_version)
- [System](#system)
- [GetSysTime](#getsystime)
- [Exit](#exit)
- [AsyncStatus](#asyncstatus)
- [AsyncCancel](#asynccancel)

---

### `GSCLIB_Init()`

Initializes the gsclib library. Must be called once in `main()` before using any other gsclib functions.

```c
main()
{
    GSCLIB_Init();
}
```

---

### `GSCLIB_Version()`

Returns the gsclib version string.

```c
version = GSCLIB_Version();
```

---

### `CoD4X_Version()`

Returns the CoD4X version string.

```c
version = CoD4X_Version();
```

---

### `CURL_Version()`

Returns the libcurl version string.

```c
version = CURL_Version();
```

---

### `System(<command>)`

Executes a shell command on the host system.

| Parameter | Type | Description |
|-----------|------|-------------|
| `command` | string | The shell command to execute |

```c
System("ls");
```

---

### `GetSysTime()`

Returns the current system time in milliseconds.

```c
time = GetSysTime();
```

---

### `Exit(<code>)`

Exits the server process with the given exit code.

| Parameter | Type | Description |
|-----------|------|-------------|
| `code` | int | Exit code |

```c
Exit(0);
```

---

### `AsyncStatus(<request>)`

Returns the current status of an async request.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An async request handle |

**Return values:**

| Value | Meaning |
|-------|---------|
| `0` | Uninitialized |
| `1` | Pending |
| `2` | Successful |
| `3` | Failure |

```c
status = AsyncStatus(request);
```

---

### `AsyncCancel(<request>)`

Cancels a pending async request.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | An async request handle |

```c
AsyncCancel(request);
```
