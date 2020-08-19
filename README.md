# gsclib
[![Build status](https://ci.appveyor.com/api/projects/status/wb0m9puc58f5d74w?svg=true)](https://ci.appveyor.com/project/Iswenzz/gsclib)
[![CodeFactor](https://www.codefactor.io/repository/github/iswenzz/gsclib/badge)](https://www.codefactor.io/repository/github/iswenzz/gsclib)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

``gsclib`` acts as a standard library extension for the Call of Duty 4 scripting language. The features this library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expression (RegEx) support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion and other type utilities, and much more. More detailed information on each feature can be found in the documentation section.

## Features & Documentation

* [HTTP/HTTPS client](https://github.com/Iswenzz/gsclib/blob/master/docs/https.md)
* [FTP/FTPS/SFTP client](https://github.com/Iswenzz/gsclib/blob/master/docs/ftp.md)
* [Regular expression](https://github.com/Iswenzz/gsclib/blob/master/docs/regex.md)
* [Language Integrated Query (Linq)](https://github.com/Iswenzz/gsclib/blob/master/docs/linq.md)
* [MySQL](https://github.com/Iswenzz/gsclib/blob/master/docs/mysql.md)
* [Type utilities](https://github.com/Iswenzz/gsclib/blob/master/docs/utility.md)

## Instructions
In order to use this library, just download the archived file down below, and extract it to the Call of Duty 4X ``/plugins/gsclib`` directory.

## Building (Linux)
_Pre-Requisites:_

Debian/Ubuntu 32-bit:

    sudo apt install nasm paxctl build-essential

Debian/Ubuntu 64-bit:

    sudo dpkg --add-architecture i386
    sudo apt-get update
    sudo apt-get install nasm:i386 build-essential gcc-multilib g++-multilib

openSUSE 32-bit:

    sudo zypper install nasm gcc-32bit gcc-c++-32bit

Arch Linux 32-bit:

    yaourt -S nasm paxctl gcc-multilib make
    
_Build Command (Linux):_

    make
    make install
    
***Note:***
``gsclib`` can be compiled without CGSC features with ``make nocgsc``target.

## Building (Windows)
_Pre-Requisites:_
1. [CGSC](https://github.com/Iswenzz/CGSC)
2. Windows [MinGW-W64 GCC-7.3.0](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-win32/dwarf/i686-7.3.0-release-win32-dwarf-rt_v5-rev0.7z)
3. Windows [Cygwin](https://www.cygwin.com/) or [Git for Windows](https://gitforwindows.org/)

_Build Command (Windows):_

    mingw32-make
    mingw32-make install
    
***Note:***
``gsclib`` can be compiled without CGSC features with ``make nocgsc``target.

### [Download](https://github.com/Iswenzz/gsclib/releases)

## Contributors:
***Note:*** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.
