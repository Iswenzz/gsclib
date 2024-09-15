cmake_minimum_required(VERSION 3.27)
project(gsclib VERSION 1.5.2 LANGUAGES C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-m32 -Wall -O1 -g -mtune=core2 -fvisibility=hidden -Wno-unused-result")
set(CMAKE_SHARED_LINKER_FLAGS "-m32 -g -shared -static-libgcc -static-libstdc++")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# CMake
add_definitions(-D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ClangTools)

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR 7Z)
include(CPack)

# Dependencies
find_path(CGSC_INCLUDE_DIRS "CGSC/cgsc.h")
find_library(PCRE2_LIB pcre2-8)
find_package(Cwalk CONFIG REQUIRED)
find_package(Libcurl REQUIRED)
find_package(Libmariadb REQUIRED)
find_package(Libzip REQUIRED)

# Tests
if(BUILD_TESTING)
	include(CTest)
	add_executable(gsclib.Tests)
	find_path(GREATEST_INCLUDE_DIRS "greatest.h")
	target_link_libraries(gsclib.Tests PRIVATE gsclib)
	target_include_directories(gsclib.Tests PRIVATE ${GREATEST_INCLUDE_DIRS})
	add_test(NAME Tests COMMAND gsclib.Tests)
endif()

# Build
add_subdirectory(src)

set_target_properties(gsclib.Plugin PROPERTIES
	OUTPUT_NAME gsclib
	LIBRARY_OUTPUT_DIRECTORY ../../../../bin
	RUNTIME_OUTPUT_DIRECTORY ../../../../bin)

target_include_directories(gsclib PUBLIC ..
	${CGSC_INCLUDE_DIRS})

target_link_libraries(gsclib PUBLIC
	$<$<BOOL:${WIN32}>:com_plugin>
	$<$<BOOL:${UNIX}>:m>
	${PCRE2_LIB}
	curl::curl
	libmariadb::libmariadb
	libzip::libzip
	cwalk)

target_link_directories(gsclib PUBLIC ..)
