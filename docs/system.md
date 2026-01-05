# System

#### ``System(<command>)``
Execute a system command.

```c
System("ls");
```
<hr>

#### ``AsyncStatus(<request>)``
Get the status of an async request.

0 = Uninitialized
1 = Pending
2 = Successful
3 = Failure

```c
status = AsyncStatus(request);
```
<hr>

#### ``AsyncCancel(<request>)``
Cancel an async request.

```c
state = AsyncCancel(request);
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

#### ``CoD4X_Version()``
Get the CoD4X version.

```c
version = CoD4X_Version();
```
<hr>

#### ``GSCLIB_Version()``
Get the gsclib version.

```c
version = GSCLIB_Version();
```
<hr>

