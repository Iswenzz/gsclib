# Async

Critical sections protect shared resources from concurrent access and race conditions. Wrapping HTTP, FTP, and MySQL calls in a critical section ensures that only one coroutine accesses a resource at a time.

## Functions

- [CriticalSection](#criticalsection)
- [CriticalSections](#criticalsections)
- [StatusCriticalSections](#statuscriticalsections)
- [EnterCriticalSection](#entercriticalsection)
- [LeaveCriticalSection](#leavecriticalsection)

---

## Usage pattern

The following GSC helpers are the recommended way to manage critical sections across your scripts. Define them once and reuse them everywhere.

```c
main()
{
    critical("mysql");
    critical("http");
    critical("ftp");
}

critical(id)
{
    CriticalSection(id);
}

critical_enter(id)
{
    while (!EnterCriticalSection(id))
        wait 0.05;
}

critical_leave(id)
{
    LeaveCriticalSection(id);
}

waitCriticalSections()
{
    while (!StatusCriticalSections())
        wait 0.05;
}

AsyncWait(request)
{
    status = AsyncStatus(request);
    while (status == 0 || status == 1)
    {
        wait 0.05;
        status = AsyncStatus(request);
    }
    return status;
}

levelRestart(persist)
{
    game["ended"] = true;
    waitCriticalSections();
    map_restart(persist);
}

levelExit(persist)
{
    game["ended"] = true;
    waitCriticalSections();
    exitLevel(persist);
}
```

---

## Functions

### `CriticalSection(<id>)`

Creates a new critical section with the given identifier.

| Parameter | Type | Description |
|-----------|------|-------------|
| `id` | string | Unique name for the critical section |

```c
CriticalSection("mysql");
```

---

### `CriticalSections()`

Returns all registered critical sections as a string-indexed array.

```c
sections = CriticalSections();
keys = getArrayKeys(sections);
```

---

### `StatusCriticalSections()`

Returns `false` if any critical section is currently locked, `true` otherwise. Useful for waiting until all async work is done before restarting or exiting.

```c
status = StatusCriticalSections();
```

---

### `EnterCriticalSection(<id>)`

Attempts to enter the critical section. Returns `false` if it is already in use by another coroutine.

| Parameter | Type | Description |
|-----------|------|-------------|
| `id` | string | Name of the critical section to enter |

```c
while (!EnterCriticalSection("mysql"))
    wait 0.05;
```

---

### `LeaveCriticalSection(<id>)`

Releases the critical section so other coroutines can enter it.

| Parameter | Type | Description |
|-----------|------|-------------|
| `id` | string | Name of the critical section to leave |

```c
LeaveCriticalSection("mysql");
```
