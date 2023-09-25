find_path(LIBZIP_INCLUDE_DIRS "zip.h")
find_library(LIBZIB_LIB zip)
find_library(BZ2_LIB bz2)
find_library(ZLIB_LIB NAMES zlib z)
find_package(OpenSSL REQUIRED)

set(LIBZIP_LIBS
	${LIBZIB_LIB}
	${BZ2_LIB}
	${ZLIB_LIB}
	openssl::openssl)

if(WIN32)
	list(APPEND LIBZIP_LIBS advapi32)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libzip DEFAULT_MSG LIBZIP_LIBS LIBZIP_INCLUDE_DIRS)
mark_as_advanced(LIBZIP_LIBS LIBZIP_INCLUDE_DIRS)

if(NOT TARGET libzip::libzip)
	add_library(libzip::libzip INTERFACE IMPORTED)
    set_property(TARGET libzip::libzip PROPERTY INTERFACE_LINK_LIBRARIES "${LIBZIP_LIBS}")
	set_property(TARGET libzip::libzip PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${LIBZIP_INCLUDE_DIRS}")
endif()
