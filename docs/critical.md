# Critical Sections

Critical sections are used to protect shared resources from concurrent access, which can lead to race conditions and other synchronization issues. By executing a critical section as an atomic operation, you can ensure that the shared resource is not modified by another process or thread while the critical section is being executed.

## Example

You can define the following GSC functions to ensure concurrent access to MySQL/HTTP/FTP/CURL etc...

```c
main()
{
	critical("mysql");
	critical("http");
	critical("ftp");
	critical("curl");
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

critical_release(id)
{
	LeaveCriticalSection(id);
}

AsyncWait(request)
{
	status = AsyncStatus(request);
	while (status <= 1)
	{
		wait 0.05;
		status = AsyncStatus(request);
	}
	return status;
}
```

#### ``CriticalSection(<id>)``
Creates a new critical section.

```c
CriticalSection("mysql");
```
<hr>

#### ``CriticalSections()``
Get the critical sections.

```c
sections = CriticalSections();
keys = getArrayKeys(sections);
```
<hr>

#### ``EnterCriticalSection(<id>)``
Enter a critical section.
Returns false if the critical section is already in use.

```c
EnterCriticalSection("mysql");
```
<hr>

#### ``LeaveCriticalSection(<id>)``
Leave a critical section.

```c
LeaveCriticalSection("mysql");
```
<hr>
