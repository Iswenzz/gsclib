# CGSC

[![Checks](https://img.shields.io/github/check-runs/Iswenzz/CGSC/master?logo=github)](https://github.com/Iswenzz/CGSC/actions)
[![CodeFactor](https://img.shields.io/codefactor/grade/github/Iswenzz/CGSC?label=codefactor&logo=codefactor)](https://www.codefactor.io/repository/github/iswenzz/CGSC)
[![License](https://img.shields.io/github/license/Iswenzz/CGSC?color=blue&logo=gitbook&logoColor=white)](https://github.com/Iswenzz/CGSC/blob/master/LICENSE)

This Call of Duty 4X source extension adds new utilities to extend the server and the creation of new plugins. Such things include new functions to get data types that the original source doesn't offer, the ability to call functions defined in GSC from the C files and async workers for expensive operations on the server. To use this extension you must add the CGSC files included in the release section to the `/src/CGSC` folder, and then compile the CoD4X server source. More detailed instructions can be found towards the bottom of this document.

`Note: Depending on the version of Call of Duty 4X that you're running, some features of CGSC may not be available.`

## Documentation

-   [API](https://github.com/Iswenzz/CGSC/blob/master/docs/api.md)
-   [Async](https://github.com/Iswenzz/CGSC/blob/master/docs/async.md)
-   [Extensions](https://github.com/Iswenzz/CGSC/blob/master/docs/extensions.md)

## Instructions

In order to use this extension, just download the archived file down below, and extract it to the cod4x server's `src/CGSC` directory, then copy the makefile snippet below and paste it before the default rule.
Then simply build the library with the build instructions and recompile the cod4x source with `make`.

### **[Download](https://github.com/Iswenzz/CGSC/releases)**

### **Snippet to add to the cod4x source's makefile before the first target:**

```makefile
##################################
# CGSC
CGSC_DIR=$(SRC_DIR)/CGSC
WIN_LLIBS:=$(WIN_LLIBS) CGSC uv iphlpapi psapi userenv ws2_32 ole32 uuid dbghelp
LINUX_LLIBS:=$(LINUX_LLIBS) CGSC uv dl pthread rt
BSD_LLIBS:=$(BSD_LLIBS) CGSC uv dl pthread rt

WIN_LFLAGS:=$(WIN_LFLAGS) -mconsole

CGSC_ASM_SOURCES=$(wildcard $(CGSC_DIR)/asm/*.asm)
CGSC_ASM_OBJ=$(patsubst $(CGSC_DIR)/asm/%.asm,$(OBJ_DIR)/%.o,$(CGSC_ASM_SOURCES))
ASM_OBJ:=$(ASM_OBJ) $(CGSC_ASM_OBJ)

$(OBJ_DIR)/%.o: $(CGSC_DIR)/asm/%.asm
	@echo	 $(NASM) $@
	@$(NASM) $(NASMFLAGS) $< -o $@
```

## Building (Linux)

_Pre-Requisites:_

    sudo dpkg --add-architecture i386
    sudo apt-get update
    sudo apt-get install nasm:i386 build-essential gcc-multilib g++-multilib

_Build Command:_

    mkdir build && cd build
    cmake .. --preset linux
    cmake --build .

## Building (Windows)

_Pre-Requisites:_

1. Windows [MinGW i686-8.1.0-win32-dwarf-msvcrt](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/8.1.0/threads-win32/dwarf/i686-8.1.0-release-win32-dwarf-rt_v6-rev0.7z)
2. [NASM](https://www.nasm.us/)
3. [CMake](https://cmake.org/) and [vcpkg](https://vcpkg.io/en/).

_Build Command:_

    mkdir build && cd build
    cmake .. --preset windows
    cmake --build .

## Package

This package is available for use via [vcpkg-registry](https://github.com/Iswenzz/vcpkg-registry).

## Contributors:

**_Note:_** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.
