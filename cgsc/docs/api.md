# API

### ``Macros``
Define a function for cod4x server and plugin export.

```c
EXPORT(float, Sys_GetCommonVersion());
```
<hr>

Checking CGSC plugin handler version:

```c
#if CGSC(4)
#elif CGSC(3)
#endif

#if CGSC_EQ(3)
#endif
```

```c
CHECK_UNSUPPORTED(CGSC_EQ(3));
```

```c
// major version, minor version
if (CGSCH >= 4 && CGSCL >= 0)
```
<hr>

### ASM
Adding a function to the plugin export (libcom_plugin):
Add a pexport with the function name in **asm/cgsc_export.asm**.

```assembly
pexport FunctionName
```
Renaming a function to export:

```assembly
ralias Com_Printf CGSC_Printf
```
<hr>

#### ``CGSC_Version()``
Get the CGSC version.

```c
if (CGSC_Version() >= 3.0)
```
<hr>

#### ``CGSC_Unsupported(<condition>)``
Check for unsupported version.

```c
if (CGSC_Unsupported(version == 3.0))
```
<hr>

#### ``CGSC_UnsupportedMessage(<condition>, <message>)``
Check for unsupported version.

```c
if (CGSC_Unsupported(version == 3.0, "Unsupported version"))
```
<hr>

#### ``Sys_GetCommonVersion()``
Get the CoD4x server version.

```c
if (Sys_GetCommonVersion() >= 20.0)
```
<hr>

#### ``fmt(char *format, ...)``
Format a string.

```c
Scr_Error(fmt("Invalid argument number %d", paramnum));
```
<hr>
