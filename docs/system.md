# System

#### ``System(<command>)``
Execute a system command.

```c
System("ls");
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
