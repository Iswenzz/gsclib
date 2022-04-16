# gsclib
[![Build status](https://ci.appveyor.com/api/projects/status/wb0m9puc58f5d74w?svg=true)](https://ci.appveyor.com/project/Iswenzz/gsclib)
[![CodeFactor](https://www.codefactor.io/repository/github/iswenzz/gsclib/badge)](https://www.codefactor.io/repository/github/iswenzz/gsclib)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

``gsclib`` acts as a standard library extension for the Call of Duty 4 scripting language. The features this library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expression (PCRE2) support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion/fmt and other type utilities, ZIP files, and much more. More detailed information on each feature can be found in the documentation section.

## Features & Documentation
* [HTTP/HTTPS client](https://github.com/Iswenzz/gsclib/blob/master/docs/https.md)
* [FTP/FTPS/SFTP client](https://github.com/Iswenzz/gsclib/blob/master/docs/ftp.md)
* [Regular expression (PCRE2)](https://github.com/Iswenzz/gsclib/blob/master/docs/regex.md)
* [Language Integrated Query (Linq)](https://github.com/Iswenzz/gsclib/blob/master/docs/linq.md)
* [MySQL](https://github.com/Iswenzz/gsclib/blob/master/docs/mysql.md)
* [Utilities](https://github.com/Iswenzz/gsclib/blob/master/docs/utility.md)
* [File](https://github.com/Iswenzz/gsclib/blob/master/docs/file.md)
* [Zip](https://github.com/Iswenzz/gsclib/blob/master/docs/zip.md)

## Instructions
In order to use this library, just download the archived file down below, and extract it to the Call of Duty 4X ``plugins/gsclib`` directory.

## Building (Linux)
_Pre-Requisites:_
1. Edit plugin_handle.h and recompile your server:
```c
#define MAX_SCRIPTFUNCTIONS 256
```
2. [CGSC](https://github.com/Iswenzz/CGSC) and it's pre-requisites.
3. [CMake](https://cmake.org/) and [Conan](https://conan.io/).

_Build Command:_

   	conan remote add iswenzz-conan https://iswenzz.jfrog.io/artifactory/api/conan/iswenzz-conan
	mkdir build && cd build
	conan install .. --build missing --profile:host ../.conan/linux_host.conf --profile:build ../.conan/linux_build.conf
	cmake ..
	cmake --build .

## Building (Windows)
_Pre-Requisites:_
1. Edit plugin_handle.h and recompile your server:
```c
#define MAX_SCRIPTFUNCTIONS 256
```
2. [CGSC](https://github.com/Iswenzz/CGSC) and it's pre-requisites.
3. [CMake](https://cmake.org/) and [Conan](https://conan.io/).
4. [Visual Studio](https://visualstudio.microsoft.com/) with [Clang](https://docs.microsoft.com/en-us/cpp/build/clang-support-msbuild?view=msvc-170) toolset.

**Using the Developer Command Prompt for Visual Studio**
_Build Command:_

    scripts/build_libcom.bat
	conan remote add iswenzz-conan https://iswenzz.jfrog.io/artifactory/api/conan/iswenzz-conan
	mkdir build && cd build
	conan install .. --build missing --profile ../.conan/windows.conf
	cmake .. -A Win32 -T ClangCL
	cmake --build .

***Note:***
VCPKG integration need to be disabled ``vcpkg integration remove``.

## [Download](https://github.com/Iswenzz/gsclib/releases)

## Troubleshouting
For resolving missing dependencies you can use the [ldd](https://man7.org/linux/man-pages/man1/ldd.1.html) command for Linux, and [Dependency Walker](https://www.dependencywalker.com/) for Windows.

## Contributors:
***Note:*** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.
