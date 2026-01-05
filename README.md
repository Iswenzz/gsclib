# gsclib

[![Checks](https://img.shields.io/github/check-runs/Iswenzz/gsclib/master?logo=github)](https://github.com/Iswenzz/gsclib/actions)
[![CodeFactor](https://img.shields.io/codefactor/grade/github/Iswenzz/gsclib?label=codefactor&logo=codefactor)](https://www.codefactor.io/repository/github/iswenzz/gsclib)
[![License](https://img.shields.io/github/license/Iswenzz/gsclib?color=blue&logo=gitbook&logoColor=white)](https://github.com/Iswenzz/gsclib/blob/master/LICENSE)

`gsclib` acts as a standard library extension for the Call of Duty 4 scripting language. The features this library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expression (PCRE2) support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion/fmt and other type utilities, ZIP files, async workers, and much more. More detailed information on each feature can be found in the documentation section.

## Features & Documentation

- [HTTP/HTTPS Client](https://github.com/Iswenzz/gsclib/blob/master/docs/http.md)
- [FTP/FTPS/SFTP Client](https://github.com/Iswenzz/gsclib/blob/master/docs/ftp.md)
- [Regular Expression (PCRE2)](https://github.com/Iswenzz/gsclib/blob/master/docs/regex.md)
- [Language Integrated Query (Linq)](https://github.com/Iswenzz/gsclib/blob/master/docs/linq.md)
- [MySQL](https://github.com/Iswenzz/gsclib/blob/master/docs/mysql.md)
- [Async](https://github.com/Iswenzz/gsclib/blob/master/docs/async.md)
- [Utilities](https://github.com/Iswenzz/gsclib/blob/master/docs/utility.md)
- [File](https://github.com/Iswenzz/gsclib/blob/master/docs/file.md)
- [Zip](https://github.com/Iswenzz/gsclib/blob/master/docs/zip.md)
- [System](https://github.com/Iswenzz/gsclib/blob/master/docs/system.md)
- [Player](https://github.com/Iswenzz/gsclib/blob/master/docs/player.md)
- [Math](https://github.com/Iswenzz/gsclib/blob/master/docs/math.md)

## Instructions

In order to use this library, you'll need to compile the binary and place it to the CoD4 `plugins` directory.
Then you can simply use `loadplugin gsclib` in your `server.cfg` or as CLI arguments.

## Server

1. Edit `plugin_handler.h` and set `#define MAX_SCRIPTFUNCTIONS` to `256`.
2. Run the script `install.bat` or `install.sh` located in the `api` folder.
3. Clean the server build then recompile.

## Building (Windows)

_Pre-Requisites:_

1. [MinGW](https://github.com/brechtsanders/winlibs_mingw/releases/download/15.2.0posix-13.0.0-msvcrt-r5/winlibs-i686-posix-dwarf-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r5.zip)
2. [CMake](https://cmake.org/) and [vcpkg](https://vcpkg.io/en/)

_Build Command:_

    mkdir build && cd build
    cmake .. --preset windows
    cmake --build .

## Building (Linux)

_Pre-Requisites:_

1. [CMake](https://cmake.org/) and [vcpkg](https://vcpkg.io/en/)

	sudo dpkg --add-architecture i386
    sudo apt update
    sudo apt install build-essential gcc-multilib g++-multilib pkg-config linux-libc-dev nasm:i386

_Build Command:_

    mkdir build && cd build
    cmake .. --preset linux
    cmake --build .

## [Download](https://github.com/Iswenzz/gsclib/releases)

## Contributors:

**_Note:_** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.
