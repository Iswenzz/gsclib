find_path(LIBMARIADB_INCLUDE_DIRS "mysql/mysql.h")
find_library(LIBMARIADB_LIB mariadb)
find_library(ZLIB_LIB NAMES zlib z)
find_package(OpenSSL REQUIRED)

set(LIBMARIADB_LIBS
	${LIBMARIADB_LIB}
	${ZLIB_LIB}
	openssl::openssl)

set(LIBMARIADB_INCLUDE_DIRS
	${LIBMARIADB_INCLUDE_DIRS}
	${LIBMARIADB_INCLUDE_DIRS}/mysql)

if(WIN32)
	list(APPEND LIBMARIADB_LIBS ws2_32 advapi32 kernel32 shlwapi crypt32)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libmariadb DEFAULT_MSG LIBMARIADB_LIBS LIBMARIADB_INCLUDE_DIRS)
mark_as_advanced(LIBMARIADB_LIBS LIBMARIADB_INCLUDE_DIRS)

if(NOT TARGET libmariadb::libmariadb)
	add_library(libmariadb::libmariadb INTERFACE IMPORTED)
    set_property(TARGET libmariadb::libmariadb PROPERTY INTERFACE_LINK_LIBRARIES "${LIBMARIADB_LIBS}")
	set_property(TARGET libmariadb::libmariadb PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${LIBMARIADB_INCLUDE_DIRS}")
endif()
