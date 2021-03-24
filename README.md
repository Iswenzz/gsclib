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
1. Recompile your server with:
```c
#define MAX_SCRIPTFUNCTIONS 256
```
2. [CGSC](https://github.com/Iswenzz/CGSC) and it's pre-requisites.
    
_Build Command (Linux):_

    make
    make install
    
***Note:***
``gsclib`` can be compiled without CGSC features with ``make nocgsc`` target.

## Building (Windows)
_Pre-Requisites:_
1. Recompile your server with:
```c
#define MAX_SCRIPTFUNCTIONS 256
```
2. [CGSC](https://github.com/Iswenzz/CGSC) and it's pre-requisites.
3. Windows [Cygwin](https://www.cygwin.com/) or [Git for Windows](https://gitforwindows.org/)

_Build Command (Windows):_

    mingw32-make
    mingw32-make install
    
***Note:***
``gsclib`` can be compiled without CGSC features with ``mingw32-make nocgsc`` target.

## [Download](https://github.com/Iswenzz/gsclib/releases)

## Troubleshouting
For resolving missing dependencies you can use the [ldd](https://man7.org/linux/man-pages/man1/ldd.1.html) command for Linux, and [Dependency Walker](https://www.dependencywalker.com/) for Windows.

## Contributors:
***Note:*** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.
