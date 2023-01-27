# System

#### ``GSCLIB_Init()``
Initialize gsclib library, this should be called at the start of your mod entry point.

```c
main()
{
	GSCLIB_Init();
}
```
<hr>

#### ``System(<command>)``
Execute a system command.

```c
System("ls");
```
<hr>

#### ``AsyncStatus(<request>)``
Get the status of an async request (MySQL, CURL, FTP, HTTP).

0 = uninitialized
1 = pending
2 = successful
3 = failure

```c
status = AsyncStatus(request);
```
<hr>

#### ``GetSysTime()``
Get the system time in milliseconds.

```c
time = GetSysTime();
```
<hr>

#### ``Exit(<code>)``
Exit the program.

```c
Exit(0);
```
<hr>

#### ``ComPrint(<fmt>, <?arguments...>)``
Print a formatted message to the console output.

```c
a = "Iswenzz";

ComPrint("Hello World!");
ComPrint("Hello %s!", a);
```
<hr>

#### ``ComPrintLn(<fmt>, <?arguments...>)``
Print a formatted message on a new line to the console output.

```c
a = "Iswenzz";

ComPrintLn("Hello World!");
ComPrintLn("Hello %s!", a);
ComPrintLn();
```
<hr>

#### ``SysPrint(<fmt>, <?arguments...>)``
Print a formatted message to the system output.

```c
a = "Iswenzz";

SysPrint("Hello World!");
SysPrint("Hello %s!", a);
```
<hr>

#### ``SysPrintLn(<fmt>, <?arguments...>)``
Print a formatted message on a new line to the system output.

```c
a = "Iswenzz";

SysPrintLn("Hello World!");
SysPrintLn("Hello %s!", a);
SysPrintLn();
```
<hr>

#### ``CoD4X_Version()``
Get the CoD4X version.

```c
version = CoD4X_Version();
```
<hr>

#### ``CGSC_Version()``
Get the CGSC version.

```c
version = CGSC_Version();
```
<hr>


#### ``GSCLIB_Version()``
Get the gsclib version.

```c
version = GSCLIB_Version();
```
<hr>

