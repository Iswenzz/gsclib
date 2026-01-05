find_path(LIBZIP_INCLUDE_DIR "zip.h")
find_path(LIBZIPPP_INCLUDE_DIR "libzippp/libzippp.h")
find_library(LIBZIP_LIB zip)
find_library(LIBZIPPP_LIB zippp_static)
find_library(BZ2_LIB bz2)
find_library(ZLIB_LIB NAMES zlib z)

set(LIBZIP_LIBS
	${LIBZIPPP_LIB}
	${LIBZIP_LIB}
	${ZLIB_LIB}
	${BZ2_LIB})

set(LIBZIP_INCLUDE_DIRS
	${LIBZIPPP_INCLUDE_DIR}/libzippp
	${LIBZIP_INCLUDE_DIR})

if(WIN32)
	list(APPEND LIBZIP_LIBS Bcrypt)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libzip DEFAULT_MSG LIBZIP_LIBS LIBZIP_INCLUDE_DIRS)
mark_as_advanced(LIBZIP_LIBS LIBZIP_INCLUDE_DIRS)

if(NOT TARGET libzip::libzip)
    add_library(libzip::libzip INTERFACE IMPORTED)
    set_target_properties(libzip::libzip PROPERTIES
        INTERFACE_LINK_LIBRARIES "${LIBZIP_LIBS}"
        INTERFACE_INCLUDE_DIRECTORIES "${LIBZIP_INCLUDE_DIRS}")
endif()
