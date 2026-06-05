# gsclib

`gsclib` acts as a standard library extension for the Call of Duty 4 scripting language. The features this library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expression (PCRE2) support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion/fmt and other type utilities, ZIP files, async workers, and much more. More detailed information on each feature can be found in the documentation section.

## Documentation

| Module | Description |
|--------|-------------|
| [System](docs/system.md) | Library init, versioning, async status, system commands |
| [Async](docs/async.md) | Critical sections and async request helpers |
| [File](docs/file.md) | File and directory operations |
| [Zip](docs/zip.md) | Zip archive creation and manipulation |
| [HTTP](docs/http.md) | HTTP/HTTPS GET and POST requests |
| [FTP](docs/ftp.md) | FTP, FTPS, and SFTP file transfers |
| [MySQL](docs/mysql.md) | MySQL database queries and prepared statements |
| [LINQ](docs/linq.md) | Array querying and transformation utilities |
| [Regex](docs/regex.md) | Regular expression matching, splitting, and replacing |
| [Math](docs/math.md) | Trigonometric and arithmetic functions |
| [Utility](docs/utility.md) | String formatting, type conversion, and helpers |
| [Player](docs/player.md) | Player movement and state accessors |

## Instructions

In order to use this library, you'll need to compile the binary and place it to the CoD4 `plugins` directory.
Then you can simply use `loadplugin gsclib` in your `server.cfg` or as CLI arguments.
To initialize gsclib library you need to call `GSCLIB_Init()` at the start of your mod entry point.

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

_Pre-Requisites:_

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
