# File

#### ``FILE_Create(<path>)``
Create an empty file.

```c
FILE_Create("test.txt");
```
<hr>

#### ``FILE_Open(<path>, <mode>)``
Open a file with the specified mode.

```c
file = FILE_Open("test.txt", "w+");
```
<hr>

#### ``FILE_Close(<file>)``
Close a file.

```c
FILE_Close(file);
```
<hr>

#### ``FILE_Exists(<path>)``
Check if a file exists.

```c
val = FILE_Exists("test.txt");
```
<hr>

#### ``FILE_Read(<file>)``
Read a file to a string value.

```c
string = FILE_Read(file);
```
<hr>

#### ``FILE_Write(<file>, <string>, <?arguments...>)``
Write a string to a file.

```c
FILE_Write(file, "test");
FILE_Write(file, "%d %s", 10, "Iswenzz");
```
<hr>

#### ``FILE_ReadLine(<file>)``
Read a line from a file.

```c
line = FILE_ReadLine(file);
```
<hr>

#### ``FILE_WriteLine(<file>, <string>, <?arguments...>)``
Write a new line to a file.

```c
FILE_WriteLine(file, "test");
FILE_WriteLine(file, "%d %s", 10, "Iswenzz");
```
<hr>

#### ``FILE_Seek(<file>, <offset>)``
Set the file buffer position.

```c
FILE_Seek(file, 0);
```
<hr>

#### ``FILE_Delete(<path>)``
Delete a file.

```c
FILE_Delete("test.txt");
```
<hr>

#### ``FILE_MkDir(<path>)``
Create a directory.

```c
FILE_MkDir("name");
```
<hr>

#### ``FILE_RmDir(<path>)``
Delete a directory.

```c
FILE_RmDir("name");
```
<hr>

#### ``FILE_ReadDir(<path>)``
Retrieve all file names from a directory.

```c
files = FILE_ReadDir("name");
```
<hr>
