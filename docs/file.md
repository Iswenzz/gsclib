# File

Functions for reading, writing, and managing files and directories on the host filesystem.

## Functions

- [FILE_Create](#file_create)
- [FILE_Open](#file_open)
- [FILE_Close](#file_close)
- [FILE_Exists](#file_exists)
- [FILE_Delete](#file_delete)
- [FILE_Read](#file_read)
- [FILE_ReadLine](#file_readline)
- [FILE_ReadLines](#file_readlines)
- [FILE_Write](#file_write)
- [FILE_WriteLine](#file_writeline)
- [FILE_WriteLines](#file_writelines)
- [FILE_Seek](#file_seek)
- [FILE_MkDir](#file_mkdir)
- [FILE_RmDir](#file_rmdir)
- [FILE_ReadDir](#file_readdir)

---

### `FILE_Create(<path>)`

Creates a new empty file at the given path.

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | string | Path of the file to create |

```c
FILE_Create("test.txt");
```

---

### `FILE_Open(<path>, <mode>)`

Opens a file and returns a file handle. Use the handle with other `FILE_*` functions.

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | string | Path of the file to open |
| `mode` | string | File mode (e.g. `"r"`, `"w"`, `"a"`, `"w+"`) |

```c
file = FILE_Open("test.txt", "w+");
```

---

### `FILE_Close(<file>)`

Closes an open file handle.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |

```c
FILE_Close(file);
```

---

### `FILE_Exists(<path>)`

Returns `true` if a file exists at the given path, `false` otherwise.

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | string | Path to check |

```c
if (FILE_Exists("test.txt"))
{
    // ...
}
```

---

### `FILE_Delete(<path>)`

Deletes the file at the given path.

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | string | Path of the file to delete |

```c
FILE_Delete("test.txt");
```

---

### `FILE_Read(<file>)`

Reads the entire file contents and returns it as a string.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |

```c
string = FILE_Read(file);
```

---

### `FILE_ReadLine(<file>)`

Reads and returns the next line from the file.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |

```c
line = FILE_ReadLine(file);
```

---

### `FILE_ReadLines(<file>)`

Reads all lines from the file and returns them as an array of strings.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |

```c
lines = FILE_ReadLines(file);
for (i = 0; i < lines.size; i++)
    ComPrintLn(lines[i]);
```

---

### `FILE_Write(<file>, <string>, <?arguments...>)`

Writes a formatted string to the file.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |
| `string` | string | Content or format string to write |
| `arguments` | any | Optional format arguments |

```c
FILE_Write(file, "hello");
FILE_Write(file, "%d %s", 10, "world");
```

---

### `FILE_WriteLine(<file>, <string>, <?arguments...>)`

Writes a formatted string followed by a newline to the file.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |
| `string` | string | Content or format string to write |
| `arguments` | any | Optional format arguments |

```c
FILE_WriteLine(file, "hello");
FILE_WriteLine(file, "%d %s", 10, "world");
```

---

### `FILE_WriteLines(<file>, <lines>)`

Writes an array of strings to the file, each on its own line.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |
| `lines` | array | Array of strings to write |

```c
FILE_WriteLines(file, lines);
```

---

### `FILE_Seek(<file>, <offset>)`

Sets the file buffer read/write position.

| Parameter | Type | Description |
|-----------|------|-------------|
| `file` | handle | An open file handle |
| `offset` | int | Byte offset from the beginning of the file |

```c
FILE_Seek(file, 0);
```

---

### `FILE_MkDir(<path>)`

Creates a directory at the given path.

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | string | Path of the directory to create |

```c
FILE_MkDir("saves");
```

---

### `FILE_RmDir(<path>)`

Deletes the directory at the given path.

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | string | Path of the directory to delete |

```c
FILE_RmDir("saves");
```

---

### `FILE_ReadDir(<path>)`

Returns an array of file names found in the given directory.

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | string | Path of the directory to list |

```c
files = FILE_ReadDir("saves");
for (i = 0; i < files.size; i++)
    ComPrintLn(files[i]);
```
