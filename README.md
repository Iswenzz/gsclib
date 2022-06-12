# gsclib

[![Checks](https://img.shields.io/github/checks-status/Iswenzz/gsclib/master?logo=github)](https://github.com/Iswenzz/gsclib/actions)
[![CodeFactor](https://img.shields.io/codefactor/grade/github/Iswenzz/gsclib?label=codefactor&logo=codefactor)](https://www.codefactor.io/repository/github/iswenzz/gsclib)
[![License](https://img.shields.io/github/license/Iswenzz/gsclib?color=blue&logo=gitbook&logoColor=white)](https://github.com/Iswenzz/gsclib/blob/master/LICENSE)

``gsclib`` acts as a standard library extension for the Call of Duty 4 scripting language. The features this library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expression (PCRE2) support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion/fmt and other type utilities, ZIP files, and much more. More detailed information on each feature can be found in the documentation section.

## Features & Documentation
* [HTTP/HTTPS client](https://github.com/Iswenzz/gsclib/blob/master/docs/https.md)
* [FTP/FTPS/SFTP client](https://github.com/Iswenzz/gsclib/blob/master/docs/ftp.md)
* [Regular expression (PCRE2)](https://github.com/Iswenzz/gsclib/blob/master/docs/regex.md)
* [Language Integrated Query (Linq)](https://github.com/Iswenzz/gsclib/blob/master/docs/linq.md)
* [MySQL](https://github.com/Iswenzz/gsclib/blob/master/docs/mysql.md)
* [Utilities](https://github.com/Iswenzz/gsclib/blob/master/docs/utility.md)
* [File](https://github.com/Iswenzz/gsclib/blob/master/docs/file.md)
* [System](https://github.com/Iswenzz/gsclib/blob/master/docs/system.md)
* [Zip](https://github.com/Iswenzz/gsclib/blob/master/docs/zip.md)

## Instructions
In order to use this library, you need to compile CoD4X server for whichever platform you're using.
Navigate inside `CoD4x_Server/plugins/` and follow the build instructions below:

</br>
</br>
</br>

## Building (Linux)
### _Pre-Requisites:_
1. Edit `src/plugin_handler.h` and recompile your server:
	```c
	#define MAX_SCRIPTFUNCTIONS 256
	```
1. [CGSC](https://github.com/Iswenzz/CGSC) and it's pre-requisites
1. [CMake](https://cmake.org/) and [Conan](https://conan.io/). (Install both using pip3 instead of pip2, else errors [(fix)](https://stackoverflow.com/a/69103664/15573604) later on)
1. Make sure your gcc is atleast version 7.5, check using `gcc --version` ( previous versions untested ).

### **_Build Guide:_**

	git clone https://github.com/Iswenzz/gsclib.git && cd gsclib
   	conan remote add iswenzz-conan https://iswenzz.jfrog.io/artifactory/api/conan/iswenzz-conan
	mkdir build && cd build
	conan install .. --build missing --profile:host ../.conan/linux_host.conf --profile:build ../.conan/linux_build.conf

If you see an error like the next screenshot, you will need to specify your compiler version in the above command using `-s compiler.version=(whatever number it shows for your cmake)`.



For example, for the above screenshot, the comipler version would be 8.4, so the argument would be `-s compiler.version=8.4`, and the final command will be `conan install .. --build missing --profile:host ../.conan/linux_host.conf --profile:build ../.conan/linux_build.conf -s compiler.version=8.4`

Now finalize the build:

	cmake ..
	cmake --build .

> The compiled `gsclib.so` will be inside `build/lib/`


</br>
</br>
</br>

## Building (Windows)
_Pre-Requisites:_
1. Edit plugin_handler.h and recompile your server:
```c
#define MAX_SCRIPTFUNCTIONS 256
```
1. [CGSC](https://github.com/Iswenzz/gsclib) and it's pre-requisites.
1. [CMake](https://cmake.org/) and [Conan](https://conan.io/).
1. [Visual Studio](https://visualstudio.microsoft.com/) with [Clang](https://docs.microsoft.com/en-us/cpp/build/clang-support-msbuild?view=msvc-170) toolset.

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
