# gsclib

[![Checks](https://img.shields.io/github/checks-status/Iswenzz/gsclib/master?logo=github)](https://github.com/Iswenzz/gsclib/actions)
[![CodeFactor](https://img.shields.io/codefactor/grade/github/Iswenzz/gsclib?label=codefactor&logo=codefactor)](https://www.codefactor.io/repository/github/iswenzz/gsclib)
[![License](https://img.shields.io/github/license/Iswenzz/gsclib?color=blue&logo=gitbook&logoColor=white)](https://github.com/Iswenzz/gsclib/blob/master/LICENSE)

``gsclib`` acts as a standard library extension for the Call of Duty 4 scripting language. The features this library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expression (PCRE2) support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion/fmt and other type utilities, ZIP files, async workers, and much more. More detailed information on each feature can be found in the documentation section.

## Features & Documentation
* [HTTP/HTTPS Client](https://github.com/Iswenzz/gsclib/blob/master/docs/http.md)
* [FTP/FTPS/SFTP Client](https://github.com/Iswenzz/gsclib/blob/master/docs/ftp.md)
* [Regular Expression (PCRE2)](https://github.com/Iswenzz/gsclib/blob/master/docs/regex.md)
* [Language Integrated Query (Linq)](https://github.com/Iswenzz/gsclib/blob/master/docs/linq.md)
* [MySQL](https://github.com/Iswenzz/gsclib/blob/master/docs/mysql.md)
* [Critical Sections](https://github.com/Iswenzz/gsclib/blob/master/docs/critical.md)
* [Utilities](https://github.com/Iswenzz/gsclib/blob/master/docs/utility.md)
* [File](https://github.com/Iswenzz/gsclib/blob/master/docs/file.md)
* [System](https://github.com/Iswenzz/gsclib/blob/master/docs/system.md)
* [Zip](https://github.com/Iswenzz/gsclib/blob/master/docs/zip.md)
* [Player](https://github.com/Iswenzz/gsclib/blob/master/docs/player.md)
* [Math](https://github.com/Iswenzz/gsclib/blob/master/docs/math.md)

## Instructions
In order to use this library, you'll need to compile the binary and place it to the CoD4 ``plugins`` directory.
Then you can simply use ``loadplugin gsclib`` in your ``server.cfg`` or as CLI arguments.

To initialize gsclib library you need to call ``GSCLIB_Init()`` at the start of your mod entry point.

```c
main()
{
	GSCLIB_Init();
}
```

## Server
1. Edit plugin_handler.h then recompile the server with a clean obj directory:
```c
#define MAX_SCRIPTFUNCTIONS 256
```

## Building (Linux)
_Pre-Requisites:_
1. [CGSC](https://github.com/Iswenzz/CGSC) and it's pre-requisites.
2. [CMake](https://cmake.org/) and [vcpkg](https://vcpkg.io/en/).

_Build Command:_

	mkdir build && cd build
	cmake .. -DCMAKE_TOOLCHAIN_FILE=.vcpkg/linux.cmake
	cmake --build .

## Building (Windows)
_Pre-Requisites:_
1. [CGSC](https://github.com/Iswenzz/CGSC) and it's pre-requisites.
2. [CMake](https://cmake.org/) and [vcpkg](https://vcpkg.io/en/).

**Using the Developer Command Prompt for Visual Studio**
_Build Command:_

    scripts/build_libcom.bat
	mkdir build && cd build
	cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=.vcpkg/windows.cmake
	cmake --build .

## [Download](https://github.com/Iswenzz/gsclib/releases)

## Troubleshouting
For resolving missing dependencies you can use the [ldd](https://man7.org/linux/man-pages/man1/ldd.1.html) command for Linux, and [Dependency Walker](https://www.dependencywalker.com/) for Windows.

## Contributors:
***Note:*** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.
