# Zip

#### ``ZIP_Open(<filepath>)``
Open a zip file.

```c
zip = ZIP_Open("file.zip");
```
<hr>

#### ``ZIP_Close(<zip>)``
Close a zip file.

```c
ZIP_Close(zip);
```
<hr>

#### ``ZIP_Add(<zip>, <filepath>, <outpath>)``
Add a file to the zip archive.

```c
ZIP_Add(zip, "temp/test.txt", "test.txt");
```
<hr>

#### ``ZIP_Rename(<zip>, <filepath>, <renamepath>)``
Rename a file in the zip archive.

```c
ZIP_Rename(zip, "test.txt", "test_new.txt");
```
<hr>

#### ``ZIP_Close(<zip>, <filepath>)``
Delete a file in the zip archive.

```c
ZIP_Delete(zip, filepath);
```
<hr>
