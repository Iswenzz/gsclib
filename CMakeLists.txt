cmake_minimum_required(VERSION 3.16.0)
project(gsclib VERSION 1.5.1 LANGUAGES C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-m32 -Wall -O1 -g -mtune=core2 -fvisibility=hidden -Wno-unused-result")
set(CMAKE_SHARED_LINKER_FLAGS "-m32 -g -shared -static-libgcc -static-libstdc++")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
add_definitions(-D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN)

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR 7Z)
include(CPack)

# Dependencies
find_path(CGSC_INCLUDE_DIRS "CGSC/cgsc.h")
find_path(LIBMARIADB_INCLUDE_DIRS "mysql/mysql.h")
find_library(CURL_LIBRARY libcurl.a)
find_library(BZ2_LIBRARY libbz2.a)
find_library(LIBCRYPTO_LIBRARY libcrypto.a)
find_library(LIBMARIADB_LIBRARY libmariadb.a)
find_library(LIBZIB_LIBRARY libzip.a)
find_library(OPENSSL_LIBRARY libssl.a)
find_library(PCRE2_LIBRARY libpcre2-8.a)
find_library(ZLIB_LIBRARY NAMES libzlib.a libz.a)
find_package(Cwalk CONFIG REQUIRED)

# Includes
string(APPEND LIBMARIADB_INCLUDE_DIRS "/mysql")

# Tests
if(BUILD_TESTING)
	include(CTest)
	add_library(gsclib.Lib STATIC)
	add_executable(gsclib.Tests)
	find_path(GREATEST_INCLUDE_DIRS "greatest.h")
	target_link_libraries(gsclib.Lib PUBLIC gsclib)
	target_include_directories(gsclib.Lib PUBLIC gsclib)
	target_link_libraries(gsclib.Tests PRIVATE gsclib.Lib)
	target_include_directories(gsclib.Tests PRIVATE gsclib.Lib ${GREATEST_INCLUDE_DIRS})
	add_test(NAME Tests COMMAND gsclib.Tests)
endif()

# Build
add_subdirectory(src)

set_target_properties(gsclib PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ../../../../bin
	RUNTIME_OUTPUT_DIRECTORY ../../../../bin)

target_include_directories(gsclib PUBLIC ..
	${CGSC_INCLUDE_DIRS}
	${LIBMARIADB_INCLUDE_DIRS})

target_link_libraries(gsclib PUBLIC
	$<$<BOOL:${WIN32}>:com_plugin>
	${CURL_LIBRARY}
	${LIBMARIADB_LIBRARY}
	${LIBZIB_LIBRARY}
	${BZ2_LIBRARY}
	${OPENSSL_LIBRARY}
	${LIBCRYPTO_LIBRARY}
	${PCRE2_LIBRARY}
	${ZLIB_LIBRARY}
	$<$<BOOL:${WIN32}>:crypt32>
	$<$<BOOL:${WIN32}>:ws2_32>
	$<$<BOOL:${WIN32}>:bcrypt>
	$<$<BOOL:${WIN32}>:shlwapi>
	$<$<BOOL:${UNIX}>:dl>
	$<$<BOOL:${UNIX}>:rt>
	$<$<BOOL:${UNIX}>:pthread>
	cwalk)

target_link_directories(gsclib PUBLIC ..)

# Install
install(TARGETS gsclib LIBRARY DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/gsclib FILES_MATCHING PATTERN "*.h" PATTERN "__test__" EXCLUDE)
