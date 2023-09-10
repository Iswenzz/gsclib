cmake_minimum_required(VERSION 3.16.0)
project(gsclib VERSION 1.5.1 LANGUAGES C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-m32 -Wall -O1 -s -mtune=core2 -Wno-unused-result")
set(CMAKE_SHARED_LINKER_FLAGS "-m32 -s -shared -static-libgcc -static-libstdc++")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
add_definitions(-D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN)

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR 7Z)
include(CPack)

# Dependencies
set(LIBMARIADB_LIBRARY ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib/mariadb/libmariadbclient.a)
set(LIBMARIADB_INCLUDE_DIRS ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/mariadb)
set(PCRE2_LIBRARY ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib/libpcre2-8.a)
find_package(CURL CONFIG REQUIRED)
find_package(Cwalk CONFIG REQUIRED)
find_package(libzip CONFIG REQUIRED)
find_path(CGSC_INCLUDE_DIRS "CGSC/cgsc.h")

# Tests
if(BUILD_TESTING)
	include(CTest)
	add_executable(gsclib.Tests)
	find_path(GREATEST_INCLUDE_DIRS "greatest.h")
	target_link_libraries(gsclib.Tests PRIVATE gsclib.Static)
	target_include_directories(gsclib.Tests PRIVATE .. ${GREATEST_INCLUDE_DIRS})
	add_test(NAME Tests COMMAND gsclib.Tests)
endif()

# Build
add_subdirectory(src)
target_include_directories(gsclib PUBLIC .. ${CGSC_INCLUDE_DIRS} ${LIBMARIADB_INCLUDE_DIRS})
target_link_directories(gsclib PUBLIC ..)

target_link_libraries(gsclib PUBLIC
	$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:libcom_plugin>
	CURL::libcurl
	cwalk
	libzip::zip
	${LIBMARIADB_LIBRARY}
	${PCRE2_LIBRARY})

target_include_directories(gsclib.Static PRIVATE .. ${CGSC_INCLUDE_DIRS} ${LIBMARIADB_INCLUDE_DIRS})
target_link_directories(gsclib.Static PRIVATE ..)
target_link_libraries(gsclib.Static PRIVATE gsclib)

# Pack
install(TARGETS gsclib LIBRARY DESTINATION lib)
install(DIRECTORY src/ DESTINATION lib/include/gsclib
    FILES_MATCHING PATTERN "*.h" PATTERN "__test__" EXCLUDE)
