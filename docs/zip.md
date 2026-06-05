# Zip

Functions for creating and manipulating zip archives.

## Functions

- [ZIP_Open](#zip_open)
- [ZIP_Close](#zip_close)
- [ZIP_Add](#zip_add)
- [ZIP_Rename](#zip_rename)
- [ZIP_Delete](#zip_delete)

---

### `ZIP_Open(<filepath>)`

Opens a zip archive and returns a handle. Creates the file if it does not exist.

| Parameter | Type | Description |
|-----------|------|-------------|
| `filepath` | string | Path to the zip file |

```c
zip = ZIP_Open("archive.zip");
```

---

### `ZIP_Close(<zip>)`

Closes an open zip archive and flushes all changes to disk.

| Parameter | Type | Description |
|-----------|------|-------------|
| `zip` | handle | An open zip handle |

```c
ZIP_Close(zip);
```

---

### `ZIP_Add(<zip>, <filepath>, <outpath>)`

Adds a file from the filesystem into the zip archive.

| Parameter | Type | Description |
|-----------|------|-------------|
| `zip` | handle | An open zip handle |
| `filepath` | string | Path of the source file on disk |
| `outpath` | string | Destination path inside the archive |

```c
zip = ZIP_Open("archive.zip");
ZIP_Add(zip, "temp/test.txt", "test.txt");
ZIP_Close(zip);
```

---

### `ZIP_Rename(<zip>, <filepath>, <renamepath>)`

Renames a file inside the zip archive.

| Parameter | Type | Description |
|-----------|------|-------------|
| `zip` | handle | An open zip handle |
| `filepath` | string | Current path of the file inside the archive |
| `renamepath` | string | New path for the file inside the archive |

```c
ZIP_Rename(zip, "test.txt", "test_renamed.txt");
```

---

### `ZIP_Delete(<zip>, <filepath>)`

Deletes a file from inside the zip archive.

| Parameter | Type | Description |
|-----------|------|-------------|
| `zip` | handle | An open zip handle |
| `filepath` | string | Path of the file inside the archive to delete |

```c
ZIP_Delete(zip, "test.txt");
```
